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
  typedef RC (QueryChecker::*relattr_match_func_t)(const RelAttr &, AttrType *attr_type, bool augment);
  typedef RC (QueryChecker::*select_list_fields_check_func_t)();

public:
  QueryChecker(const char *db, const Selects &selects)
    : db_(db), selects_(selects), local_tables_(&global_tables_), is_aggregation_query_(selects.agg_num > 0),
      relattr_match_table_(
              (selects.relation_num > 1)
              ? &QueryChecker::non_nullable_relattr_match_any_table
              : &QueryChecker::nullable_relattr_match_table)
    { }

  RC check_fields();

private:
  RC non_nullable_relattr_match_any_table(const RelAttr &rel_attr, AttrType *attr_type, bool augment);
  RC nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type, bool augment);
  RC check_from_relations_and_init_tables() { return check_from_relations_and_init_tables_helper(selects_.relations, selects_.relation_num); }
  RC check_from_relations_and_init_tables_helper(const char * const relations[], int relation_num);
  RC check_where_fields() { return check_where_fields_helper(selects_.conditions, selects_.condition_num, false); }
  RC check_where_fields_helper(const Condition conditions[], int condition_num, bool subquery_is_agg);
  RC check_and_push_extra_in_comparator_condition(const Condition &condition);
  bool is_checking_subquery() { return local_tables_ != &global_tables_; }
  RC check_subquery_condition_makes_sense(const Condition &condition);
  RC check_subquery(Subquery *subquery, CompOp comp, bool left);
  RC check_subquery_position(CompOp comp, bool left);
  RC check_subquery_result_type(const Subquery *subquery, CompOp comp);
  RC check_subquery_where_fields(Subquery *subquery);
  RC check_and_rewrite_subquery_where_fields_identifier(Subquery *subquery);
  RC check_mark_subquery_lazy_and_get_result_type(Subquery *subquery);
  RC check_mark_condition_field_refers_outer(Subquery *subquery, ConditionField &cond_field);
  RC check_and_augment_relations_from_where_fields(Subquery *subquery);
  bool relation_in(const char *relation_name, const vector<Table *> &tables, Table **);
  RC check_subquery_select_attribute(const Subquery *subquery);
  RC subquery_select_attr_nullable_relattr_match_table(const RelAttr &rel_attr, AttrType *attr_type, bool augment);
  RC check_group_by_fields();
  bool find_group_by_field_in_attribute_list(const RelAttr &group_by_field);
  RC check_attribute_list_fields();
  RC check_aggregation_list_fields();

  const char *db_;
  const Selects &selects_;
  vector<Table *> global_tables_;
  vector<Table *> *local_tables_;
  bool is_aggregation_query_;
  relattr_match_func_t relattr_match_table_;
};

#endif //MINIDB_QUERY_CHECKER_H
