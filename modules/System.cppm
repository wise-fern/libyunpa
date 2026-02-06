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

export using Point2ui = Point2<unsigned int>;

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
