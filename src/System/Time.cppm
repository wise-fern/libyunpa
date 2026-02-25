export module libyunpa:Time;
export import std;

namespace libyunpa {
export using Duration = std::chrono::duration<long double, std::milli>;
export using TimePoint =
    std::chrono::time_point<std::chrono::steady_clock, Duration>;

export struct GameTime {
  Duration lastFrame{Duration::zero()};
  Duration totalTime{Duration::zero()};
};

export class Clock {
private:
  GameTime  _gameTime;
  TimePoint _frameStart{TimePoint::clock::now()};

public:
  auto get_last_frame() const {
    return _gameTime.lastFrame;
  }

  auto get_total_time() const {
    return _gameTime.totalTime;
  }

  const auto &get_game_time() const {
    return _gameTime;
  }

  auto update() {
    auto now{TimePoint::clock::now()};
    _gameTime.lastFrame  = now - _frameStart;
    _gameTime.totalTime += _gameTime.lastFrame;
    _frameStart          = now;
  }

  auto reset() {
    _gameTime.lastFrame = Duration::zero();
    _gameTime.totalTime = Duration::zero();
    _frameStart         = TimePoint::clock::now();
  }
};
} // namespace libyunpa
