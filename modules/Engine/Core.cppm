module;
#include <SFML/Graphics/RenderWindow.hpp>
export module libyunpa:Core;
import :Scene;
import :Time;
import std;

namespace libyunpa::Engine {
/// @brief Central class for coordinating a game.
export class Core {
private:
  class impl {
  private:
    Clock            _clock;
    SceneManager     _sceneMan;
    sf::RenderWindow _window;

    void gameLoop() {
      while (true) {
        _sceneMan.update(_clock.update());
        if (_sceneMan.empty()) {
          return;
        }
        while (auto event = _window.pollEvent()) {
          _sceneMan.handleEvent(event.value());
        }
        _window.clear(sf::Color::Black);
        _window.draw(_sceneMan);
        _window.display();
      }
    }

  public:
    impl(const sf::VideoMode& mode, const sf::String& title) {
      _window.create(mode, title);
    }

    void setNextScene(ScenePtr nextScene) {
      _sceneMan.setNextScene(std::move(nextScene));
    }

    [[nodiscard]]
    auto getCurrentScene() const -> ScenePtr {
      return _sceneMan.getCurrentScene();
    }

    void run() {
      _clock.restart();
      gameLoop();
    }
  };

  static std::unique_ptr<impl> _instance;
  static bool                  _initialized;

public:
  static void Initialize(const sf::VideoMode& mode, const sf::String& title) {
    if (_initialized) {
      return;
    }
    _initialized = true;
    _instance    = std::make_unique<impl>(mode, title);
  }

  static void Initialize(
    unsigned int width, unsigned int height, const sf::String& title) {
    Initialize(sf::VideoMode({width, height}), title);
  }

  static void SetNextScene(ScenePtr nextScene) {
    _instance->setNextScene(std::move(nextScene));
  }

  static auto GetCurrentScene() -> ScenePtr {
    return _instance->getCurrentScene();
  }

  static void Run() {
    _instance->run();
  }
};
} // namespace libyunpa::Engine
