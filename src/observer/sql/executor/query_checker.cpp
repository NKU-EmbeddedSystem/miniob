//
// Created by Light-Laptop on 2021/10/27.
//

#include <vector>

#include "query_checker.h"
#include "common/log/log.h"
#include "aggregator.h"
#include "storage/default/default_handler.h"

RC QueryChecker::check_fields() {
  Table *table;
  std::vector<Table *> tables;
  RC rc;

  rc = check_from_relations_and_init_tables();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = check_where_fields();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = (this->*check_select_list_fields_)();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_from_relations_and_init_tables() {
  Table *table;

  // check FROM relations existence
  for (int i = 0; i < selects_.relation_num; i++) {
    const char *relation_name = selects_.relations[i];
    table = DefaultHandler::get_default().find_table(db_, relation_name);
    if (table == nullptr) {
      LOG_WARN("No such table [%s] in db [%s]", relation_name, db_);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables_.push_back(table);
  }

  return RC::SUCCESS;
}

RC QueryChecker::check_where_fields() {
  RC rc;

  // check WHERE relation.attribute existence
  for (int i = 0; i < selects_.condition_num; i++) {
    const Condition &condition = selects_.conditions[i];
    if (condition.left_is_attr == 1) {
      rc = (this->*relattr_match_table_)(condition.left_attr, nullptr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    if (condition.right_is_attr == 1) {
      rc = (this->*relattr_match_table_)(condition.right_attr, nullptr);
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

  for (auto table: tables_) {
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
  Table *table = tables_[0];
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
