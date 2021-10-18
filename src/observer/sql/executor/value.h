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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <cstring>

#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <ctime>

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

private:
  int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
//    os << value_;
      std::stringstream ss;
      ss << std::fixed << std::setprecision(2)<< value_;
      std::string str = ss.str();
      while ((str.find('.') != std::string::npos &&
            str.substr(str.length() - 1, 1) == "0")
            || str.substr(str.length() - 1, 1) == ".") {
        str.pop_back();
      }
      os << str;
  }

  int compare(const TupleValue &other) const override {
    const auto & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (std::abs(result) < 1e-7)
      return 0;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    return -1;
  }
private:
  float value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }
private:
  std::string value_;
};

typedef unsigned int date_t;

class DateValue : public TupleValue {
public:

  /**
   * construct a DateValue
   * should first invoke validation, this will also construct a date_data parameter
   * @param value days since 1970.01.01
   */
  explicit DateValue(date_t value)
    : value(value) {
      init_str(value);
    }

  void to_string(std::ostream &os) const override {
    os << str;
  }

  int compare(const TupleValue &other) const override {
    const auto &date_value = static_cast<const DateValue &>(other);
    return static_cast<int>(value - date_value.value);
  }

  /**
   * validate string format.
   * Since the validation involves a transformation, resulted Y-M-D
   * may be required or not, which is used to construct d DateValue.
   * @param value date string to validate
   * @param t out tm result. set nullptr if not to construct a DateValue instance
   * @return whether the date string is legal
   */
  static bool validate_data_format(const char *value, tm *t);

  static date_t to_raw_data(tm *t);
  static void from_raw_data(date_t days, tm *t);

private:
  void init_str(date_t days);

  date_t value;
  char str[12];
};

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
