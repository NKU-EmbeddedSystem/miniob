/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include <unordered_set>

#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"
#include "sql/executor/value.h"

using namespace common;
using std::unordered_set;

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
//  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

//  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op)
{
//  if (attr_type < CHARS || attr_type > FLOATS) {
//    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type);
//    return RC::INVALID_ARGUMENT;
//  }

//  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
//    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
//    return RC::INVALID_ARGUMENT;
//  }

  left_ = left;
  right_ = right;
  printf("condition filter evaluated to AttrType: %d\n", attr_type);
  attr_type_ = attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

RC DefaultConditionFilter::init(const Table &table, const Condition &condition)
{
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  left.type = condition.left.type;
  if (is_attr(&condition.left)) {
    const FieldMeta *field_left = table_meta.field(condition.left.attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left.attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.nullable_ = field_left->is_nullable();
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();
    left.value = nullptr;
    type_left = field_left->type();
  } else if (is_value(&condition.left)){
    left.value = condition.left.value.data;  // 校验type 或者转换类型
    type_left = condition.left.value.type;

    left.nullable_ = false;
    left.attr_length = 0;
    left.attr_offset = 0;
  } else {
    left.subquery = condition.left.subquery;
    type_left = condition.left.subquery->result_type;
  }

  right.type = condition.right.type;
  if (is_attr(&condition.right)) {
    const FieldMeta *field_right = table_meta.field(condition.right.attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right.attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.nullable_ = field_right->is_nullable();
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();

    right.value = nullptr;
  } else if (is_value(&condition.right)){
    right.value = condition.right.value.data;
    type_right = condition.right.value.type;

    right.nullable_ = false;
    right.attr_length = 0;
    right.attr_offset = 0;
  } else {
    right.subquery = condition.right.subquery;
    type_right = condition.right.subquery->result_type;
  }

  left.isnull_ = (type_left == NULLS);
  right.isnull_ = (type_right == NULLS);

  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
  // 但是选手们还是要实现。这个功能在预选赛中会出现
  if (type_left != type_right) {
    if (type_left == NULLS || type_right == NULLS) {
      goto match;
    }

    if (((type_left == INTS && type_right == FLOATS) || (type_left == FLOATS && type_right == INTS))
      && !((is_attr(left) && is_attr(right)))) {
      float_int_ = true;
      int_left_ = (type_left == INTS);
      goto match;
    }
    // subquery type can be viewed the same as attribute
    if ((is_value(left) && !is_value(right)) || (!is_value(left) && is_value(right))) {
      ConDesc &attr_cond = is_value(left) ? right : left;
      ConDesc &value_cond = is_value(left) ? left : right;
      AttrType attr_type = is_value(left) ? type_right : type_left;
      AttrType value_type = is_value(left) ? type_left : type_right;

      // rewrite date value
      if (attr_type == DATE && value_type == CHARS) {
        tm t;

        // validate and rewrite scalar value
        if (DateValue::validate_data_format(
                static_cast<const char *>(value_cond.value), &t)) {
          *reinterpret_cast<date_t *>(value_cond.value) = DateValue::to_raw_data(&t);

          // for later init() parameter
          type_left = DATE;

          goto match;
        } else {
          return RC::INVALID_ARGUMENT;
        }
      }
    }

    if ((is_attr(left) && !is_attr(right))|| (is_attr(right) && !is_attr(left))) {

    }
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

match:
  return init(left, right, type_left, condition.comp);
}

int DefaultConditionFilter::subquery_filter(const Record &rec, bool *has_null) const {
  TupleValue *left_value = nullptr;
  TupleValue *right_value = nullptr;
  char *value;
  int result;

  if (is_attr(left_)) {
    value = (char *)(rec.data + left_.attr_offset);
    left_value = TupleValue::from(attr_type_, value);
  } else if (is_value(left_)) {
    value = (char *)left_.value;
    left_value = TupleValue::from(attr_type_, value);
  } else {
    left_value = static_cast<TupleValue *>(left_.subquery->result)->clone();
  }

  if (is_attr(right_)) {
    value = (char *)(rec.data + right_.attr_offset);
    right_value = TupleValue::from(attr_type_, value);
  } else if (is_value(right_)) {
    value = (char *)right_.value;
    right_value = TupleValue::from(attr_type_, value);
  } else {
    right_value = static_cast<TupleValue *>(right_.subquery->result)->clone();
  }

  *has_null = (left_value->is_null() || right_value->is_null());

  if (!(*has_null) && float_int_) {
    if (int_left_) {
      left_value = FloatValue::move_from(static_cast<IntValue *>(left_value));
    } else {
      right_value = FloatValue::move_from(static_cast<IntValue *>(right_value));
    }
  }

  result = left_value->compare(*right_value);
  delete left_value;
  delete right_value;
  return result;
}

bool DefaultConditionFilter::filter(const Record &rec) const
{
  int left_isnull = 0;
  int right_isnull = 0;
  char *left_value = nullptr;
  char *right_value = nullptr;
  int cmp_result = 0;

  if (comp_op_ != COND_IN && comp_op_ != NOT_IN && (float_int_ || is_subquery(left_) || is_subquery(right_))) {
    bool has_null;
    cmp_result = subquery_filter(rec, &has_null);
    if (has_null) {
      return false;
    } else {
      goto op_switch;
    }
  }

  if (is_attr(left_)) {  // value
    if (left_.nullable_) {
      // nullable占4位
      left_isnull = *(int *)(rec.data + left_.attr_offset);
      left_value = (char *)(rec.data + left_.attr_offset + 4);
    }else {
      left_value = (char *)(rec.data + left_.attr_offset);
    }
  } else if (is_value(left_)) {
    left_isnull = left_.isnull_;
    if (!left_isnull)
      left_value = (char *)left_.value;
  } else {
    LOG_ERROR("DefaultConditionFilter::filter: left is subquery");
  }

  if (is_attr(right_)) {
    if (right_.nullable_) {
      // nullable需要多读4位判断是否为空
      right_isnull = *(int *)(rec.data + right_.attr_offset);
      right_value = (char *)(rec.data + right_.attr_offset + 4);
    } else {
        right_value = (char *)(rec.data + right_.attr_offset);
    }
  } else if (is_value(right_)){
    right_isnull = right_.isnull_;
    if (!right_isnull)
      right_value = (char *)right_.value;
  } else {
    LOG_ERROR("DefaultConditionFilter::filter: right is subquery");
  }

  if (comp_op_ != IS_OP && comp_op_ != IS_NOT_OP) {
    if (left_isnull || right_isnull)
      return false;
  }

  if (comp_op_ == IS_NOT_OP) {
    return !left_isnull;
  }

  if (comp_op_ == IS_OP) {
    return left_isnull;
  }

  using Set = std::unordered_set<TupleValue *, std::hash<TupleValue *>, TupleValueKeyEqualTo>;
  if (comp_op_ == COND_IN || comp_op_ == NOT_IN) {
    printf("DefaultConditionFilter::filter: deal with in operator\n");
    Subquery *subquery = right_.subquery;
    AttrType set_type = subquery->result_type;
    if (attr_type_ != set_type) {
      LOG_ERROR("Where IN operator type mismatch: left = %d, right = %d", attr_type_, set_type);
      return false;
    }

    bool found;
    TupleValue *temp_tuple_value_from_record = TupleValue::from(attr_type_, left_value);
    auto set = static_cast<Set *>(subquery->result);
    found = (set->find(temp_tuple_value_from_record) != set->end());
    delete temp_tuple_value_from_record;
    return (comp_op_ == COND_IN) == found;
  }

  switch (attr_type_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    case FLOATS: {
      float left = *(float *)left_value;
      float right = *(float *)right_value;
      auto fcmp = left - right;
      if (fcmp == 0) {
        cmp_result = 0;
      } else {
        cmp_result = (fcmp > 0) ? 1 : -1;
      }
    } break;
    case DATE: {
      date_t left = *reinterpret_cast<date_t *>(left_value);
      date_t right = *reinterpret_cast<date_t *>(right_value);
      cmp_result = static_cast<int>(left - right);
    } break;
    default: {
      LOG_ERROR("error comp data type\n");
    }
    break;
  }

op_switch:
  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;
    case IS_OP:
      return left_isnull && right_isnull;
    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
