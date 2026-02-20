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
} // namespace libyunpa
