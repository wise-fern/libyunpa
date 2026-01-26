module;
#ifdef WIN32
#include <conio.h>
#endif
#include <tao/pegtl.hpp>
export module libyunpa:Events;
import :Helpers;
import :Keyboard;
import std;

namespace libyunpa {
using namespace tao;

namespace Events {
/// @brief Represents a key press or release
export struct KeyEvent {
  /// @brief Whether this Event is a key press or release
  bool    isKeyDown;
  /// @brief Which input or function key was pressed
  Keys    key;
  /// @brief Which, if any, modifier keys were pressed
  KeyMods mods;
};
} // namespace Events

/// @brief Represents an Event for a game to process.
export using Event  = std::variant<std::monostate, Events::KeyEvent>;
using EventCallback = std::function<void(Event)>;

namespace Grammar {
struct ESC : pegtl::one<'\x1b'> {};

struct CSI : pegtl::seq<ESC, pegtl::one<'['>> {};

template <char delim = ';'>
struct DigitPlusTerm :
    pegtl::seq<pegtl::plus<pegtl::digit>, pegtl::one<delim>> {};

struct Win32InputString :
    pegtl::seq<CSI,
      DigitPlusTerm<>,
      DigitPlusTerm<>,
      DigitPlusTerm<>,
      DigitPlusTerm<>,
      DigitPlusTerm<>,
      DigitPlusTerm<'_'>> {};

struct Language : pegtl::sor<Win32InputString> {};
} // namespace Grammar

/// @brief An action struct
template <typename Rule>
struct Action {
  /// @brief An action function
  template <typename ActionInput>
  static auto apply(
    const ActionInput& actionInput, const EventCallback& callback) {
    (void)actionInput;
    (void)callback;
  }
};

/// @brief An action struct
template <>
struct Action<Grammar::Win32InputString> {
  /// @brief An action function
  template <typename ActionInput>
  static auto apply(
    const ActionInput& actionInput, const EventCallback& callback) {
    std::string inputString = actionInput.string();
    inputString             = inputString.substr(2);
    auto virtualKeyCode     = ConvertAndTrim(inputString);
    [[maybe_unused]]
    auto virtualScancode
      = ConvertAndTrim(inputString);
    [[maybe_unused]]
    auto unicodeCharValue
      = ConvertAndTrim(inputString);
    auto isKeyDown = ConvertAndTrim(inputString) == 1;

    auto event = Events::KeyEvent{.isKeyDown = isKeyDown,
      .key                                   = ConvertMSVK(virtualKeyCode),
      .mods                                  = KeyMods::NONE};
    callback(event);
  }
};

namespace Engine {
/// @brief Manages Events for a game
class EventManager {
  std::atomic_flag _running;
  std::thread      _eventThread;

  std::mutex        _eventQueueMutex;
  std::queue<Event> _eventQueue;

  auto enqueueEvent(Event event) -> void {
    std::lock_guard lock(_eventQueueMutex);
    _eventQueue.push(event);
  }

#ifdef WIN32
  auto eventLoop() {
    while (_running.test()) {
      std::string iString;
      while (_kbhit() not_eq 0) {
        auto input  = _getch();
        iString    += static_cast<char>(input);
      }
      if (iString.empty()) {
        continue;
      }
      auto parserInput = pegtl::memory_input(iString, "");
      auto callback    = [&](Event event) -> void {
        enqueueEvent(event);
      };
      pegtl::parse<Grammar::Language, Action>(parserInput, callback);
    }
  }
#else
  auto eventLoop() {}
#endif

public:
  /// @brief Start monitoring for Events
  auto start() {
    _running.test_and_set();
    _running.notify_all();
    _eventThread = std::thread(&EventManager::eventLoop, this);
  }

  /// @brief Stop monitoring for Events
  auto stop() {
    _running.clear();
    _running.notify_all();
    if (_eventThread.joinable()) {
      _eventThread.join();
    }
  }

  /// @brief Poll for events
  auto pollEvents() -> std::optional<Event> {
    std::lock_guard lock(_eventQueueMutex);
    if (_eventQueue.empty()) {
      return {};
    }
    auto result = _eventQueue.front();
    _eventQueue.pop();
    return result;
  }

  ~EventManager() {
    stop();
  }
};
} // namespace Engine
} // namespace libyunpa
