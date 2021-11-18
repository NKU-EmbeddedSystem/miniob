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
  virtual TupleValue *result() const = 0;
  virtual void reset() = 0;
  const AggDesc &desc() const { return agg_desc_; }
  static RC check_operand_type_match_agg_type(const AggDesc &agg_desc);
  static RC check_field_type_match_agg_type(const AggDesc &agg_desc, const AttrType &attr_type);

private:
  const AggDesc &agg_desc_;
};

class CountAggregator: public Aggregator {
public:
  explicit CountAggregator(const AggDesc &agg_desc)
    : Aggregator(agg_desc), cnt_(0)
    { }

  void consume(const Tuple &tuple) override {
    if (tuple.size() == 1 && tuple.get(0).is_null())
      return;
    cnt_++;
  }

  TupleValue *result() const override { return new IntValue(cnt_); }
  void reset() override { cnt_ = 0; }

private:
  int cnt_;
};

class ConstAggregator: public Aggregator {
public:
  ConstAggregator(const AggDesc &agg_desc, int const_val)
    : Aggregator(agg_desc), const_val_(const_val)
    { }

  void consume(const Tuple &tuple) override { }
  TupleValue *result() const override { return new IntValue(const_val_); }
  void reset() override { }

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
    if (tuple.get(pos_).is_null())
      return;
    const TupleValue *other = &tuple.get(pos_);
    if (max_ == nullptr || max_->compare(*other) < 0) {
      max_ = other;
    }
  }

  TupleValue *result() const override {
    if (max_ == nullptr)
      return new NullValue();
    return max_->clone();
  }

  void reset() override { max_ = nullptr; }

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
    if (other->is_null())
      return;
    if (min_ == nullptr || min_->compare(*other) > 0) {
      min_ = other;
    }
  }

  TupleValue *result() const override {
    if (min_ == nullptr) {
      return new NullValue();
    }
    return min_->clone();
  }

  void reset() override { min_ = nullptr; }

private:
  const TupleValue *min_;
};

class AvgAggregator: public FieldAggregator {
private:
  typedef void (AvgAggregator::*acc_value_func_t)(const TupleValue &value);
public:
  AvgAggregator(const AggDesc &agg_desc, int pos, AttrType attr_type)
    : FieldAggregator(agg_desc, pos), cnt_(0), int_sum_(0), attr_type_(attr_type),
      acc_value_(attr_type == INTS
        ? &AvgAggregator::acc_int
        : &AvgAggregator::acc_float)
    { }

  void consume(const Tuple &tuple) override {
    if (tuple.get(pos_).is_null())
      return;
    (this->*acc_value_)(tuple.get(pos_));
    cnt_++;
  }

  TupleValue *result() const override {
    if (is_null || cnt_ == 0)
      return new NullValue();

    if (attr_type_ == INTS) {
      return new FloatValue(((float)int_sum_) / cnt_);
    } else {
      return new FloatValue(float_sum_ / cnt_);
    }
  }

  void reset() override { cnt_ = 0; int_sum_ = 0; }

private:
  void acc_int(const TupleValue &value) {
    is_null = false;
    int_sum_ += static_cast<const IntValue &>(value).get_value();
  }

  void acc_float(const TupleValue &value) {
    is_null = false;
    float_sum_ += static_cast<const FloatValue &>(value).get_value();
  }

  int cnt_;
  union {
    int int_sum_;
    float float_sum_;
  };
  bool is_null = true;
  AttrType attr_type_;
  acc_value_func_t acc_value_;
};

#endif //MINIDB_AGGREGATOR_H
