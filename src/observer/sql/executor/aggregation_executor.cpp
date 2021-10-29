//
// Created by Luminosity on 2021/10/28.
//

#include "aggregation_executor.h"
#include "common/log/log.h"

AggregationExecutor::~AggregationExecutor() {
  for (auto aggregator : aggregators_) {
    delete aggregator;
  }
}

RC AggregationExecutor::execute(AggTupleSet &result_tuple_set) {
  RC rc = create_aggregators();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  do_aggregation();
  collect_result(result_tuple_set);

  return RC::SUCCESS;
}

RC AggregationExecutor::create_aggregators() {
  Aggregator *aggregator;

  for (int i = 0; i < selects_.agg_num; i++) {
    aggregator = create_from(selects_.aggs[i]);
    if (aggregator == nullptr) {
      LOG_ERROR("Fail to create aggregator for aggregation[%d]", i);
      return RC::GENERIC_ERROR;
    }

    aggregators_.push_back(aggregator);
  }

  return RC::SUCCESS;
}

Aggregator *AggregationExecutor::create_from(const AggDesc &agg_desc) {
  auto agg_type = agg_desc.agg_type;
  auto operand_type = agg_desc.agg_operand_type;

  switch (agg_type) {
    case AGG_COUNT: {
      return new CountAggregator(agg_desc);
    }
    case AGG_MAX:
    case AGG_MIN:
    case AGG_AVG: {
      if (operand_type == AGG_NUMBER) {
        return new ConstAggregator(agg_desc, agg_desc.number);
      }
    }
    break;
  }

  // max/min/avg with field operand
  int pos;
  RC rc = find_pos_of_agg_field_in_schema(agg_desc.agg_attr, &pos);
  if (rc != RC::SUCCESS) {
    return nullptr;
  }

  const AttrType attr_type = in_tuple_set_.schema().field(pos).type();
  switch (agg_type) {
    case AGG_MAX: {
      return new MaxAggregator(agg_desc, pos);
    }
    case AGG_MIN: {
      return new MinAggregator(agg_desc, pos);
    }
    case AGG_AVG: {
      return new AvgAggregator(agg_desc, pos, attr_type);
    }
  }

  return nullptr;
}

RC AggregationExecutor::find_pos_of_agg_field_in_schema(const RelAttr &rel_attr, int *pos) {
  const auto &schema = in_tuple_set_.schema();

  *pos = (rel_attr.relation_name == nullptr)
    ? schema.index_of_field(rel_attr.attribute_name)
    : schema.index_of_field(rel_attr.relation_name, rel_attr.attribute_name);

  if (*pos < 0) {
    LOG_ERROR("Fail to find position of [relation = %s, field = %s] in schema for aggregation",
              rel_attr.relation_name, rel_attr.attribute_name);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

void AggregationExecutor::do_aggregation() {
  for (const auto &tuple : in_tuple_set_.tuples()) {
    for (auto aggregator : aggregators_) {
      aggregator->consume(tuple);
    }
  }
}

void AggregationExecutor::collect_result(AggTupleSet &out_tuple_set) {
  auto& schema = out_tuple_set.schema();
  for (auto aggregator : aggregators_) {
    schema.add(aggregator->desc());
  }

  if (!in_tuple_set_.is_empty()) {
    Tuple tuple;

    for (auto aggregator: aggregators_) {
      tuple.add(const_cast<TupleValue *>(aggregator->result()));
    }

    out_tuple_set.add(std::move(tuple));
  }
}