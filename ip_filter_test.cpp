#include <gtest/gtest.h>

#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using namespace std;

TEST(IPFilterTest, SplitTest) {

  ip_type ip {split("", '.')};
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
