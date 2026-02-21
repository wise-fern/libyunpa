module;

export module libyunpa:Drawable;
export import :Color;
export import :Point2;

namespace libyunpa {
export struct DrawableOptions {
  Color   color{.red = 255, .green = 255, .blue = 255};
  Color   bgColor{.red = 0, .green = 0, .blue = 0};
  Point2i position{1, 1};
};

export class Drawable {
private:
  Color   _color;
  Color   _bgColor;
  Point2i _position;

public:
  Drawable() : Drawable(DrawableOptions{}) {}

  Drawable(const DrawableOptions& options) :
      _color(options.color),
      _bgColor(options.bgColor),
      _position(options.position) {}

  auto set_color(Color color) {
    _color = color;
  }

  [[nodiscard]] auto get_color() const {
    return _color;
  }

  auto set_bg_color(Color color) {
    _bgColor = color;
  }

  [[nodiscard]] auto get_bg_color() const {
    return _bgColor;
  }

  auto setPosition(Point2i position) {
    _position = position;
  }

  [[nodiscard]] auto get_position() const {
    return _position;
  }

  virtual std::string to_string() = 0;
};
} // namespace libyunpa
