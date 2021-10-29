//
// Created by Light-Laptop on 2021/10/27.
//

#ifndef MINIDB_AGGREGATOR_H
#define MINIDB_AGGREGATOR_H

#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "tuple.h"

class Aggregator {
public:
  explicit Aggregator(const AggDesc &agg_desc)
    : agg_desc_(agg_desc)
    { }

  virtual ~Aggregator() = default;

  virtual void consume(const Tuple &tuple) = 0;
  virtual const TupleValue *result() const = 0;
  const AggDesc &desc() const { return agg_desc_; }
  static RC check_operand_type_match_agg_type(const AggDesc &agg_desc);
  static RC check_field_type_match_agg_type(const AggDesc &agg_desc, const AttrType &attr_type);

private:
  const char *make_agg_field_name();

  static const char *agg_type_names[];

  const AggDesc &agg_desc_;
};

class CountAggregator: public Aggregator {
public:
  explicit CountAggregator(const AggDesc &agg_desc)
    : Aggregator(agg_desc), cnt_(0)
    { }

  void consume(const Tuple &tuple) override { cnt_++; }
  const TupleValue *result() const override { return new IntValue(cnt_); }

private:
  int cnt_;
};

class ConstAggregator: public Aggregator {
public:
  ConstAggregator(const AggDesc &agg_desc, int const_val)
    : Aggregator(agg_desc), const_val_(const_val)
    { }

  void consume(const Tuple &tuple) override { }
  const TupleValue *result() const override { return new IntValue(const_val_); }

private:
  int const_val_;
};

class FieldAggregator: public Aggregator {
public:
  FieldAggregator(const AggDesc &agg_desc, int pos)
    : Aggregator(agg_desc), pos_(pos)
    { }

protected:
  int pos_;
};

class MaxAggregator: public FieldAggregator {
public:
  MaxAggregator(const AggDesc &agg_desc, int pos)
    : FieldAggregator(agg_desc, pos), max_(nullptr)
    { }

  void consume(const Tuple &tuple) override {
    const TupleValue *other = &tuple.get(pos_);
    if (max_ == nullptr || max_->compare(*other) < 0) {
      max_ = other;
    }
  }

  // bug?
  const TupleValue *result() const override { return max_->clone(); }

private:
  const TupleValue *max_;
};

class MinAggregator: public FieldAggregator {
public:
  MinAggregator(const AggDesc &agg_desc, int pos)
    : FieldAggregator(agg_desc, pos), min_(nullptr)
  { }

  void consume(const Tuple &tuple) override {
    const TupleValue *other = &tuple.get(pos_);
    if (min_ == nullptr || min_->compare(*other) > 0) {
      min_ = other;
    }
  }

  // bug?
  const TupleValue *result() const override { return min_->clone(); }

private:
  const TupleValue *min_;
};

class AvgAggregator: public FieldAggregator {
private:
  typedef void (AvgAggregator::*acc_value_func_t)(const TupleValue &value);
public:
  AvgAggregator(const AggDesc &agg_desc, int pos, AttrType attr_type)
    : FieldAggregator(agg_desc, pos), cnt_(0), attr_type_(attr_type),
      acc_value_(attr_type == INTS
        ? &AvgAggregator::acc_int
        : &AvgAggregator::acc_float)
    { }

  void consume(const Tuple &tuple) override {
    (this->*acc_value_)(tuple.get(pos_));
    cnt_++;
  }

  const TupleValue *result() const override {
    if (attr_type_ == INTS) {
      return new IntValue(int_sum_ / cnt_);
    } else {
      return new FloatValue(float_sum_ / cnt_);
    }
  }

private:
  void acc_int(const TupleValue &value) {
    int_sum_ += static_cast<const IntValue &>(value).get_value();
  }

  void acc_float(const TupleValue &value) {
    float_sum_ += static_cast<const FloatValue &>(value).get_value();
  }

  int cnt_;
  union {
    int int_sum_ = 0;
    float float_sum_;
  };
  AttrType attr_type_;
  acc_value_func_t acc_value_;
};

#endif //MINIDB_AGGREGATOR_H
