export module libyunpa:SceneManager;
export import :Events;
export import :Scene;
export import :Time;
export import std;

namespace libyunpa {
export class SceneManager {
private:
  ScenePtr             _nextScene;
  std::stack<ScenePtr> _scenes;

  auto pop_scene() {
    if (_scenes.empty()) {
      return;
    }
    _scenes.pop();
    if (_scenes.empty()) {
      return;
    }
    _scenes.top()->on_reveal();
  }

  auto transition_scene() {
    if (_nextScene == nullptr) {
      return;
    }
    if (not _scenes.empty()) {
      _scenes.top()->on_bury();
    }
    _scenes.push(std::move(_nextScene));
    _nextScene = nullptr;
  }

public:
  auto set_next_scene(ScenePtr nextScene) {
    _nextScene = std::move(nextScene);
  }

  auto get_current_scene() const {
    if (_scenes.empty()) {
      return ScenePtr{};
    }
    return _scenes.top();
  }

  auto update(const GameTime &gameTime) {
    if (not _scenes.empty() and _scenes.top()->wants_exit()) {
      pop_scene();
    }
    if (_nextScene not_eq nullptr) {
      transition_scene();
    }
    if (_scenes.empty()) {
      return;
    }
    _scenes.top()->update(gameTime);
  }

  auto handle_event(const Event &event) {
    (void)event;
  }
};
} // namespace libyunpa
