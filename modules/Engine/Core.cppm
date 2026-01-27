module;
#ifdef WIN32
#include <windows.h>
#endif
export module libyunpa:Core;
import :Events;
import :Keyboard;
import :Scene;
import :Time;
import ftxui;
import std;

namespace libyunpa::Engine {
/// @brief Central class for coordinating a game.
export class Core {
  class impl {
  private:
    GameTime      _gameTime;
    EventManager  _eventMan;
    SceneManager  _sceneMan;
    ftxui::Screen _screen;
    bool          _fullExit        = false;
    bool          _fullExitEnabled = false;

    // NOLINTNEXTLINE(misc-no-recursion)
    auto render(const ScenePtr& scene) {
      if (scene == nullptr) {
        return;
      }
      render(scene->getParent());
      ftxui::Render(_screen, scene->render());
    }

    auto gameLoop() {
      while (true) {
        if (_fullExitEnabled and _fullExit) {
          _sceneMan.fullExit();
          return;
        }
        _fullExitEnabled = false;
        _gameTime.update();
        _sceneMan.update(_gameTime);
        if (_sceneMan.empty()) {
          return;
        }
        while (auto event = _eventMan.pollEvents()) {
          if (not event.has_value()) {
            continue;
          }
          auto realEvent = event.value();
          _sceneMan.handleEvent(realEvent);
        }
        _screen.Clear();
        render(_sceneMan.getCurrentScene());
        std::cout << std::format("\x1b[1;1H{}", _screen.ToString());
      }
    }

  public:
    impl() : _screen(ftxui::Screen::Create(ftxui::Dimension::Full())) {
      using enum DecModes;
#ifdef WIN32
      HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
      DWORD  mode   = (ENABLE_EXTENDED_FLAGS
                     bitor ENABLE_WINDOW_INPUT
                     bitor ENABLE_MOUSE_INPUT
                     bitor ENABLE_PROCESSED_INPUT
                     bitor ENABLE_VIRTUAL_TERMINAL_INPUT)
            bitand compl(ENABLE_ECHO_INPUT bitor ENABLE_QUICK_EDIT_MODE);
      SetConsoleMode(handle, mode);

      handle = GetStdHandle(STD_OUTPUT_HANDLE);
      mode   = (ENABLE_PROCESSED_OUTPUT
              bitor ENABLE_VIRTUAL_TERMINAL_PROCESSING
              bitor DISABLE_NEWLINE_AUTO_RETURN);
      SetConsoleMode(handle, mode);
      DECSET(WIN32_INPUT_MODE);
#else
#endif
      DECSET(APPLICATION_KEYPAD_MODE);
      DECSET(APPLICATION_CURSOR_KEYS);
      DECSET(ANY_EVENT_MOUSE_TRACKING);
      DECSET(SGR_MOUSE_MODE);
      DECRST(SHOW_CURSOR);
    }

    auto setNextScene(ScenePtr nextScene) {
      _sceneMan.setNextScene(std::move(nextScene));
    }

    auto getCurrentScene() {
      return _sceneMan.getCurrentScene();
    }

    auto run() {
      _eventMan.start();
      _gameTime.reset();
      gameLoop();
      _eventMan.stop();
    }

    auto fullExit() {
      _fullExit = true;
    }

    auto enableFullExit() {
      _fullExitEnabled = true;
    }
  };

  static std::unique_ptr<impl> _instance;
  static bool                  _initialized;

public:
  /// @brief Initialize the Core.
  /// @details This must be called before any other operations can be performed
  /// on the Core.
  static void Initialize() noexcept {
    if (_initialized) {
      return;
    }
    _initialized = true;
    _instance    = std::make_unique<impl>();
  }

  /// @brief Set the next Scene to run
  /// @param[in] nextScene
  static void SetNextScene(ScenePtr nextScene) noexcept {
    _instance->setNextScene(std::move(nextScene));
  }

  ///@brief Get the currently active Scene
  static auto GetCurrentScene() noexcept -> ScenePtr {
    return _instance->getCurrentScene();
  }

  /// @brief Run the game
  static void Run() noexcept {
    _instance->run();
  }

  static void FullExit() noexcept {
    _instance->fullExit();
  }

  static void EnableFullExit() noexcept {
    _instance->enableFullExit();
  }
};

bool Core::_initialized = false;

std::unique_ptr<Core::impl> Core::_instance = nullptr;
static_assert(noexcept(Core::Run));
} // namespace libyunpa::Engine
