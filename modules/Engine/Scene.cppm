module;
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

export module libyunpa:Scene;
import :Time;
import std;

namespace libyunpa {
export class Scene;
export using ScenePtr = std::shared_ptr<Scene>;

export class Scene : public sf::Drawable {
private:
  ScenePtr _parent;
  bool     _wantsExit = false;

protected:
  auto requestExit() {
    _wantsExit = true;
  }

public:
  Scene(ScenePtr parent) : _parent(std::move(parent)) {}

  Scene() : Scene(nullptr) {}

  Scene(const Scene&) = default;
  Scene(Scene&&)      = default;

  virtual ~Scene() = default;

  auto operator=(const Scene&) -> Scene& = default;
  auto operator=(Scene&&) -> Scene&      = default;

  virtual void handleEvent(const sf::Event& event) = 0;

  virtual void update([[maybe_unused]] const GameTime& gameTime) {}

  virtual void onBury() {}

  virtual void onReveal() {}

  [[nodiscard]]
  auto getParent() const {
    return _parent;
  }

  [[nodiscard]]
  auto wantsExit() const {
    return _wantsExit;
  }
};

#pragma region Manager

export class SceneManager : public sf::Drawable {
private:
  ScenePtr             _nextScene = nullptr;
  std::stack<ScenePtr> _scenes;

  void popScene() {
    if (_scenes.empty()) {
      return;
    }
    _scenes.pop();
    if (_scenes.empty()) {
      return;
    }
    _scenes.top()->onReveal();
  }

  void transitionScene() {
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
  void setNextScene(ScenePtr nextScene) {
    _nextScene = std::move(nextScene);
  }

  [[nodiscard]]
  auto getCurrentScene() const -> ScenePtr {
    if (_scenes.empty()) {
      return nullptr;
    }
    return _scenes.top();
  }

  void update(const GameTime& gameTime) {
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

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(*_scenes.top(), states);
  }

  void handleEvent(const sf::Event& event) {
    if (_scenes.empty()) {
      return;
    }
    _scenes.top()->handleEvent(event);
  }

  [[nodiscard]]
  auto empty() const -> bool {
    return _scenes.empty();
  }
};
} // namespace libyunpa
