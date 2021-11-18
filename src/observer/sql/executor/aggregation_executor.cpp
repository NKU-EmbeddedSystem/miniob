//
// Created by Luminosity on 2021/10/28.
//

#include "aggregation_executor.h"

RC AggregationExecutor::execute(AggTupleSet &result_tuple_set) {
  RC rc = manager_.create();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  do_aggregation();
  collect_result(result_tuple_set);

  return RC::SUCCESS;
}

void AggregationExecutor::do_aggregation() {
  for (const auto &tuple : in_tuple_set_.tuples()) {
    for (auto aggregator : manager_.aggregators()) {
      aggregator->consume(tuple);
    }
  }
}

void AggregationExecutor::collect_result(AggTupleSet &out_tuple_set) {
  auto& schema = out_tuple_set.schema();
  auto& aggregators = manager_.aggregators();

  for (auto aggregator : aggregators) {
    schema.add(aggregator->desc());
  }

  Tuple tuple;

  for (auto aggregator: aggregators) {
    tuple.add(const_cast<TupleValue *>(aggregator->result()));
  }

  out_tuple_set.add(std::move(tuple));
}