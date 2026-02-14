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
  bool        _dim;
  bool        _italic;
  bool        _underline;
  bool        _doubleUnderline;
  bool        _blink;
  bool        _inverse;
  bool        _invisible;
  bool        _struck;

public:
  Text(std::string text);
  Text(std::string text, const TextOptions& options);

  [[nodiscard]] auto getText() const;
  auto               setText(const std::string& text);
  [[nodiscard]] auto to_string() const -> std::string override;

  [[nodiscard]] auto getBold() const;
  auto               setBold(bool bold = true);
  [[nodiscard]] auto getDim() const;
  auto               setDim(bool dim = true);
  [[nodiscard]] auto getItalic() const;
  auto               setItalic(bool italic = true);
  [[nodiscard]] auto getUnderline() const;
  auto               setUnderline(bool underline = true);
  [[nodiscard]] auto getDoubleUnderline() const;
  auto               setDoubleUnderline(bool doubleUnderline = true);
  [[nodiscard]] auto getBlink() const;
  auto               setBlink(bool blink = true);
  [[nodiscard]] auto getInverse() const;
  auto               setInverse(bool inverse = true);
  [[nodiscard]] auto getInvisible() const;
  auto               setInvisible(bool invisible = true);
  [[nodiscard]] auto getStruck() const;
  auto               setStruck(bool struck = true);
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
    Drawable(options),
    _text(std::move(text)),
    _bold(options.bold),
    _dim(options.dim),
    _italic(options.italic),
    _underline(options.underline),
    _doubleUnderline(options.doubleUnderline),
    _blink(options.blink),
    _inverse(options.inverse),
    _invisible(options.invisible),
    _struck(options.struck) {}

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
  return std::format("{}\033[0m", result);
}

auto Text::getText() const {
  return _text;
}

auto Text::setText(const std::string& text) {
  _text = text;
}

auto Text::getDim() const {
  return _dim;
}

auto Text::setDim(bool dim) {
  _dim = dim;
}

auto Text::getItalic() const {
  return _italic;
}

auto Text::setItalic(bool italic) {
  _italic = italic;
}

auto Text::getUnderline() const {
  return _underline;
}

auto Text::setUnderline(bool underline) {
  _underline = underline;
}

auto Text::getDoubleUnderline() const {
  return _doubleUnderline;
}

auto Text::setDoubleUnderline(bool doubleUnderline) {
  _doubleUnderline = doubleUnderline;
}

auto Text::getBlink() const {
  return _blink;
}

auto Text::setBlink(bool blink) {
  _blink = blink;
}

auto Text::getInverse() const {
  return _inverse;
}

auto Text::setInverse(bool inverse) {
  _inverse = inverse;
}

auto Text::getInvisible() const {
  return _invisible;
}

auto Text::setInvisible(bool invisible) {
  _invisible = invisible;
}

auto Text::getStruck() const {
  return _struck;
}

auto Text::setStruck(bool struck) {
  _struck = struck;
}
} // namespace libyunpa
