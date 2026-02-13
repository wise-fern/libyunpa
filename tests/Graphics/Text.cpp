#include <gtest/gtest.h>

import libyunpa;

class TextTests : public testing::TestWithParam<std::string> {
protected:
  libyunpa::Text _text;

  TextTests() : _text(GetParam()) {}
};

TEST_P(TextTests, GetText) {
  EXPECT_EQ(_text.getText(), GetParam());
}

TEST_P(TextTests, ToString) {
  auto result = std::format("\033[1;1H{}\033[0m", GetParam());
  EXPECT_EQ(_text.to_string(), result);
}

INSTANTIATE_TEST_SUITE_P(Graphics,
                         TextTests,
                         testing::Values("test",
                                         "A string for you",
                                         "some more Text"));
