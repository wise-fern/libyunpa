module;

export module libyunpa.System;
export import std;

namespace libyunpa {
export using Duration = std::chrono::duration<long double, std::milli>;
export using TimePoint
  = std::chrono::time_point<std::chrono::steady_clock, Duration>;

export struct GameTime {
  Duration lastFrame = Duration::zero();
  Duration totalTime = Duration::zero();
};

export template <typename T>
  requires std::integral<T>
struct Point2 {
  T x;
  T y;
};

export template <typename T>
  requires std::integral<T>
Point2<T> operator+(const Point2<T>& lhs, const Point2<T>& rhs) {
  return Point2<T>{.x = lhs.x + rhs.x, .y = lhs.y + rhs.y};
}

export template <typename T>
  requires std::integral<T>
Point2<T> operator-(const Point2<T>& lhs, const Point2<T>& rhs) {
  return Point2<T>{.x = lhs.x - rhs.x, .y = lhs.y - rhs.y};
}

export template <typename T, typename U>
  requires std::integral<T> and (std::integral<U> or std::floating_point<U>)
Point2<T> operator*(Point2<T> point, U scalar) {
  return Point2<T>{.x = point.x * scalar, .y = point.y * scalar};
}

export template <typename T, typename U>
  requires std::integral<T> and (std::integral<U> or std::floating_point<U>)
Point2<T> operator/(Point2<T> point, U scalar) {
  return Point2<T>{.x = point.x / scalar, .y = point.y / scalar};
}

export template <typename T>
  requires std::integral<T>
Point2<T> operator==(const Point2<T>& lhs, const Point2<T>& rhs) {
  return lhs.x == rhs.x and lhs.y == rhs.y;
}

export using Point2i = Point2<int>;

export template <typename T>
  requires std::integral<T>
struct Point3 {
  T x;
  T y;
  T z;
};

export template <typename T>
  requires std::floating_point<T>
struct Vector2 {
  T x;
  T y;
};

export template <typename T>
  requires std::floating_point<T>
struct Vector3 {
  T x;
  T y;
  T z;
};

export class Clock {
private:
  TimePoint _lastUpdate = std::chrono::steady_clock::now();
  Duration  _totalTime;

public:
  auto update() {
    auto     now        = std::chrono::steady_clock::now();
    Duration lastFrame  = now - _lastUpdate;
    _totalTime         += lastFrame;
    _lastUpdate         = now;
    return GameTime{.lastFrame = lastFrame, .totalTime = _totalTime};
  }

  auto reset() {
    _lastUpdate = std::chrono::steady_clock::now();
    _totalTime  = Duration::zero();
  }
};

} // namespace libyunpa
