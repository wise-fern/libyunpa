module;

export module libyunpa:Time;
import std;

namespace libyunpa {
using namespace std;
/// @brief An interval of time
export using Duration = chrono::duration<long double, std::milli>;

/// @brief A point in time
export using TimePoint = chrono::time_point<chrono::steady_clock, Duration>;

namespace {
constexpr auto ZERO_TIME = chrono::milliseconds(0);
}

/// @brief Options to use when constructing a timer
export struct TimerOptions {
  /// @brief The interval on whic @a callback is called
  Duration              interval;
  /// @brief Whether to run the timer again after @a interval has expired
  bool                  repeat;
  /// @brief The function to call when @a interval expires
  std::function<void()> callback;
};

/// @brief Tracks time for a game
export class GameTime {
private:
  Duration  _lastFrame;
  Duration  _totalElapsedTime;
  TimePoint _frameStart;

public:
  GameTime() :
      _lastFrame(ZERO_TIME),
      _totalElapsedTime(ZERO_TIME),
      _frameStart(chrono::steady_clock::now()) {}

  /// @brief Get the last frame
  /// @returns A Duration object with the time it took to update and render the
  /// previous frame
  [[nodiscard]]
  auto getLastFrame() const -> const Duration& {
    return _lastFrame;
  }

  /// @brief Get the total time
  /// @returns A Duration object with the time since the game was started
  [[nodiscard]]
  auto getTotalTime() const -> const Duration& {
    return _totalElapsedTime;
  }

  /// @brief Reset the internal clocks
  void reset() {
    _lastFrame        = ZERO_TIME;
    _totalElapsedTime = ZERO_TIME;
    _frameStart       = chrono::steady_clock::now();
  }

  /// @brief Update the internal clocks
  void update() {
    auto now           = chrono::steady_clock::now();
    _lastFrame         = now - _frameStart;
    _totalElapsedTime += _lastFrame;
    _frameStart        = now;
  }
};

/// @brief Handles doing things on an interval
export class Timer {
private:
  Duration              _interval;
  Duration              _elapsed = ZERO_TIME;
  bool                  _active  = true;
  bool                  _repeats;
  std::function<void()> _callback;

public:
  /// @brief Construct a new timer with the given options
  /// @param[in] options
  Timer(const TimerOptions& options) :
      _interval(options.interval),
      _repeats(options.repeat),
      _callback(options.callback) {}

  /// @brief Update the timer
  /// @param[in] elapsed
  void update(const Duration& elapsed) {
    if (not _active) {
      return;
    }
    _elapsed += elapsed;
    if (_elapsed >= _interval) {
      _elapsed = ZERO_TIME;
      _active  = _repeats;
      _callback();
    }
  }

  /// @overload
  void update(const GameTime& gameTime) {
    update(gameTime.getLastFrame());
  }

  /// @brief Set whether the timer is active or not
  void setActive(bool active) {
    _active = active;
  }

  /// @brief Set the timer to be active
  void activate() {
    setActive(true);
  }

  /// @brief Set the timer to be inactive
  void deactivate() {
    setActive(false);
  }

  /// @brief Set whether the timer repeats
  void setRepeats(bool repeats) {
    _repeats = repeats;
  }

  /// @brief Set the interval for the timer
  void setInterval(Duration interval) {
    _interval = interval;
  }
};
} // namespace libyunpa
