module;

export module libyunpa:Color;

namespace libyunpa {
export struct Color {
  unsigned int red   : 8;
  unsigned int green : 8;
  unsigned int blue  : 8;

  constexpr auto operator==(const Color& other) const {
    return red == other.red and green == other.green and blue == other.blue;
  }

  constexpr auto operator+(const Color& other) const {
    return Color{.red = static_cast<unsigned int>(red + other.red),
                 .green = static_cast<unsigned int>(green + other.green),
                 .blue = static_cast<unsigned int>(blue + other.blue)};
  }

  constexpr auto operator-(const Color& other) const {
    return Color{.red = static_cast<unsigned int>(red - other.red),
                 .green = static_cast<unsigned int>(green - other.green),
                 .blue = static_cast<unsigned int>(blue - other.blue)};
  }
};
} // namespace libyunpa
