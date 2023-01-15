#include <gtest/gtest.h>

#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

TEST(IPFilterTest, SplitTest) {

  ip_type_s ip {split("", '.')};
  ASSERT_EQ(ip.size(), 1);
  EXPECT_STREQ(ip[0].c_str(), "");

  ip = split("11", '.');
  ASSERT_EQ(ip.size(), 1);
  EXPECT_STREQ(ip[0].c_str(), "11");

  ip = split("..", '.');
  ASSERT_EQ(ip.size(), 3);
  EXPECT_STREQ(ip[0].c_str(), "");
  EXPECT_STREQ(ip[1].c_str(), "");
  EXPECT_STREQ(ip[2].c_str(), "");

  ip = split("11.", '.');
  ASSERT_EQ(ip.size(), 2);
  EXPECT_STREQ(ip[0].c_str(), "11");
  EXPECT_STREQ(ip[1].c_str(), "");

  ip = split(".11", '.');
  ASSERT_EQ(ip.size(), 2);
  EXPECT_STREQ(ip[0].c_str(), "");
  EXPECT_STREQ(ip[1].c_str(), "11");

  ip = split("11.22", '.');
  ASSERT_EQ(ip.size(), 2);
  EXPECT_STREQ(ip[0].c_str(), "11");
  EXPECT_STREQ(ip[1].c_str(), "22");

}

TEST(IPFilterTest, ValidityCheck) {
  ip_type_s ip {split("255.255.255.255", '.')};
  EXPECT_EQ(is_valid_ip(ip), true) << "Valid IP rejected";

  ip = split("256.0.0.0", '.');
  EXPECT_EQ(is_valid_ip(ip), false) << "value > 255 allowed";

  ip = split("-1.0.0.0", '.');
  EXPECT_EQ(is_valid_ip(ip), false) << "negative value allowed";

  ip = split("tr.am.ta.ram", '.');
  EXPECT_EQ(is_valid_ip(ip), false) << "non-digits allowed";

}

