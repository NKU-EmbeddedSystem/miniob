//
// Created by Light-Laptop on 2021/10/27.
//

#include <atomic>

#include "common/log/log.h"
#include "single_relation_select_execution_node_creator.h"
#include "storage/default/default_handler.h"

static RC push_single_table_filter(const Condition &condition, const Table *table, std::vector<DefaultConditionFilter *> &condition_filters);
static bool condition_refers_multiple_tables(const Condition &condition);
static RC schema_add_field(const Table *table, const char *field_name, TupleSchema &schema);
static bool relattr_refers_table(const RelAttr &rel_attr, const char *table_name);
static RC force_extend_tuple_schema(const Table *table, TupleSchema &schema);

RC SingleRelationSelectExeNodeCreator::create(vector<SelectExeNode *> &select_nodes, vector<int> &extra_counts) {
  RC rc;

  for (int i = 0; i < selects_.relation_num; i++) {
    int extra_count = 0;
    const char *table_name = selects_.relations[i];
    SelectExeNode *select_node = new SelectExeNode;

    rc = create_selection_executor(table_name, select_node, extra_count);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }

      return rc;
    }

    select_nodes.push_back(select_node);
    extra_counts.push_back(extra_count);
  }

  return RC::SUCCESS;
}

RC SingleRelationSelectExeNodeCreator::create_selection_executor(const char *table_name, SelectExeNode *select_node, int &extra_count) {
  // 列出跟这张表关联的Attr
  Table * table = DefaultHandler::get_default().find_table(db_, table_name);

  // 设置结果集的列名
  TupleSchema schema;
  RC rc = (this->*create_tuple_schema_)(table, schema);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  rc = create_condition_filters(table, schema, condition_filters, extra_count);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return select_node->init(trx_, table, std::move(schema), std::move(condition_filters));
}

RC SingleRelationSelectExeNodeCreator::create_condition_filters(
        const Table *table,
        TupleSchema &schema,
        vector<DefaultConditionFilter *> &condition_filters,
        int &extra_count) {
  auto table_name = table->name();
  RC rc;

  for (int i = 0; i < selects_.condition_num; i++) {
    const auto &condition = selects_.conditions[i];
    if (condition_refers_single_table(condition, table_name)) {
      rc = push_single_table_filter(condition, table, condition_filters);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (condition_refers_multiple_tables(condition)) {
      rc = condition_filter_extend_tuple_schema(condition, table_name, schema, extra_count);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return RC::SUCCESS;
}

bool SingleRelationSelectExeNodeCreator::condition_refers_single_table(
        const Condition &condition,
        const char *table_name) {
  return (condition.left_is_attr == 0 && condition.right_is_attr == 0) // 两边都是值
         || (condition.left_is_attr == 1 && condition.right_is_attr == 0
             && match_table(condition.left_attr.relation_name, table_name)) // 左边是属性右边是值
         || (condition.left_is_attr == 0 && condition.right_is_attr == 1
             && match_table(condition.right_attr.relation_name, table_name)) // 左边是值，右边是属性名
         || (condition.left_is_attr == 1 && condition.right_is_attr == 1
             && match_table(condition.left_attr.relation_name, table_name)
             && match_table(condition.right_attr.relation_name, table_name)); // 左右都是属性名，并且表名都符合
}

bool SingleRelationSelectExeNodeCreator::match_table(
        const char *table_name_in_condition,
        const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects_.relation_num == 1;
}

static RC push_single_table_filter(const Condition &condition, const Table *table, std::vector<DefaultConditionFilter *> &condition_filters) {
  DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
  RC rc = condition_filter->init(*table, condition);
  if (rc != RC::SUCCESS) {
    delete condition_filter;
    for (DefaultConditionFilter * &filter : condition_filters) {
      delete filter;
    }
    return rc;
  }

  condition_filters.push_back(condition_filter);
  return RC::SUCCESS;
}

static bool condition_refers_multiple_tables(const Condition &condition) {
  return condition.left_is_attr == 1 && condition.right_is_attr == 1
         && strcmp(condition.left_attr.relation_name, condition.right_attr.relation_name) != 0;
}

RC SingleRelationSelectExeNodeCreator::condition_filter_extend_tuple_schema(
        const Condition &condition,
        const char *table_name,
        TupleSchema &schema,
        int &extra_count) {
  char *left_attr_name = condition.left_attr.attribute_name;
  char *left_table_name = condition.left_attr.relation_name;
  char *right_attr_name = condition.right_attr.attribute_name;
  char *right_table_name = condition.right_attr.relation_name;
  const Table *left_table = DefaultHandler::get_default().find_table(db_, left_table_name);
  const Table *right_table = DefaultHandler::get_default().find_table(db_, right_table_name);
  int left_idx = schema.index_of_field(condition.left_attr.relation_name, left_attr_name);

  // 增加对应的列，不过得在自己这个表里才加
  // 如果类型不匹配返回错误 或者增加对应的列
  if (left_idx == -1) {
    if (strcmp(left_table_name, table_name) == 0)
    {
      RC rc = schema_add_field(left_table, left_attr_name, schema);
      if (rc != RC::SUCCESS)
      {
        return rc;
      }
      extra_count++;
    }
  }

  int right_idx = schema.index_of_field(condition.right_attr.relation_name, right_attr_name);
  if (right_idx == -1) {
    if (strcmp(right_table_name, table_name) == 0) {
      RC rc = schema_add_field(right_table, right_attr_name, schema);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      extra_count++;
    }
  }
}

static RC schema_add_field(const Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

static RC create_tuple_schema_from_aggregation_list(const Selects &selects, Table *table, TupleSchema &schema) {
  int agg_num = selects.agg_num;
  int schema_empty = true;

  // try to add from aggregation field
  for (int i = agg_num - 1; i >= 0; i--) {
    const auto &agg_desc = selects.aggs[i];
    if (agg_desc.agg_operand_type == AGG_FIELD) {
      if (agg_desc.agg_attr.relation_name == nullptr) {
        if (selects.relation_num > 1) {
          return RC::INVALID_ARGUMENT;
        }
      } else {
        if (strcmp(agg_desc.agg_attr.relation_name, table->name()) != 0) {
          continue;
        }
      }
      auto field_meta = table->table_meta().field(agg_desc.agg_attr.attribute_name);
      schema_add_field(table, field_meta->name(), schema);
      schema_empty = false;
    }
  }

  // try to find from where conditions
  if (schema_empty) {

  }

//  return create_tuple_schema_from_aggregation_list(table, schema);
}

RC SingleRelationSelectExeNodeCreator::create_tuple_schema_from_attribute_list(const Table *table, TupleSchema &schema) {
  auto table_name = table->name();

  /**
   * distinguish select attribute from select aggregation
   *
   * attr_num and agg_num will not greater than 0 at the same time,
   * because parser doesn't recognize it
   *
   * here prepare schema for selected attribute/aggregation
   */
  for (int i = selects_.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects_.attributes[i];
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  return RC::SUCCESS;
}

RC SingleRelationSelectExeNodeCreator::create_tuple_schema_from_aggregation_list(const Table *table, TupleSchema &schema) {
  RC rc;

  // try to add from aggregation field
  rc = aggregation_list_extend_tuple_schema(table, schema);
  if (rc == RC::SUCCESS || rc != RC::EMPTY) {
    return rc;
  }

  // if condition filter will later extend it, schema will later be filled
  rc = condition_filter_will_extend_tuple_schema(table, schema);
  if (rc == RC::SUCCESS) {
    return rc;
  }

  // randomly pick a column(this is necessary for SQL like select count(*) from t;)
  rc = force_extend_tuple_schema(table, schema);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return RC::SUCCESS;
}

RC SingleRelationSelectExeNodeCreator::aggregation_list_extend_tuple_schema(const Table *table, TupleSchema &schema) {
  RC rc = RC::EMPTY;

  for (int i = 0; i < selects_.agg_num; i++) {
    const auto &agg_desc = selects_.aggs[i];
    if (agg_desc.agg_operand_type == AGG_FIELD
        && relattr_refers_table(agg_desc.agg_attr, table->name())) {
      rc = schema_add_field(table, agg_desc.agg_attr.attribute_name, schema);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return rc;
}

static bool relattr_refers_table(const RelAttr &rel_attr, const char *table_name) {
  // (field existence & multiple tables identification) checks have been done before,
  // so here we only check name match
  return rel_attr.relation_name == nullptr
         || strcmp(rel_attr.relation_name, table_name) == 0;
}

RC SingleRelationSelectExeNodeCreator::condition_filter_will_extend_tuple_schema(const Table *table, const TupleSchema &schema) {
  const char *table_name = table->name();

  for (int i = 0; i < selects_.condition_num; i++) {
    const auto &condition = selects_.conditions[i];
    if ((condition.left_is_attr && relattr_refers_table(condition.left_attr, table_name))
        || (condition.right_is_attr && relattr_refers_table(condition.right_attr, table_name))) {
      // do not extend schema here, because latter condition filter will itself extend it
      return RC::SUCCESS;
    }
  }

  return RC::EMPTY;
}

static RC force_extend_tuple_schema(const Table *table, TupleSchema &schema) {
  RC rc;
  auto table_meta = table->table_meta();

  // directly pick the first visible column of the table
  // for latter aggregation operation(like count(*))
  const FieldMeta *field_meta = table_meta.field(table_meta.sys_field_num());
  if (field_meta == nullptr) {
    LOG_ERROR("Table %s has no field", table->name());
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  rc = schema_add_field(table, field_meta->name(), schema);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return RC::SUCCESS;
}