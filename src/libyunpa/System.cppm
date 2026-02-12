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

} // namespace libyunpa

module :private;

