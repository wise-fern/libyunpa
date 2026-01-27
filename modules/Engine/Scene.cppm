module;

export module libyunpa:Scene;
import :Events;
import :Keyboard;
import :Time;
import ftxui;
import std;

namespace libyunpa::Engine {
#pragma region Scene
export class Scene;
/// @brief A pointer to a Scene
export using ScenePtr = std::shared_ptr<Scene>;

/// @brief A discrete segment of a game
export class Scene {
private:
  ScenePtr _parent;
  bool     _wantsExit = false;

protected:
  /// @brief Indicate that the Scene wants to exit
  auto requestExit() {
    _wantsExit = true;
  }

public:
  /// @brief Construct a Scene with the given @a parent
  Scene(ScenePtr parent) : _parent(std::move(parent)) {}

  Scene() : Scene(nullptr) {}

  virtual ~Scene() = default;

  /// @brief Called before another Scene is placed on top of this one on the
  /// scene stack
  virtual void onBury() {}

  /// @brief Called after the Scene on top of this one is popped off the stack
  /// and this Scene is reactivated
  virtual void onReveal() {}

  /// @brief Update the Scene
  /// @param[in] gameTime
  virtual void update(const GameTime& gameTime) {
    (void)gameTime;
  }

  /// @brief Handle a key press or release event
  /// @param[in] event
  virtual void handleEvent(const Events::KeyEvent& event) = 0;

  /// @brief Render the Scene
  [[nodiscard]]
  virtual auto render() const -> ftxui::Element
    = 0;

  /// @brief Get the Scene's parent Scene
  [[nodiscard]]
  auto getParent() const {
    return _parent;
  }

  /// @brief Check whether this Scene wants to exit
  [[nodiscard]]
  auto wantsExit() const {
    return _wantsExit;
  }
};

#pragma region Manager

template <typename... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

/// @brief Manages @ref Scene Scenes for a game
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
  /// @brief Set the next Scene to run
  /// @param[in] nextScene
  auto setNextScene(ScenePtr nextScene) {
    _nextScene = std::move(nextScene);
  }

  /// @brief Get a copy of the currently active Scene's ScenePtr
  [[nodiscard]]
  auto getCurrentScene() const {
    if (_scenes.empty()) {
      return ScenePtr{};
    }
    return _scenes.top();
  }

  /// @brief Update the active Scene
  /// @todo Finish documentation
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

  /// @brief Handles a key press or release event
  /// @param[in] event
  /// @details Handles distributing a std::variant to active Scene
  auto handleEvent(const Event& event) {
    if (_scenes.empty()) {
      return;
    }
    auto scene   = _scenes.top();
    auto handler = Overload{[](std::monostate) -> void {},
      [&scene](Events::KeyEvent event) -> void {
        scene->handleEvent(event);
      }};
    try {
      event.visit(handler);
    } catch (std::bad_variant_access& except) {
      (void)except;
    }
  }

  /// @brief Check whether there are any @ref Scene Scenes on the scene stack
  [[nodiscard]]
  auto empty() const {
    return _scenes.empty();
  }

  /// @brief Check whether there is another Scene waiting to be activated
  [[nodiscard]]
  auto hasNext() const {
    return _nextScene not_eq nullptr;
  }

  auto fullExit() {
    while (not _scenes.empty()) {
      _scenes.pop();
    }
  }
};
} // namespace libyunpa::Engine
