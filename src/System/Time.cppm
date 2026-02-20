module;

export module libyunpa.System:Time;
export import std;

using namespace std::chrono;

namespace libyunpa {
export using Duration  = duration<long double, std::milli>;
export using TimePoint = time_point<steady_clock, Duration>;

export struct GameTime {
  Duration lastFrame;
  Duration totalTime;
};

export class Clock {
private:
  GameTime  _gameTime{};
  TimePoint _frameStart{steady_clock::now()};

public:
  const auto& update() {
    auto now             = steady_clock::now();
    _gameTime.lastFrame  = now - _frameStart;
    _gameTime.totalTime += _gameTime.lastFrame;
    _frameStart          = now;
    return _gameTime;
  }

  [[nodiscard]] const auto& getGameTime() const {
    return _gameTime;
  }

  auto reset() {
    _gameTime.lastFrame = Duration::zero();
    _gameTime.totalTime = Duration::zero();
    _frameStart         = steady_clock::now();
  }
};
} // namespace libyunpa
