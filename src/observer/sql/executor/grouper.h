//
// Created by Light-Laptop on 2021/11/12.
//

#ifndef MINIDB_GROUPER_H
#define MINIDB_GROUPER_H

#include <vector>
#include <unordered_map>

#include "aggregator_manager.h"
#include "sql/parser/parse.h"
#include "storage/common/table.h"
#include "rc.h"

class Grouper {
  using Key = TupleValue *;
  using Value = std::shared_ptr<void>;
  using Map = std::unordered_map<Key, Value, std::hash<TupleValue *>, TupleValueKeyEqualTo>;
  using Group = std::vector<const Tuple *>;

public:
  Grouper(const Selects &selects, const TupleSet &in_tuple_set, const char *db)
    : selects_(selects), in_tuple_set_(in_tuple_set), db_(db),
      manager_(selects, in_tuple_set), map_depth_(selects.group_by_num)
    { }

  RC execute(GroupByTupleSet &out_tuple_set);

private:
  RC init(GroupByTupleSet &out_tuple_set);
  RC init_schema_and_indices(GroupByTupleSet &out_tuple_set);
  Group *get_group_of_tuple(const Tuple &tuple);
  Group *create_later_map_chain(Map *map, int chain_start_cnt, const Tuple &tuple);
  void do_aggregation(GroupByTupleSet &out_tuple_set);
  void do_aggregation_helper(int depth, void *ptr, const Tuple &tuple, GroupByTupleSet &out_tuple_set);

  const Selects &selects_;
  const TupleSet &in_tuple_set_;
  const char *db_;
  AggregatorManager manager_;
  const int map_depth_;
  std::vector<int> group_by_tuple_indices;
  Map map_;
};


#endif //MINIDB_GROUPER_H
