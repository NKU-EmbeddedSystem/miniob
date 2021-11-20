//
// Created by Light-Laptop on 2021/10/27.
//

#include <vector>

#include "query_checker.h"
#include "common/log/log.h"
#include "aggregator.h"
#include "aggregator_manager.h"
#include "storage/default/default_handler.h"

#define push_local_tables() \
  vector<Table *> local_tables;   \
  vector<Table *> *tables_save = local_tables_; \
  local_tables_ = &local_tables

#define pop_local_tables() local_tables_ = tables_save

#define push_match_func_and_global_table() \
  for (auto table : *local_tables_) { \
    global_tables_.push_back(table); \
  }                                        \
  int push_cnt = local_tables_->size();                                        \
  relattr_match_func_t match_func_save = relattr_match_table_; \
  relattr_match_table_ = &QueryChecker::non_nullable_relattr_match_any_table

#define pop_match_func_and_global_table() \
  for (int i = 0; i < push_cnt; i++) { \
    global_tables_.pop_back(); \
  } \
  relattr_match_table_ = match_func_save

static inline bool refers(const char *relation_name, const char *table_name) {
  return strcmp(relation_name, table_name) == 0;
}

static inline bool refers(const char *relation_name, const Table *table) {
  return strcmp(relation_name, table->name()) == 0;
}

RC QueryChecker::check_fields() {
  RC rc;

  rc = check_from_relations_and_init_tables();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = check_where_fields();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = check_group_by_fields();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = check_attribute_list_fields();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = check_aggregation_list_fields();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_from_relations_and_init_tables_helper(const char *const relations[], int relation_num) {
  Table *table;

  if (relation_num == 0) {
    LOG_ERROR("Illegal sql: empty FROM relations");
    return RC::SQL_SYNTAX;
  }

  // check FROM relations existence
  for (int i = 0; i < relation_num; i++) {
    const char *relation_name = relations[i];
    table = DefaultHandler::get_default().find_table(db_, relation_name);
    if (table == nullptr) {
      LOG_WARN("No such table [%s] in db [%s]", relation_name, db_);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    local_tables_->push_back(table);
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_where_fields_helper(const Condition conditions[], int condition_num, bool subquery_is_agg) {
  RC rc;

  // check WHERE relation.attribute existence
  for (int i = 0; i < condition_num; i++) {
    const Condition &condition = conditions[i];

    if (condition.comp == COND_IN || condition.comp == NOT_IN) {
      if (!is_attr(&condition.left) || !is_subquery(&condition.right)) {
        LOG_ERROR("Illegal sql: left/right side of IN must be attribute/subquery");
        return RC::SQL_SYNTAX;
      }
    }

    if (is_attr(&condition.left)) {
      rc = (this->*relattr_match_table_)(condition.left.attr, nullptr, true);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (is_subquery(&condition.left)) {
      rc = check_subquery(condition.left.subquery, condition.comp, true);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    if (is_attr(&condition.right)) {
      rc = (this->*relattr_match_table_)(condition.right.attr, nullptr, true);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (is_subquery(&condition.right)) {
      rc = check_subquery(condition.right.subquery, condition.comp, false);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    if (is_checking_subquery() && !subquery_is_agg) {
      rc = check_subquery_condition_makes_sense(condition);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return RC::SUCCESS;
}

RC QueryChecker::non_nullable_relattr_match_any_table(const RelAttr &rel_attr, AttrType *attr_type, bool augment) {
  const FieldMeta *field_meta;

  if (!is_checking_subquery() && rel_attr.relation_name == nullptr) {
    LOG_ERROR("Multiple table query requires identifying table of the field");
    return RC::SCHEMA_TABLE_NAME_ILLEGAL;
  }

  for (auto table: global_tables_) {
    if (refers(rel_attr.relation_name, table)
        && (field_meta = table->table_meta().field(rel_attr.attribute_name)) != nullptr) {
      if (attr_type != nullptr) {
        *attr_type = field_meta->type();
      }
      return RC::SUCCESS;
    }
  }

  LOG_ERROR("No table matches table: %s field: %s", rel_attr.relation_name, rel_attr.attribute_name);
  return RC::SCHEMA_FIELD_NOT_EXIST;
}

RC QueryChecker::nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type, bool augment) {
  Table *table = global_tables_[0];
  const FieldMeta *field_meta;

  if (rel_attr.relation_name != nullptr) {
    if (!refers(rel_attr.relation_name, table)) {
      LOG_ERROR("Field identifier table name: %s conflicts with single table name: %s", rel_attr.relation_name, table->name());
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }
  }

  if (strcmp(rel_attr.attribute_name, "*") != 0) {
    if ((field_meta = table->table_meta().field(rel_attr.attribute_name)) == nullptr) {
      LOG_ERROR("Table: %s doesn't have field: %s", table->name(), rel_attr.attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    if (augment) {
      const_cast<RelAttr &>(rel_attr).relation_name = strdup(table->name());
    }

    if (attr_type != nullptr) {
      *attr_type = field_meta->type();
    }
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_subquery_condition_makes_sense(const Condition &condition) {
  /*
   * Queries whose condition has at least one attribute field like:
   *    select * from t1 where t1.id in (select t2.id from t2 where t1.id > 1);
   *    select * from t1, t2 where t1.id in (select t3.id from t3 where t1.id > t2.id);
   * make no sense, because conditions of subquery refer no subquery relations.
   *
   * However, queries like:
   *    select * from t1 where t1.id in (select t2.id from t2 where t1.id > 1 and t2.id > t1.id);
   *    select * from t1, t2 where t1.id in (select t3.id from t3 where t1.id > t2.id and t3.id > t1.id and t3.id > t2.id);
   *    select * from t1, t2 where t1.id in (select t3.id from t3 where t1.id > t2.id and t3.id > t1.id);
   * should pass, because the multiple table conditions(e.g. t2.id > t1.id in first query) implies more tables should be
   * augmented to origin subquery relations.
   *
   * Note queries like:
   *    select * from t1 where t1.id in (select t3.id from t3 where t1.id > t2.id and t3.id > t1.id and t3.id > t2.id);
   * are also illegal, because t2 doesn't appear in outer join list.
   *
   * Still, queries like:
   *    select * from t1, t2 where t1.id in (select t3.id from t3 where t2.id > 3 and t3.id > t1.id);
   * make so sense.
   *
   * Subquery relation augmentation should be dealt with earlier.
   */
  if (is_attr(&condition.left) && is_attr(&condition.right)) {
    for (auto table : *local_tables_) {
      if (refers(condition.left.attr.relation_name, table)
        || refers(condition.right.attr.relation_name, table)) {
        return RC::SUCCESS;
      }
    }
  } else if (!is_attr(&condition.left) && !is_attr(&condition.right)) {
    return RC::SUCCESS;
  } else {
    const ConditionField &attr_field = is_attr(&condition.left) ? condition.left : condition.right;
    for (auto table : *local_tables_) {
      if (refers(attr_field.attr.relation_name, table)) {
        return RC::SUCCESS;
      }
    }
  }

  LOG_ERROR("Illegal sql: subquery condition refers no subquery relations");
  return RC::SQL_SYNTAX;
}

RC QueryChecker::check_subquery(Subquery *subquery, CompOp comp, bool left) {
  RC rc;
  rc = check_subquery_position(comp, left);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = check_subquery_result_type(subquery, comp);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  push_local_tables();

  rc = check_from_relations_and_init_tables_helper(subquery->relations, subquery->relation_num);
  if (rc != RC::SUCCESS) {
    pop_local_tables();
    return rc;
  }

  rc = check_subquery_select_attribute(subquery);
  if (rc != RC::SUCCESS) {
    pop_local_tables();
    return rc;
  }

  rc = check_subquery_where_fields(subquery);
  if (rc != RC::SUCCESS) {
    pop_local_tables();
    return rc;
  }

  pop_local_tables();
  return RC::SUCCESS;
}

RC QueryChecker::check_subquery_position(CompOp comp, bool left) {
  if ((comp == COND_IN || comp == NOT_IN) && left) {
    LOG_ERROR("Illegal sql: subquery should be on right side of (NOT) IN comparator");
    return RC::SQL_SYNTAX;
  }
  return RC::SUCCESS;
}

RC QueryChecker::check_subquery_result_type(const Subquery *subquery, CompOp comp) {
  if (subquery->is_agg) {
    if (comp == COND_IN || comp == NOT_IN) {
      LOG_ERROR("Illegal sql: subquery should not be evaluated to single value");
      return RC::SQL_SYNTAX;
    }
  } else {
    if (comp != COND_IN && comp != NOT_IN) {
      LOG_ERROR("Illegal sql: subquery should be evaluated to single value");
      return RC::SQL_SYNTAX;
    }
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_subquery_where_fields(Subquery *subquery) {
  RC rc;

  push_match_func_and_global_table();

  rc = check_and_rewrite_subquery_where_fields_identifier(subquery);
  if (rc !=  RC::SUCCESS) {
    pop_match_func_and_global_table();
    return rc;
  }

  rc = check_mark_subquery_lazy_and_get_result_type(subquery);

  if (rc != RC::SUCCESS) {
    pop_match_func_and_global_table();
    return rc;
  }

  rc = check_where_fields_helper(subquery->conditions, subquery->condition_num, subquery->is_agg);

  pop_match_func_and_global_table();
  return rc;
}

RC QueryChecker::check_and_rewrite_subquery_where_fields_identifier(Subquery *subquery) {
  if (local_tables_->size() == 1) {
    const char *table_name = (*local_tables_)[0]->name();
    for (int i = 0; i < subquery->condition_num; i++) {
      Condition &condition = subquery->conditions[i];
      if (is_attr(&condition.left) && condition.left.attr.relation_name == nullptr) {
        condition.left.attr.relation_name = strdup(table_name);
      }
      if (is_attr(&condition.right) && condition.right.attr.relation_name == nullptr) {
        condition.right.attr.relation_name = strdup(table_name);
      }
    }
  } else {
    for (int i = 0; i < subquery->condition_num; i++) {
      Condition &condition = subquery->conditions[i];
      if ((is_attr(&condition.left) && condition.left.attr.relation_name == nullptr)
        || (is_attr(&condition.right) && condition.right.attr.relation_name == nullptr)) {
        LOG_ERROR("Multiple table query requires identifying table of the field");
        return RC::SCHEMA_TABLE_NAME_ILLEGAL;
      }
    }
  }
  return RC::SUCCESS;
}

RC QueryChecker::check_mark_subquery_lazy_and_get_result_type(Subquery *subquery) {
  RC rc;

  for (int i = 0; i < subquery->condition_num; i++) {
    Condition &condition = subquery->conditions[i];

    if (is_attr(&condition.left)) {
      rc = check_mark_condition_field_refers_outer(subquery, condition.left);
      if (rc != RC::SUCCESS) {
        rc;
      }
    }

    if (is_attr(&condition.right)) {
      rc = check_mark_condition_field_refers_outer(subquery, condition.right);
      if (rc != RC::SUCCESS) {
        rc;
      }
    }
  }

  if (subquery->is_agg) {
    subquery->result_type = AggregatorManager::result_type(subquery->agg, db_);
  } else {
    subquery->result_type = DefaultHandler::get_default()
            .find_table(db_, subquery->attribute.relation_name)
            ->table_meta().field(subquery->attribute.attribute_name)->type();
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_mark_condition_field_refers_outer(Subquery *subquery, ConditionField &cond_field) {
  bool in_local = relation_in(cond_field.attr.relation_name, *local_tables_, nullptr);

  if (!in_local) {
    Table *table;
    bool in_global = relation_in(cond_field.attr.relation_name, global_tables_, &table);

    if (in_global) {
      cond_field.refers_outer = 1;
    } else {
      LOG_ERROR("Illegal sql: %s is in neither local tables nor global tables",
                cond_field.attr.relation_name);
      return RC::SQL_SYNTAX;
    }
  }

  return RC::SUCCESS;
}

bool QueryChecker::relation_in(const char *relation_name, const vector<Table *> &tables, Table **found_table) {
  for (auto table : tables) {
    if (refers(relation_name, table)) {
      if (found_table != nullptr) {
        *found_table = table;
      }
      return true;
    }
  }
  return false;
}

RC QueryChecker::check_subquery_select_attribute(const Subquery *subquery) {
  if (subquery->is_agg) {
    const AggDesc &agg_desc = subquery->agg;
    AttrType agg_field_type;
    RC rc;

    rc = Aggregator::check_operand_type_match_agg_type(agg_desc);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (agg_desc.agg_operand_type == AGG_FIELD) {
      rc = subquery_select_attr_nullable_relattr_match_table(agg_desc.agg_attr, &agg_field_type, true);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      rc = Aggregator::check_field_type_match_agg_type(agg_desc, agg_field_type);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    return RC::SUCCESS;
  } else {
    return subquery_select_attr_nullable_relattr_match_table(subquery->attribute, nullptr, true);
  }
}

RC QueryChecker::subquery_select_attr_nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type, bool augment) {
  const FieldMeta *field_meta;

  if (rel_attr.relation_name == nullptr) {
    if (strcmp(rel_attr.attribute_name, "*") == 0) {
      return RC::SQL_SYNTAX;
    }

    if (local_tables_->size() > 1) {
      LOG_ERROR("Multiple table query requires identifying table of the field");
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }

    Table *table = (*local_tables_)[0];
    const_cast<RelAttr &>(rel_attr).relation_name = strdup(table->name());

    if ((field_meta = table->table_meta().field(rel_attr.attribute_name)) == nullptr) {
      LOG_ERROR("Table: %s doesn't have field: %s", table->name(), rel_attr.attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    if (attr_type != nullptr) {
      *attr_type = field_meta->type();
    }
    return RC::SUCCESS;
  }

  for (auto table : *local_tables_) {
    if (refers(rel_attr.relation_name, table)
        && (field_meta = table->table_meta().field(rel_attr.attribute_name)) != nullptr) {
      if (attr_type != nullptr) {
        *attr_type = field_meta->type();
      }
      return RC::SUCCESS;
    }
  }

  LOG_ERROR("No table matches table: %s field: %s", rel_attr.relation_name, rel_attr.attribute_name);
  return RC::SCHEMA_FIELD_NOT_EXIST;
}

RC QueryChecker::check_group_by_fields() {
  // bypass check
  if (selects_.group_by_num == 0) {
    return RC::SUCCESS;
  }

  // syntax check
  if (!is_aggregation_query_) {
    LOG_ERROR("GROUP BY on non-aggregation query.");
    return RC::GENERIC_ERROR;
  }

  // field check
  RC rc;

  for (int i = 0; i < selects_.group_by_num; i++) {
    const auto &rel_attr = selects_.group_by_attributes[i];

    rc = (this->*relattr_match_table_)(rel_attr, nullptr, false);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (!find_group_by_field_in_attribute_list(rel_attr)) {
      LOG_ERROR("Cannot find group by table: %s field: %s from attribute list",
                rel_attr.relation_name, rel_attr.attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }

  return RC::SUCCESS;
}

bool QueryChecker::find_group_by_field_in_attribute_list(const RelAttr &group_by_field) {
  bool field_found, table_found;

  for (int i = 0; i < selects_.attr_num; i++) {
    const auto &attr_field = selects_.attributes[i];
    field_found = strcmp(group_by_field.attribute_name, attr_field.attribute_name) == 0;
    table_found = group_by_field.relation_name == nullptr
      || attr_field.relation_name == nullptr
      || refers(group_by_field.relation_name, attr_field.relation_name);
    if (field_found && table_found) {
      return true;
    }
  }

  return false;
}

RC QueryChecker::check_aggregation_list_fields() {
  RC rc;
  AttrType agg_field_type;

  for (int i = 0; i < selects_.agg_num; i++) {
    const auto &agg_desc = selects_.aggs[i];

    rc = Aggregator::check_operand_type_match_agg_type(agg_desc);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (selects_.aggs[i].agg_operand_type == AGG_FIELD) {
      rc = (this->*relattr_match_table_)(agg_desc.agg_attr, &agg_field_type, false);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      rc = Aggregator::check_field_type_match_agg_type(agg_desc, agg_field_type);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_attribute_list_fields() {
  RC rc;

  for (int i = 0; i < selects_.attr_num; i++) {
    const auto &rel_attr = selects_.attributes[i];

    // deal with "*"(well, this should also be the only attribute, guaranteed by parser)
    if (rel_attr.relation_name == nullptr && strcmp("*", rel_attr.attribute_name) == 0) {
      return RC::SUCCESS;
    }

    rc = (this->*relattr_match_table_)(rel_attr, nullptr, false);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return RC::SUCCESS;
}
