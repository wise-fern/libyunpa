#include <gtest/gtest.h>

// NOLINTBEGIN(*magic-numbers)

import libyunpa;

class Color : public testing::Test {
protected:
  libyunpa::Color       lhs   = {.red = 30, .green = 30, .blue = 30};
  libyunpa::Color       rhs   = {.red = 100, .green = 100, .blue = 100};
  const libyunpa::Color WHITE = {.red = 255, .green = 255, .blue = 255};
  const libyunpa::Color BLACK = {.red = 0, .green = 0, .blue = 0};
};

TEST_F(Color, Equality) {
  EXPECT_TRUE(lhs == lhs);
  EXPECT_TRUE(rhs == rhs);
  EXPECT_FALSE(rhs == lhs);
}

// NOLINTEND(*magic-numbers)
