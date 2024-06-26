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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"

Tuple::Tuple(const Tuple &other) {
  values_.resize(other.values_.size());
  std::copy(other.values_.begin(), other.values_.end(), values_.begin());
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

void Tuple::add(date_t value) {
  add(new DateValue(value));
}

void Tuple::add_null() {
  add(new NullValue());
}

void Tuple::pop_back() {
  values_.pop_back();
}

std::vector<std::pair<int, OrderType>> orders_;

bool compare(const Tuple &t1, const Tuple &t2) {
  for (const auto & order : orders_) {
    int comp = t1.get(order.first).compare(t2.get(order.first));
    if (order.second == ORDER_DESC) {
      comp = -comp;
    }
    if (comp < 0)
      return true;
    if (comp > 0)
      return false;
  }
  return false;
}

void TupleSet::sort_by_orders(std::vector<Order> &orders) {
  if (orders.empty())
    return;
  const auto &schema = get_schema();
  orders_.clear();
  for (const auto order: orders) {
    int field_index;
    if (order.order_attr.relation_name == nullptr) {
      field_index = schema.index_of_field(order.order_attr.attribute_name);
    } else {
      field_index = schema.index_of_field(order.order_attr.relation_name, order.order_attr.attribute_name);
    }
    orders_.emplace_back(field_index, order.order_type);
  }
  std::sort(tuples_.begin(), tuples_.end(), compare);
}
////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

int TupleSchema::index_of_field(const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print_content(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (table_names.size() > 1) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (table_names.size() > 1) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name();
}

void TupleSchema::print(std::ostream &os) const {
  print_content(os);
  os << std::endl;
}

void TupleSchema::mprint_content(std::ostream &os) const {
   if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    os << iter->table_name() << ".";
    os << iter->field_name() << " | ";
  }

  os << fields_.back().table_name() << ".";
  os << fields_.back().field_name();
}

void TupleSchema::mprint(std::ostream &os) const {
  mprint_content(os);
  os << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}


void TupleSet::add_record(Tuple &tuple, TupleSchema &schema) {
  const TupleSchema &res_schema = get_schema();
  // 用来筛选只有res的列的tuple
  Tuple added;
  for (const auto &field : res_schema.fields()) {
    int schema_index = schema.index_of_field(field.field_name());
    added.add(tuple.values()[schema_index]);
  }
  add(std::move(added));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

void TupleSet::pop_row() {
  for (int i = 0; i < tuples_.size(); ++i) {
    tuples_[i].pop_back();
  }
}

void TupleSet::mprint(std::ostream &os) {
if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.mprint(os);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }

}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}


void TupleRecordConverter::add_record(const char *record) {
  int offset = 0;
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    bool is_null = false;
    if (field_meta->is_nullable()) {
      is_null = *(int *) (record + field_meta->offset());
      offset = 4;
    }
    else {
      offset = 0;
    }

    if (is_null) {
      tuple.add_null();
      continue;
    }

    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset() + offset);
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset() + offset);
        tuple.add(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset() + offset;  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      case DATE: {
        date_t value = *reinterpret_cast<const date_t *>(record + field_meta->offset() + offset);
        tuple.add(value);
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}

void AggSchema::print_content(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  for (auto iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    os << agg_type_name(iter->agg_type) << "(";
    if (iter->agg_operand_type == AGG_NUMBER) {
      os << iter->number;
    } else {
      if (iter->agg_attr.relation_name != nullptr) {
        os << iter->agg_attr.relation_name << ".";
      }
      os << iter->agg_attr.attribute_name;
    }
    os << ") | ";
  }

  auto back = fields_.back();
  os << agg_type_name(back.agg_type) << "(";
  if (back.agg_operand_type == AGG_NUMBER) {
    os << back.number;
  } else {
    if (back.agg_attr.relation_name != nullptr) {
      os << back.agg_attr.relation_name << ".";
    }
    os << back.agg_attr.attribute_name;
  }
  os << ")";
}

void AggSchema::print(std::ostream &os) const {
  print_content(os);
  os << std::endl;
}

void AggTupleSet::print(std::ostream &os) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (auto iter = values.begin(), end = --values.end();
         iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void GroupBySchema::print(std::ostream &os, const Selects &selects) const {
  if (selects.relation_num > 1) {
    group_schema_.mprint_content(os);
  } else {
    group_schema_.print_content(os);
  }
  os << " | ";
  agg_schema_.print_content(os);
  os << std::endl;
}

void GroupByTupleSet::print(std::ostream &os, const Selects &selects) const {
  if (schema_.group_schema().fields().empty()) {
    LOG_WARN("Got empty group by group schema");
    return;
  }

  if (schema_.agg_schema().fields().empty()) {
    LOG_WARN("Got empty group by agg schema");
    return;
  }

  schema_.print(os, selects);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (auto iter = values.begin(), end = --values.end();
         iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}