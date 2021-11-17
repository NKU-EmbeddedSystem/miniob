//
// Created by Light-Laptop on 2021/10/27.
//

#include <vector>

#include "query_checker.h"
#include "common/log/log.h"
#include "aggregator.h"
#include "storage/default/default_handler.h"

#define push_local_tables() \
  vector<Table *> local_tables;   \
  vector<Table *> *tables_save = local_tables_; \
  local_tables_ = &local_tables

#define pop_local_tables() local_tables_ = tables_save

#define push_match_func() \
  relattr_match_func_t match_func_save = relattr_match_table_; \
  relattr_match_table_ = &QueryChecker::subquery_condition_nullable_relattr_match_table

#define pop_match_func() relattr_match_table_ = match_func_save

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

  // check FROM relations existence
  for (int i = 0; i < relation_num; i++) {
    const char *relation_name = relations[i];
    printf("relation_name[%d]: %p\n", i, relation_name);
    table = DefaultHandler::get_default().find_table(db_, relation_name);
    if (table == nullptr) {
      LOG_WARN("No such table [%s] in db [%s]", relation_name, db_);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    printf("local tables_ : %p\n", local_tables_);
    local_tables_->push_back(table);
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_where_fields_helper(const Condition conditions[], int condition_num) {
  RC rc;

  // check WHERE relation.attribute existence
  for (int i = 0; i < condition_num; i++) {
    const Condition &condition = conditions[i];

    if (is_subquery(&condition.left) && is_subquery(&condition.right)) {
      LOG_ERROR("Illegal sql: both side of where condition are subquery");
      return RC::SQL_SYNTAX;
    }

    if (is_attr(&condition.left)) {
      rc = (this->*relattr_match_table_)(condition.left.attr, nullptr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (is_subquery(&condition.left)) {
      printf("check left subquery: %p\n", condition.left.subquery);
      rc = check_subquery(condition.left.subquery, condition.comp, true);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    if (is_attr(&condition.right)) {
      rc = (this->*relattr_match_table_)(condition.right.attr, nullptr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (is_subquery(&condition.right)) {
      printf("check right subquery: %p\n", condition.right.subquery);
      rc = check_subquery(condition.right.subquery, condition.comp, false);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return RC::SUCCESS;
}

RC QueryChecker::non_nullable_relattr_match_any_table(const RelAttr &rel_attr, AttrType *attr_type) {
  const FieldMeta *field_meta;

  if (rel_attr.relation_name == nullptr) {
    LOG_ERROR("Multiple table query requires identifying table of the field");
    return RC::SCHEMA_TABLE_NAME_ILLEGAL;
  }

  for (auto table: global_tables_) {
    if (strcmp(table->name(), rel_attr.relation_name) == 0
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

RC QueryChecker::nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type) {
  Table *table = global_tables_[0];
  const FieldMeta *field_meta;

  if (rel_attr.relation_name != nullptr) {
    if (strcmp(rel_attr.relation_name, table->name()) != 0) {
      LOG_ERROR("Field identifier table name: %s conflicts with single table name: %s", rel_attr.relation_name, table->name());
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }
  }

  if (strcmp(rel_attr.attribute_name, "*") != 0) {
    if ((field_meta = table->table_meta().field(rel_attr.attribute_name)) == nullptr) {
      LOG_ERROR("Table: %s doesn't have field: %s", table->name(), rel_attr.attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    if (attr_type != nullptr) {
      *attr_type = field_meta->type();
    }
  }

  return RC::SUCCESS;
}


RC QueryChecker::check_subquery(const Subquery *subquery, CompOp comp, bool left) {
  RC rc;
  printf("into check_subquery\n");
  rc = check_subquery_position(comp, left);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  printf("before check result type\n");
  rc = check_subquery_result_type(subquery, comp);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  printf("after check result type\n");
  push_local_tables();

  printf("after check from\n");
  rc = check_from_relations_and_init_tables_helper(subquery->relations, subquery->relation_num);
  if (rc != RC::SUCCESS) {
    pop_local_tables();
    return rc;
  }

  printf("before check where\n");
  rc = check_subquery_where_fields(subquery);
  if (rc != RC::SUCCESS) {
    pop_local_tables();
    return rc;
  }

  printf("before check attr\n");
  rc = check_subquery_select_attribute(subquery);
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
  printf("\tcomp: %d is_agg: %d\n", comp, subquery->is_agg);
  if (comp != COND_IN && comp != NOT_IN && !subquery->is_agg) {
    LOG_ERROR("Illegal sql: subquery should be evaluated to single value");
    return RC::SQL_SYNTAX;
  }
  return RC::SUCCESS;
}

RC QueryChecker::check_subquery_where_fields(const Subquery *subquery) {
  RC rc;

  for (auto table : *local_tables_) {
    global_tables_.push_back(table);
  }
  push_match_func();

  rc = check_where_fields_helper(subquery->conditions, subquery->condition_num);

  pop_match_func();
  for (int i = 0; i < local_tables_->size(); i++) {
    global_tables_.pop_back();
  }

  return rc;
}

RC QueryChecker::subquery_condition_nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type) {
  const FieldMeta *field_meta;

  if (rel_attr.relation_name == nullptr) {
    if (local_tables_->size() > 1) {
      LOG_ERROR("Multiple table query requires identifying table of the field");
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }

    Table *table = (*local_tables_)[0];

    if ((field_meta = table->table_meta().field(rel_attr.attribute_name)) == nullptr) {
      LOG_ERROR("Table: %s doesn't have field: %s", table->name(), rel_attr.attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    if (attr_type != nullptr) {
      *attr_type = field_meta->type();
    }
    return RC::SUCCESS;
  }

  for (auto table : global_tables_) {
    if (strcmp(table->name(), rel_attr.relation_name) == 0
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
      rc = subquery_select_attr_nullable_relattr_match_table(agg_desc.agg_attr, &agg_field_type);
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
    return subquery_select_attr_nullable_relattr_match_table(subquery->attribute, nullptr);
  }
}

RC QueryChecker::subquery_select_attr_nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type) {
  const FieldMeta *field_meta;

  if (rel_attr.relation_name == nullptr) {
    if (strcmp(rel_attr.attribute_name, "*") == 0) {
      return RC::SUCCESS;
    }

    if (local_tables_->size() > 1) {
      LOG_ERROR("Multiple table query requires identifying table of the field");
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }

    Table *table = (*local_tables_)[0];

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
    if (strcmp(table->name(), rel_attr.relation_name) == 0
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

    rc = (this->*relattr_match_table_)(rel_attr, nullptr);
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
      || strcmp(group_by_field.relation_name, attr_field.relation_name) == 0;
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
      rc = (this->*relattr_match_table_)(agg_desc.agg_attr, &agg_field_type);
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

    rc = (this->*relattr_match_table_)(rel_attr, nullptr);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return RC::SUCCESS;
}
