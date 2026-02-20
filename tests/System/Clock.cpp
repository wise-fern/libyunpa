#include <gtest/gtest.h>

import libyunpa;

TEST(Clock, Update) {
  libyunpa::Clock clock{};
  auto            originalTime = clock.getGameTime();
  auto            updatedTime  = clock.update();
  EXPECT_GE(updatedTime.totalTime, originalTime.totalTime);
}
