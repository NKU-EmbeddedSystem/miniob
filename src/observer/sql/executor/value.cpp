/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <ctime>

#include "value.h"

bool DateValue::validate_data_format(const char *value, tm *t) {
  tm dumpy;
  tm *tptr = (t == nullptr) ? &dumpy : t;

  memset(tptr, 0, sizeof(tm));

  return strptime(value, "%Y-%m-%d", tptr) != nullptr
         && check_date_manually(tptr);
}

static bool big_month[12] = {
        true, false, true, false,
        true, false, true, true,
        false, true, false, true
};

bool DateValue::check_date_manually(const tm *t) {
  int year = t->tm_year + 1900;
  int month = t->tm_mon;
  int day = t->tm_mday;

  // only permit 1970 later
  if (year < 1970) {
    return false;
  }

  if (!big_month[month]) {
    // normal small month
    if (month != 1) {
      return day <= 30;
    } else { // lunar check
      bool lunar = ((year % 4) == 0);
      return lunar
            ? (day <= 29)
            : (day <= 28);
    }
  }

  return true;
}

bool DateValue::check_date_with_syscall(const tm *t) {
  tm t_clone = *t;
  time_t time = mktime(&t_clone);
  time += (8 * 3600);
  gmtime_r(&time, &t_clone);
  return t->tm_mon == t_clone.tm_mon && t->tm_mday == t_clone.tm_mday;
}
date_t DateValue::to_raw_data(tm *t) {
  time_t time = mktime(t);

  time /= 3600;
  time += 8;
  time /= 24;

  return static_cast<date_t>(time);
}

void DateValue::from_raw_data(date_t days, tm *t) {
  time_t secs = days * (24 * 3600);
  memset(t, 0, sizeof(t));

  gmtime_r(&secs, t);
}

void DateValue::init_str(date_t days) {
  tm t;
  from_raw_data(days, &t);
  strftime(str_, sizeof(str_), "%Y-%m-%d", &t);
}