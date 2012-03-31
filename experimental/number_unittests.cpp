#include <gtest/gtest.h>
#include "number.h"

// Tests the putDigit() method.
TEST(Number, putDigit) {
  Number num = Number(2);
  Number num2;

  // EXPECT_EQ() evaluates its arguments exactly once, so they
  // can have side effects.

  EXPECT_EQ(23, num.putDigit(3));
  EXPECT_EQ(234, num.putDigit(4));
  EXPECT_EQ(2345, num.putDigit(5));

  EXPECT_EQ(0, num2.putDigit(0));
  EXPECT_EQ(6, num2.putDigit(6));
  EXPECT_EQ(67, num2.putDigit(7));

}



