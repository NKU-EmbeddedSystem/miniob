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

#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_H_
#define __OBSERVER_SQL_EXECUTOR_TUPLE_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "sql/parser/parse.h"
#include "sql/executor/value.h"

class Table;

class Tuple {
public:
  Tuple() = default;

  Tuple(const Tuple &other);

  ~Tuple();

  Tuple(Tuple &&other) noexcept ;
  Tuple & operator=(Tuple &&other) noexcept ;

  void add(TupleValue *value);
  void add(const std::shared_ptr<TupleValue> &other);
  void add(int value);
  void add(float value);
  void add(const char *s, int len);
  void add(date_t value);
  void pop_back();

  const std::vector<std::shared_ptr<TupleValue>> &values() const {
    return values_;
  }

  std::vector<std::shared_ptr<TupleValue>> &raw_values() {
    return values_;
  }

  int size() const {
    return values_.size();
  }

  const TupleValue &get(int index) const {
    return *values_[index];
  }

  const std::shared_ptr<TupleValue> &get_pointer(int index) const {
    return values_[index];
  }

    void add_null();

private:
  std::vector<std::shared_ptr<TupleValue>>  values_;

};

class TupleField {
public:
  TupleField() {

  }
  TupleField(AttrType type, const char *table_name, const char *field_name) :
          type_(type), table_name_(table_name), field_name_(field_name){
  }

  AttrType  type() const{
    return type_;
  }

  const char *table_name() const {
    return table_name_.c_str();
  }
  const char *field_name() const {
    return field_name_.c_str();
  }

  std::string to_string() const;
private:
  AttrType  type_;
  std::string table_name_;
  std::string field_name_;
};

class TupleSchema {
public:
  TupleSchema() {}
  ~TupleSchema() = default;

  TupleSchema(const TupleSchema& schema) {
    fields_.resize(schema.fields_.size());
    std::copy(schema.fields_.begin(), schema.fields_.end(),fields_.begin());
  }

  void add(AttrType type, const char *table_name, const char *field_name);
  void add_if_not_exists(AttrType type, const char *table_name, const char *field_name);
  // void merge(const TupleSchema &other);
  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const {
    return fields_;
  }

  const TupleField &field(int index) const {
    return fields_[index];
  }

  int index_of_field(const char *table_name, const char *field_name) const;

  int index_of_field(const char *field_name) const;

  void clear() {
    fields_.clear();
  }

  void pop_back() {
    fields_.pop_back();
  }

  void print_content(std::ostream &os) const;
  void print(std::ostream &os) const;
  void mprint_content(std::ostream &os) const;
  void mprint(std::ostream &os) const;
public:
  static void from_table(const Table *table, TupleSchema &schema);

private:
  std::vector<TupleField> fields_;
};

class TupleSet {
public:
  TupleSet() = default;
  TupleSet(TupleSet &&other);
  explicit TupleSet(const TupleSchema &schema) : schema_(schema) {
  }

  TupleSet &operator =(TupleSet &&other);

  ~TupleSet() = default;

  void set_schema(const TupleSchema &schema);

  const TupleSchema &get_schema() const;

  void add(Tuple && tuple);

  void add_record(Tuple &tuple, TupleSchema &schema);

  void clear();

  bool is_empty() const;
  int size() const;
  const Tuple &get(int index) const;
  const std::vector<Tuple> &tuples() const;

  void print(std::ostream &os) const;

  void pop_row();

  void mprint(std::ostream &os);

  void sort_by_orders(std::vector<Order> &orders);

public:
  const TupleSchema &schema() const {
    return schema_;
  }
private:
  std::vector<Tuple> tuples_;
  TupleSchema schema_;

};

class TupleRecordConverter {
public:
  TupleRecordConverter(Table *table, TupleSet &tuple_set);

  void add_record(const char *record);
private:
  Table *table_;
  TupleSet &tuple_set_;
};

class AggSchema {
public:
  AggSchema() = default;

  void add(const AggDesc &agg_desc) { fields_.emplace_back(agg_desc); }
  void print_content(std::ostream &os) const;
  void print(std::ostream &os) const;
  const std::vector<AggDesc> &fields() const { return fields_; }

private:
  std::vector<AggDesc> fields_;
};

class AggTupleSet {
public:
  AggTupleSet() = default;
  AggSchema &schema() { return schema_; }
  void add(Tuple &&tuple) {
    tuples_.emplace_back(std::move(tuple));
  }
  void print(std::ostream &os) const;
  const std::vector<Tuple> &tuples() const { return tuples_; }
  void prune_null() {
    if (tuples_.empty()) {
      return;
    }
    Tuple &tuple = tuples_[0];
    bool clean = false;
    for (const auto& value : tuple.raw_values()) {
      if (value->is_null()) {
        clean = true;
        break;
      }
    }
    if (clean) {
      tuples_.pop_back();
    }
  }

private:
  AggSchema schema_;
  std::vector<Tuple> tuples_;
};

class GroupBySchema {
public:
  GroupBySchema() = default;

  void add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
    group_schema_.add_if_not_exists(type, table_name, field_name);
  }

  void add(const AggDesc &agg_desc) { agg_schema_.add(agg_desc); }
  const TupleSchema &group_schema() const { return group_schema_; }
  const AggSchema &agg_schema() const { return agg_schema_; }

  void print(std::ostream &os, const Selects &selects) const;

private:
  TupleSchema group_schema_;
  AggSchema agg_schema_;
};

class GroupByTupleSet {
public:
  GroupByTupleSet() = default;

  GroupBySchema &schema() { return schema_; }
  void add(Tuple &&tuple) {
    tuples_.emplace_back(std::move(tuple));
  }
  void print(std::ostream &os, const Selects &selects) const;

private:
  GroupBySchema schema_;
  std::vector<Tuple> tuples_;
};

#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
