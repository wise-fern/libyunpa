module;

export module libyunpa.Engine;
export import libyunpa.Console;
export import libyunpa.System;
export import ftxui;
import std;

namespace libyunpa {
export class Scene;
export using ScenePtr = std::shared_ptr<Scene>;
#pragma region Scene

export class Scene {
private:
  ScenePtr _parent    = nullptr;
  bool     _wantsExit = false;

protected:
  auto requestExit() {
    _wantsExit = true;
  }

public:
  Scene(ScenePtr parent) : _parent(std::move(parent)) {}

  Scene()          = default;
  virtual ~Scene() = default;

  virtual void onBury() {}

  virtual void onReveal() {}

  virtual void update(const GameTime& gameTime)           = 0;
  virtual void handleEvent(const Events::KeyEvent& event) = 0;
  [[nodiscard]]
  virtual auto render() const -> ftxui::Element
    = 0;

  [[nodiscard]]
  auto getParent() const {
    return _parent;
  }

  [[nodiscard]]
  auto wantsExit() const {
    return _wantsExit;
  }
};

#pragma region SceneMan

template <typename... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

class SceneManager {
private:
  ScenePtr             _nextScene = nullptr;
  std::stack<ScenePtr> _scenes;

  auto popScene() {
    if (_scenes.empty()) {
      return;
    }
    _scenes.pop();
    if (_scenes.empty()) {
      return;
    }
    _scenes.top()->onReveal();
  }

  auto transitionScene() {
    if (_nextScene == nullptr) {
      return;
    }
    if (not _scenes.empty()) {
      _scenes.top()->onBury();
    }
    _scenes.push(_nextScene);
    _nextScene = nullptr;
  }

public:
  auto update(const GameTime& gameTime) {
    if (_scenes.empty() and _nextScene == nullptr) {
      return;
    }
    if (not _scenes.empty() and _scenes.top()->wantsExit()) {
      popScene();
    }
    if (_nextScene not_eq nullptr) {
      transitionScene();
    }
    if (_scenes.empty()) {
      return;
    }
    _scenes.top()->update(gameTime);
  }

  auto handleEvent(const Event& event) {
    auto handler = Overload{[](std::monostate) {},
      [&](const Events::KeyEvent& event) {
        _scenes.top()->handleEvent(event);
      }};
    event.visit(handler);
  }

  [[nodiscard]]
  auto getCurrentScene() const {
    if (not _scenes.empty()) {
      return _scenes.top();
    }
    return ScenePtr{};
  }

  auto setNextScene(ScenePtr nextScene) {
    _nextScene = std::move(nextScene);
  }

  [[nodiscard]]
  auto empty() const {
    return _scenes.empty();
  }

  [[nodiscard]]
  auto render() const {
    if (not _scenes.empty()) {
      return _scenes.top()->render();
    }
    return ftxui::text("No Scenes");
  }
};

#pragma region Core

export class Core {
private:
  static std::unique_ptr<Core> _instance;
  static bool                  _initialized;
  Core() = default;

  SceneManager _sceneMan;
  EventManager _eventMan;
  Clock        _clock;

  auto gameLoop() {
    while (true) {
      _sceneMan.update(_clock.update());
      if (_sceneMan.empty()) {
        return;
      }
      while (auto event = _eventMan.pollEvents()) {
        _sceneMan.handleEvent(event.value());
      }
      auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
      ftxui::Render(screen, _sceneMan.render());
      std::cout << std::format("\x1b[1;1H{}", screen.ToString());
    }
  }

  auto run() {
    _eventMan.start();
    _clock.reset();
    gameLoop();
  }

  auto setNextScene(ScenePtr nextScene) {
    _sceneMan.setNextScene(std::move(nextScene));
  }

  [[nodiscard]]
  auto getCurrentScene() const {
    return _sceneMan.getCurrentScene();
  }

public:
  static auto Initialize() {
    if (_initialized) {
      return;
    }
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    _instance.reset(new Core());
  }

  static auto SetNextScene(ScenePtr nextScene) {
    _instance->setNextScene(std::move(nextScene));
  }

  static auto GetCurrentScene() {
    return _instance->getCurrentScene();
  }

  static auto Run() {
    _instance->run();
  }
};

std::unique_ptr<Core> Core::_instance = nullptr;

bool Core::_initialized = false;
} // namespace libyunpa
