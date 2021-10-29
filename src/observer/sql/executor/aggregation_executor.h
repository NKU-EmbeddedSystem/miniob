//
// Created by Luminosity on 2021/10/28.
//

#ifndef MINIDB_AGGREGATION_EXECUTOR_H
#define MINIDB_AGGREGATION_EXECUTOR_H

#include <vector>

#include "rc.h"
#include "aggregator.h"

using std::vector;

class AggregationExecutor {
public:
  AggregationExecutor(const Selects &selects, const TupleSet &in_tuple_set)
    : selects_(selects), in_tuple_set_(in_tuple_set)
    { }

  ~AggregationExecutor();
  RC execute(AggTupleSet &result_tuple_set);

private:
  RC create_aggregators();
  Aggregator *create_from(const AggDesc &agg_desc);
  RC find_pos_of_agg_field_in_schema(const RelAttr &rel_attr, int *pos);
  void do_aggregation();
  void collect_result(AggTupleSet &out_tuple_set);

  const Selects &selects_;
  const TupleSet &in_tuple_set_;
  vector<Aggregator *> aggregators_;
};


#endif //MINIDB_AGGREGATION_EXECUTOR_H
