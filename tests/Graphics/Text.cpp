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
  auto result = std::format("{}\e[0m", GetParam());
  EXPECT_EQ(_text.to_string(), result);
}

TEST_P(TextTests, Bold) {
  EXPECT_EQ(false, _text.getBold());
  _text.setBold();
  EXPECT_EQ(true, _text.getBold());
  auto result = std::format("\x1b[1m{}\x1b[0m", GetParam());
  EXPECT_EQ(result, _text.to_string());
}

TEST_P(TextTests, Italic) {
  EXPECT_EQ(false, _text.getItalic());
  _text.setItalic();
  EXPECT_EQ(true, _text.getItalic());
  auto result = std::format("\x1b[2m{}\x1b[0m", GetParam());
  EXPECT_EQ(result, _text.to_string());
}

TEST_P(TextTests, Underline) {
  EXPECT_EQ(false, _text.getUnderline());
  _text.setUnderline();
  EXPECT_EQ(true, _text.getUnderline());
  auto result = std::format("\x1b[3m{}\x1b[0m", GetParam());
  EXPECT_EQ(result, _text.to_string());
}

TEST_P(TextTests, DoubleUnderline) {
  EXPECT_EQ(false, _text.getDoubleUnderline());
  _text.setDoubleUnderline();
  EXPECT_EQ(true, _text.getDoubleUnderline());
  auto result = std::format("\x1b[21m{}\x1b[0m", GetParam());
  EXPECT_EQ(result, _text.to_string());
}

TEST_P(TextTests, Blink) {
  EXPECT_EQ(false, _text.getBlink());
  _text.setBlink();
  EXPECT_EQ(true, _text.getBlink());
  auto result = std::format("\x1b[5{}\x1b[0m", GetParam());
  EXPECT_EQ(result, _text.to_string());
}

INSTANTIATE_TEST_SUITE_P(Graphics,
                         TextTests,
                         testing::Values("test",
                                         "A string for you",
                                         "some more Text"));
