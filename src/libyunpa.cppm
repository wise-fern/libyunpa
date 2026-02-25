export module libyunpa;
// Engine
export import :Scene;
export import :SceneManager;

// System
export import :Events;
export import :Time;

namespace libyunpa {
export class Core {
private:
  Core() = default;
  static std::unique_ptr<Core> _instance;

public:
  static auto &get_instance() {
    if (_instance == nullptr) {
      _instance.reset(new Core());
    }
    return *_instance;
  }

  Core(Core &)             = delete;
  Core(Core &&)            = delete;
  Core &operator=(Core &)  = delete;
  Core &operator=(Core &&) = delete;
  ~Core()                  = default;

private:
  Clock        _clock;
  EventManager _eventMan;
  SceneManager _sceneMan;

  auto game_loop() -> void;

public:
  auto run() -> void;
  auto set_next_scene(ScenePtr nextScene) -> void;
};
} // namespace libyunpa
