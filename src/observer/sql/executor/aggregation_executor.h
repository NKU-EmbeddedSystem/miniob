//
// Created by Luminosity on 2021/10/28.
//

#ifndef MINIDB_AGGREGATION_EXECUTOR_H
#define MINIDB_AGGREGATION_EXECUTOR_H

#include <vector>

#include "rc.h"
#include "aggregator.h"
#include "aggregator_manager.h"

using std::vector;

class AggregationExecutor {
public:
  AggregationExecutor(const Selects &selects, const TupleSet &in_tuple_set)
    : selects_(selects), in_tuple_set_(in_tuple_set), manager_(selects, in_tuple_set)
    { }

  RC execute(AggTupleSet &result_tuple_set);

private:
  void do_aggregation();
  void collect_result(AggTupleSet &out_tuple_set);

  const Selects &selects_;
  const TupleSet &in_tuple_set_;
  AggregatorManager manager_;
};


#endif //MINIDB_AGGREGATION_EXECUTOR_H
