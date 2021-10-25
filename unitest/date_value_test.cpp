
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
  auto str1 = "2021-2-29";
  ASSERT_FALSE(DateValue::validate_data_format(str1, nullptr));

  auto str2 = "202x-10-19";
  ASSERT_FALSE(DateValue::validate_data_format(str2, nullptr));

  auto str3 = "2020--19";
  ASSERT_FALSE(DateValue::validate_data_format(str3, nullptr));

  auto str4 = "2020";
  ASSERT_FALSE(DateValue::validate_data_format(str4, nullptr));

  auto str5 = "2020-13-07";
  ASSERT_FALSE(DateValue::validate_data_format(str5, nullptr));

  auto str6 = "2020-3-33";
  ASSERT_FALSE(DateValue::validate_data_format(str6, nullptr));
}

#include <ctime>

int main(int argc, char **argv) {
  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果
  return RUN_ALL_TESTS();
}
