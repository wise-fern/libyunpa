module libyunpa;
import std;

namespace libyunpa {
auto Core::game_loop() -> void {
  while (true) {
    _eventMan.update();
    _clock.update();
    return;
  }
}

auto Core::run() -> void {
  _clock.reset();
  game_loop();
}

auto Core::set_next_scene(ScenePtr nextScene) -> void {
  _sceneMan.set_next_scene(std::move(nextScene));
}
} // namespace libyunpa
