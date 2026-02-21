module;

export module libyunpa:Point2;
export import std;

namespace libyunpa {
template <typename T>
  requires std::integral<T>
struct Point2 {
  T x;
  T y;

  constexpr auto operator==(const Point2<T>& other) const {
    return x == other.x and y == other.y;
  }

  constexpr auto operator+(const Point2<T>& other) const {
    return Point2<T>{x + other.x, y + other.y};
  }

  constexpr auto operator-(const Point2<T>& other) const {
    return Point2<T>{x - other.x, y - other.y};
  }

  constexpr auto operator-() const {
    return Point2<T>{-x, -y};
  }

  constexpr auto operator*(T scalar) const {
    return Point2<T>{x * scalar, y * scalar};
  }

  constexpr auto operator*(const Point2<T>& other) {
    return Point2{x * other.x, y * other.y};
  }
};

using Point2i = Point2<int>;
} // namespace libyunpa
