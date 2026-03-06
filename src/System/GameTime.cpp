module libyunpa;

namespace libyunpa {
void GameTime::reset() {
    lastFrame  = Duration::zero();
    totalTime  = Duration::zero();
    frameStart = TimePoint::clock::now();
}

void GameTime::update() {
    auto now{TimePoint::clock::now()};
    lastFrame   = now - frameStart;
    totalTime  += lastFrame;
    frameStart  = now;
}

Duration GameTime::get_last_frame() const {
    return lastFrame;
}

Duration GameTime::get_total_time() const {
    return totalTime;
}

} // namespace libyunpa
