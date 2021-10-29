//
// Created by Light-Laptop on 2021/10/27.
//

#ifndef MINIDB_SINGLE_RELATION_SELECT_EXECUTION_NODE_CREATOR_H
#define MINIDB_SINGLE_RELATION_SELECT_EXECUTION_NODE_CREATOR_H

#include <vector>

#include "sql/executor/execution_node.h"
#include "sql/parser/parse.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"
#include "rc.h"

using std::vector;

class SingleRelationSelectExeNodeCreator {
private:
  typedef SelectExeNode *(SingleRelationSelectExeNodeCreator::*create_select_node_func_t)();
  typedef RC (SingleRelationSelectExeNodeCreator::*create_tuple_schema_func_t)(const Table *table, TupleSchema &schema);

public:
  SingleRelationSelectExeNodeCreator(const char *db, const Selects &selects, Trx *trx)
    : db_(db), selects_(selects), trx_(trx),
      create_tuple_schema_(
              (selects.agg_num > 0)
              ? &SingleRelationSelectExeNodeCreator::create_tuple_schema_from_aggregation_list
              : &SingleRelationSelectExeNodeCreator::create_tuple_schema_from_attribute_list)
    { }

  RC create(vector<SelectExeNode *> &select_nodes, vector<int> &extra_counts);

private:
  RC create_selection_executor(const char *table_name, SelectExeNode *select_node, int &extra_count);
  RC create_tuple_schema_from_aggregation_list(const Table *table, TupleSchema &schema);
  RC create_tuple_schema_from_attribute_list(const Table *table, TupleSchema &schema);
  RC create_condition_filters(const Table *table, TupleSchema &schema, vector<DefaultConditionFilter *> &condition_filters, int &extra_count);
  bool condition_refers_single_table(const Condition &condition, const char *table_name);
  bool match_table(const char *table_name_in_condition, const char *table_name_to_match);
  RC condition_filter_extend_tuple_schema(const Condition &condition, const char *table_name, TupleSchema &schema, int &extra_count);
  RC aggregation_list_extend_tuple_schema(const Table *table, TupleSchema &schema);
  RC condition_filter_will_extend_tuple_schema(const Table *table, const TupleSchema &schema);

  const char *db_;
  const Selects &selects_;
  Trx *trx_;
  create_tuple_schema_func_t create_tuple_schema_;
};


#endif //MINIDB_SINGLE_RELATION_SELECT_EXECUTION_NODE_CREATOR_H
