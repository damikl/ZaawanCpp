#include <gtest/gtest.h>
#include "number.h"

TEST(Number,nwd) {
  Number num = Number(42);
  Number num2;
  Number num3 = Number(14);

  EXPECT_EQ(14,num.nwd(56));
  EXPECT_EQ(21,num.nwd(21));
  EXPECT_EQ(42,num.nwd(0));
  EXPECT_EQ(78,num2.nwd(78));
  EXPECT_EQ(2,num.nwd(-4));
}

TEST(Number,nww)
{
  Number num = Number(42);

  EXPECT_EQ(168,num.nww(56));
  EXPECT_EQ(42,num.nww(1));
}
