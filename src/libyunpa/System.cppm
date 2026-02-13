module;

export module libyunpa.System;
import std;

namespace libyunpa {
export template <typename T>
  requires std::integral<T>
struct Point2 {
  T x;
  T y;
};

export template <typename T>
  requires std::integral<T>
constexpr auto operator+(Point2<T> lhs, Point2<T> rhs) {
  return Point2<T>{lhs.x + rhs.x, lhs.y + rhs.y};
}

export template <typename T>
  requires std::integral<T>
constexpr auto operator==(Point2<T> lhs, Point2<T> rhs) {
  return lhs.x == rhs.x and lhs.y == rhs.y;
}

export template <typename T>
  requires std::integral<T>
constexpr auto operator-(Point2<T> point) {
  return Point2<T>{-point.x, -point.y};
}

export template <typename T>
  requires std::integral<T>
constexpr auto operator-(Point2<T> lhs, Point2<T> rhs) {
  return Point2<T>{lhs.x - rhs.x, lhs.y - rhs.y};
}

export template <typename T>
  requires std::integral<T>
constexpr auto operator*(Point2<T> lhs, Point2<T> rhs) {
  return Point2<T>{lhs.x * rhs.x, lhs.y * rhs.y};
}

export template <typename T>
  requires std::integral<T>
constexpr auto operator*(Point2<T> lhs, T rhs) {
  return Point2<T>{.x = lhs.x * rhs, .y = lhs.y * rhs};
}

export template <typename T>
  requires std::integral<T>
constexpr auto operator/(Point2<T> lhs, Point2<T> rhs) {
  return Point2<T>{.x = lhs.x / rhs.x, .y = lhs.y / rhs.y};
}

export using Point2i = Point2<int>;

} // namespace libyunpa

module :private;
