module;

export module libyunpa.Graphics;
export import libyunpa.System;
import std;

namespace libyunpa {
export struct Color {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;
};

constexpr auto UINT8T_MAX = 255;

export struct DrawableOptions {
  Color   color = {.red = UINT8T_MAX, .green = UINT8T_MAX, .blue = UINT8T_MAX};
  Color   bgColor  = {.red = 0, .green = 0, .blue = 0};
  Point2i position = {.x = 1, .y = 1};
};

export class Drawable {
private:
  Color   _color;
  Color   _bgColor;
  Point2i _position;

public:
  Drawable();
  Drawable(const DrawableOptions& options);
  Drawable(const Drawable&) = default;
  Drawable(Drawable&&)      = default;
  virtual ~Drawable()       = default;

  auto operator=(const Drawable&) -> Drawable& = default;
  auto operator=(Drawable&&) -> Drawable&      = default;

  [[nodiscard]] virtual auto to_string() const -> std::string = 0;

  [[nodiscard]] auto getColor() const;
  auto               setColor(Color color);
  [[nodiscard]] auto getBackground() const;
  auto               setBackground(Color bgColor);
  [[nodiscard]] auto getPosition() const;
  auto               setPosition(Point2i position);
  auto               draw() const;
};

export struct TextOptions : public DrawableOptions {
  bool bold            = false;
  bool dim             = false;
  bool italic          = false;
  bool underline       = false;
  bool doubleUnderline = false;
  bool blink           = false;
  bool inverse         = false;
  bool invisible       = false;
  bool struck          = false;
};

export class Text : public Drawable {
private:
  std::string _text;
  bool        _bold;

public:
  Text(std::string text);
  Text(std::string text, const TextOptions& options);

  [[nodiscard]] auto getBold() const;
  auto               setBold(bool bold);
  [[nodiscard]] auto getText() const;
  auto               setText(const std::string& text);
  [[nodiscard]] auto to_string() const -> std::string override;
};
} // namespace libyunpa

module :private;

namespace libyunpa {
#pragma region Drawable

Drawable::Drawable() : Drawable(DrawableOptions{}) {}

Drawable::Drawable(const DrawableOptions& options) :
    _color(options.color),
    _bgColor(options.bgColor),
    _position(options.position) {}

auto Drawable::getColor() const {
  return _color;
}

auto Drawable::setColor(Color color) {
  _color = color;
}

auto Drawable::getBackground() const {
  return _bgColor;
}

auto Drawable::setBackground(Color bgColor) {
  _bgColor = bgColor;
}

auto Drawable::getPosition() const {
  return _position;
}

auto Drawable::setPosition(Point2i position) {
  _position = position;
}

auto Drawable::draw() const {
  std::cout << std::format(
      "\033[{};{}H{}", _position.y, _position.x, to_string());
}

#pragma region Text

Text::Text(std::string text) : Text(std::move(text), TextOptions{}) {}

Text::Text(std::string text, const TextOptions& options) :
    Drawable(options), _text(std::move(text)), _bold(options.bold) {}

auto Text::getBold() const {
  return _bold;
}

auto Text::setBold(bool bold) {
  _bold = bold;
}

auto Text::to_string() const -> std::string {
  auto position = getPosition();
  auto result   = _text;
  if (_bold) {
    result = std::format("\033[1m{}", result);
  }
  return std::format("\033[{};{}H{}\033[0m", position.y, position.x, result);
}

auto Text::getText() const {
  return _text;
}

auto Text::setText(const std::string& text) {
  _text = text;
}
} // namespace libyunpa
