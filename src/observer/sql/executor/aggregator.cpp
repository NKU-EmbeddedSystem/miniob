//
// Created by Light-Laptop on 2021/10/27.
//

#include "aggregator.h"
#include "common/log/log.h"
#include "storage/common/field_meta.h"

RC Aggregator::check_operand_type_match_agg_type(const AggDesc &agg_desc) {
  auto operand_type = agg_desc.agg_operand_type;
  auto agg_type = agg_desc.agg_type;

  switch (operand_type) {
    case AGG_STAR: {
      if (agg_type != AGG_COUNT) {
        goto mismatch;
      }
    }
    break;
  }

  return RC::SUCCESS;

mismatch:
  LOG_ERROR("Aggregation type %s mismatches operand type: %s", agg_type_name(agg_type), agg_operand_name(operand_type));
  return RC::INVALID_ARGUMENT;
}

RC Aggregator::check_field_type_match_agg_type(const AggDesc &agg_desc, const AttrType &attr_type) {
  auto agg_type = agg_desc.agg_type;

  switch (agg_type) {
    case AGG_AVG: {
      if (attr_type == CHARS || attr_type == DATE) {
        goto mismatch;
      }
    }
    break;
  }

  return RC::SUCCESS;

mismatch:
  LOG_ERROR("Aggregation type %s mismatches field type: %d", agg_type_name(agg_type), attr_type);
  return RC::INVALID_ARGUMENT;
}