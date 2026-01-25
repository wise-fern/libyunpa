module;
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

export module libyunpa:Time;
import std;

namespace libyunpa {
export struct GameTime {
  sf::Time lastFrame;
  sf::Time totalElapsed;
};

export class Clock {
private:
  sf::Clock _clock;
  GameTime  _gameTime;

public:
  auto update() -> const GameTime& {
    _gameTime.lastFrame     = _clock.reset();
    _gameTime.totalElapsed += _gameTime.lastFrame;
    return _gameTime;
  }

  [[nodiscard]]
  auto getTime() const -> const GameTime& {
    return _gameTime;
  }

  void restart() {
    _gameTime = GameTime{};
    _clock.restart();
  }
};
} // namespace libyunpa
