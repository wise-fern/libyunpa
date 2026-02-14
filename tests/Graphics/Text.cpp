#include <gtest/gtest.h>

import libyunpa;

class Text : public testing::Test {
protected:
  libyunpa::Text _text;

  Text() : _text("A string of text!") {}
};

TEST_F(Text, GetText) {
  EXPECT_EQ(_text.getText(), "A string of text!");
}

TEST_F(Text, ToString) {
  auto result = std::format("{}\x1B[0m", "A string of text!");
  EXPECT_EQ(_text.to_string(), result);
}

TEST_F(Text, Bold) {
  EXPECT_EQ(false, _text.getBold());
  _text.setBold();
  EXPECT_EQ(true, _text.getBold());
  auto result = std::format("\x1b[1m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Dim) {
  EXPECT_EQ(false, _text.getDim());
  _text.setDim();
  EXPECT_EQ(true, _text.getDim());
  auto result = std::format("\x1b[2m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Italic) {
  EXPECT_EQ(false, _text.getItalic());
  _text.setItalic();
  EXPECT_EQ(true, _text.getItalic());
  auto result = std::format("\x1b[3m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Underline) {
  EXPECT_EQ(false, _text.getUnderline());
  _text.setUnderline();
  EXPECT_EQ(true, _text.getUnderline());
  auto result = std::format("\x1b[4m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, DoubleUnderline) {
  EXPECT_EQ(false, _text.getDoubleUnderline());
  _text.setDoubleUnderline();
  EXPECT_EQ(true, _text.getDoubleUnderline());
  auto result = std::format("\x1b[21m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Blink) {
  EXPECT_EQ(false, _text.getBlink());
  _text.setBlink();
  EXPECT_EQ(true, _text.getBlink());
  auto result = std::format("\x1b[5m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Inverse) {
  EXPECT_EQ(false, _text.getInverse());
  _text.setInverse();
  EXPECT_EQ(true, _text.getInverse());
  auto result = std::format("\x1b[7m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Invisible) {
  EXPECT_EQ(false, _text.getInvisible());
  _text.setInvisible();
  EXPECT_EQ(true, _text.getInvisible());
  auto result = std::format("\x1b[8m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}

TEST_F(Text, Struck) {
  EXPECT_EQ(false, _text.getStruck());
  _text.setStruck();
  EXPECT_EQ(true, _text.getStruck());
  auto result = std::format("\x1b[9m{}\x1b[0m", "A string of text!");
  EXPECT_EQ(result, _text.to_string());
}
