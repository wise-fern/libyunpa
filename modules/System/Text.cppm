module;

export module libyunpa:Text;
import ftxui;
import std;

namespace libyunpa {
/// @brief Styles of underline to use with text
export enum class Underline : std::uint8_t {
  None,
  Single,
  Double
};

/// @brief Options to use when rendering some text
export struct TextOptions {
  /// @brief Color to use for the text
  ftxui::Color color = ftxui::Color::White;
  /// @brief Color to use for the background
  ftxui::Color backgroundColor = ftxui::Color::Black;
  /// @brief Whether to @b bold the text
  bool bold = false;
  /// @brief Whether to @a italicize the text
  bool italic = false;
  /// @brief Whether to dim the text
  bool dim = false;
  /// @brief Whether to invert the text and background colors
  bool inverted = false;
  /// @brief the style of underline to use
  Underline underline = Underline::None;
  /// @brief Whether to render the text with a strikethrough
  bool strikethrough = false;
  /// @brief Whether to have the text blinke
  bool blink = false;
};

auto RenderText(const TextOptions& options, const std::string& input)
  -> ftxui::Element {
  using namespace ftxui;
  auto result
    = text(input) | color(options.color) | bgcolor(options.backgroundColor);
  if (options.bold) {
    result = result | bold;
  }
  if (options.italic) {
    result = result | italic;
  }
  if (options.dim) {
    result = result | dim;
  }
  if (options.inverted) {
    result = result | inverted;
  }
  switch (options.underline) {
  case Underline::None  : break;
  case Underline::Single: result = result | underlined; break;
  case Underline::Double: result = result | underlinedDouble; break;
  }
  if (options.strikethrough) {
    result = result | strikethrough;
  }
  if (options.blink) {
    result = result | blink;
  }
  return result;
}
} // namespace libyunpa
