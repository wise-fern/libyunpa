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
    Clock _clock;
    SceneManager _sceneMan;
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
    impl(const sf::VideoMode &mode, const sf::String &title) {
      _window.create(mode, title);
    }

    void setNextScene(ScenePtr nextScene) noexcept {
      _sceneMan.setNextScene(std::move(nextScene));
    }

    [[nodiscard]]
    auto getCurrentScene() const noexcept -> ScenePtr {
      return _sceneMan.getCurrentScene();
    }

    void run() noexcept {
      _clock.restart();
      gameLoop();
    }
  };

  static std::unique_ptr<impl> _instance;
  static bool _initialized;

public:
  static void Initialize(const sf::VideoMode &mode,
                         const sf::String &title) noexcept {
    if (_initialized) {
      return;
    }
    _initialized = true;
    _instance = std::make_unique<impl>(mode, title);
  }

  static void Initialize(unsigned int width, unsigned int height,
                         const sf::String &title) noexcept {
    Initialize(sf::VideoMode({width, height}), title);
  }

  static void SetNextScene(ScenePtr nextScene) noexcept {
    _instance->setNextScene(std::move(nextScene));
  }

  static auto GetCurrentScene() noexcept -> ScenePtr {
    return _instance->getCurrentScene();
  }

  static void Run() noexcept { _instance->run(); }
};

bool Core::_initialized = false;
std::unique_ptr<Core::impl> Core::_instance = nullptr;
} // namespace libyunpa::Engine
