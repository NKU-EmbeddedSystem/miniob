
#include <ostream>
#include <string>
#include <sstream>

#include "gtest/gtest.h"
#include "sql/executor/value.h"

using std::ostream;
using std::ostringstream;
using std::string;

TEST(dateTest, validTests) {
  auto valid_str = "2021-10-19";
  tm t;
  ASSERT_TRUE(DateValue::validate_data_format(valid_str, &t));
  ASSERT_EQ(t.tm_year, 121);
  ASSERT_EQ(t.tm_mon, 9);
  ASSERT_EQ(t.tm_mday, 19);
  date_t d = DateValue::to_raw_data(&t);
  DateValue v1(d);
  ostringstream s1;
  v1.to_string(s1);
  ASSERT_EQ(s1.str(), valid_str);

  auto valid_str_zero = "1972-07-02";
  ASSERT_TRUE(DateValue::validate_data_format(valid_str_zero, &t));
  d = DateValue::to_raw_data(&t);
  DateValue v2(d);
  ostringstream s2;
  v2.to_string(s2);
  ASSERT_EQ(s2.str(), valid_str_zero);
}

TEST(dateTest, invalidTests) {
  auto str1 = "202x-10-19";
  ASSERT_FALSE(DateValue::validate_data_format(str1, nullptr));

  auto str2 = "2020--19";
  ASSERT_FALSE(DateValue::validate_data_format(str2, nullptr));

  auto str3 = "2020";
  ASSERT_FALSE(DateValue::validate_data_format(str3, nullptr));

  auto str4 = "2020-13-07";
  ASSERT_FALSE(DateValue::validate_data_format(str4, nullptr));

  auto str5 = "2020-3-33";
  ASSERT_FALSE(DateValue::validate_data_format(str5, nullptr));
}

#include <ctime>

int main(int argc, char **argv) {
//  auto dstr = "1970-02-30";
//  tm t;
//
//  memset(&t, 0, sizeof(t));
//  auto ret = strptime(dstr, "%Y-%m-%d", &t);
//  printf("ret: %p\n", ret);
//  printf("%d %d %d\n", t.tm_year, t.tm_mon, t.tm_mday);
//
//  time_t time = mktime(&t);
//  time /= 3600;
//  time += 8;
//  time /= 24;
//  printf("%ld\n", time);
//
//  time *= (24 * 3600);
//  tm *gmt = gmtime(&time);
//  tm *localt = localtime(&time);
//
//  printf("gmt: %d %d %d\n", gmt->tm_year, gmt->tm_mon, gmt->tm_mday);
//  printf("localt: %d %d %d\n", localt->tm_year, localt->tm_mon, localt->tm_mday);
//
//  char buff[12];
//  auto r = strftime(buff, 12, "%Y-%m-%d\n", gmt);
//  printf("%s", buff);
//
//  r = strftime(buff, 12, "%Y-%m-%d\n", localt);
//  printf("%s", buff);

  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果
  return RUN_ALL_TESTS();
}
