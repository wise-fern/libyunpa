export module libyunpa:Time;
export import std;

namespace libyunpa {
using namespace std::chrono;
export using Duration  = duration<long double, std::ratio<1, 1>>;
export using TimePoint = time_point<steady_clock, Duration>;

export class GameTime {
private:
    Duration  lastFrame{Duration::zero()};
    Duration  totalTime{Duration::zero()};
    TimePoint frameStart{TimePoint::clock::now()};

public:
    void update();
    void reset();

    [[nodiscard]]
    Duration get_last_frame() const;
    [[nodiscard]]
    Duration get_total_time() const;
};
} // namespace libyunpa
