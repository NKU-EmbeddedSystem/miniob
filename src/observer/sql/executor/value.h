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

class DateValue : public TupleValue {
public:

  /**
   * construct a DateValue
   * should first invoke validation, this will also construct a date_data parameter
   * @param date_data [0] = year, [1] = month, [2] = day
   */
  explicit DateValue(const int date_data[3]) {
    year = date_data[0];
    month = date_data[1];
    day = date_data[2];
  }

  void to_string(std::ostream &os) const override {
    if (year < 1000) {
      os << '0';
      if (year < 100) {
        os << '0';
        if (year < 10) {
          os << '0';
        }
      }
    }
    os << year << '-';

    if (month < 10) {
      os << '0';
    }
    os << month << '-';

    if (day < 10) {
      os << '0';
    }
    os << day;
  }

  int compare(const TupleValue &other) const override {
    const DateValue &date_value = static_cast<const DateValue &>(other);
    if (year != date_value.year) {
      return year - date_value.year;
    } else if (month != date_value.month) {
      return month - date_value.month;
    } else {
      return day - date_value.day;
    }
  }

  /**
   * validate string format.
   * Since the validation involves a transformation, resulted Y-M-D
   * may be required or not, which is used to construct d DateValue.
   * @param value date string to validate
   * @param date_data resulted Y-M-D. set nullptr if not to construct a DateValue instance
   * @return whether the date string is legal
   */
  static bool validate_data_format(const char *value, int date_data[3]) {
    // dump parameter if the resulted Y-M-D is not required
    int tmp[3];
    return transform(value, (date_data == nullptr) ? tmp : date_data);
  }

private:
  static bool transform(const char *value, int date_data[3]) {
    if (value == nullptr) {
      return false;
    }

    int start = 0, end = 0;
    for (int i = 0; i < 2; i++) {
      // find next '-' or '\0'
      while (value[end] != '-' && value[end] != '\0') {
        end++;
      }

      // first two int shouldn't end with '\0'
      if (end == '\0') {
        return false;
      }

      // transform to int
      if (!str2int(value, start, end, &date_data[i])) {
        return false;
      }

      start = ++end;
    }

    while (value[end] != '\0') {
      end++;
    }

    if (!str2int(value, start, end, &date_data[2])) {
      return false;
    }

    // got date_data[year, month, day]
    // now validate
    if (date_data[0] > 2038
        || date_data[1] > 12
        || date_data[2] > 31
        || date_data[0] == 0
        || date_data[1] == 0
        || date_data[2] == 0) {
      return false;
    }

    return true;
  }

  static bool str2int(const char *value, int start, int end, int *date_data) {
    // empty string
    if (start == end) {
      return false;
    }

    int num = 0;
    char digit;
    while (start != end) {
      digit = value[start++];

      // check digit char
      if (digit < '0' || digit > '9') {
        return false;
      }

      num *= 10;
      num += (digit - '0');
    }

    *date_data = num;
    return true;
  }

  int year;
  int month;
  int day;
};

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
