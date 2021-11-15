//
// Created by Light-Laptop on 2021/10/27.
//

#ifndef MINIDB_QUERY_CHECKER_H
#define MINIDB_QUERY_CHECKER_H

#include <vector>

#include "sql/parser/parse.h"
#include "storage/common/table.h"
#include "rc.h"

using std::vector;

class QueryChecker {
private:
  typedef RC (QueryChecker::*relattr_match_func_t)(const RelAttr &, AttrType *attr_type);
  typedef RC (QueryChecker::*select_list_fields_check_func_t)();

public:
  QueryChecker(const char *db, const Selects &selects)
    : db_(db), selects_(selects), is_aggregation_query_(selects.agg_num > 0),
      relattr_match_table_(
              (selects.relation_num > 1)
              ? &QueryChecker::non_nullable_relattr_match_any_table
              : &QueryChecker::nullable_relattr_match_table)
    { }

  RC check_fields();

private:
  RC non_nullable_relattr_match_any_table(const RelAttr &rel_attr, AttrType *attr_type);
  RC nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type);
  RC check_from_relations_and_init_tables();
  RC check_where_fields();
  RC check_group_by_fields();
  bool find_group_by_field_in_attribute_list(const RelAttr &group_by_field);
  RC check_attribute_list_fields();
  RC check_aggregation_list_fields();

  const char *db_;
  const Selects &selects_;
  vector<Table *> tables_;
  bool is_aggregation_query_;
  relattr_match_func_t relattr_match_table_;
};

#endif //MINIDB_QUERY_CHECKER_H
