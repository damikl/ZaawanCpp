#include "number.h"
#include <gtest/gtest.h>

// Tests the putDigit() method.
TEST(Number, putDigit) {
  Number num = Number(2);
  Number num2;

  // EXPECT_EQ() evaluates its arguments exactly once, so they
  // can have side effects.

  EXPECT_EQ(2, num.putDigit(3));
  EXPECT_EQ(23, num.putDigit(4));
  EXPECT_EQ(234, num.putDigit(5));

  EXPECT_EQ(0, num2.putDigit(0));
  EXPECT_EQ(0, num2.putDigit(3));
  EXPECT_EQ(3, num2.putDigit(4));

}
