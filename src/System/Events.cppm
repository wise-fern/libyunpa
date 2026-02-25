module;
#ifdef WIN32
#else
#include <cstdio>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#undef CTRL
#endif
#include <tao/pegtl.hpp>
export module libyunpa:Events;
export import std;

#ifndef WIN32
namespace {
int _kbhit() {
  static const int STDIN = 0;
  static bool      initialized{false};

  if (not initialized) {
    termios term{};
    tcgetattr(STDIN, &term);
    term.c_lflag and_eq compl ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, nullptr);
    initialized = true;
  }
  int bytesWaiting{};
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}
} // namespace
#endif

namespace libyunpa {
export enum class Keys {
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_ESCAPE,
  KEY_SPACE,
  KEY_RETURN,
  KEY_BACKSPACE,
  KEY_INSERT,
  KEY_DELETE,
  KEY_HOME,
  KEY_END,
  KEY_PAGE_UP,
  KEY_PAGE_DOWN,
  KEY_ARROW_UP,
  KEY_ARROW_RIGHT,
  KEY_ARROW_DOWN,
  KEY_ARROW_LEFT,
  KEY_BACKTICK,
  KEY_TAB,
  KEY_HYPHEN,
  KEY_EQUALS,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KP_0,
  KP_1,
  KP_2,
  KP_3,
  KP_4,
  KP_5,
  KP_6,
  KP_7,
  KP_8,
  KP_9
};
export enum class KeyMods {
  NONE    = 0 << 0,
  ALT     = 1 << 0,
  SHIFT   = 1 << 1,
  CONTROL = 1 << 2,
  META    = 1 << 3,
  CTRL    = CONTROL
};

export auto operator|(KeyMods lhs, KeyMods rhs) {
  return static_cast<KeyMods>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

namespace Events {
export struct KeyEvent {
  bool    isKeyDown;
  Keys    key;
  KeyMods mods;
};
} // namespace Events

export using Event = std::variant<std::monostate, Events::KeyEvent>;

namespace Grammar {
using namespace tao::pegtl;

struct ESC : one<'\x1b'> {};

struct CSI : seq<ESC, one<'['>> {};

template <char delim = ';'>
struct DigitPlusTerm : seq<plus<digit>, one<delim>> {};

struct Win32Input : seq<CSI,
                        DigitPlusTerm<>,
                        DigitPlusTerm<>,
                        DigitPlusTerm<>,
                        DigitPlusTerm<>,
                        DigitPlusTerm<>,
                        DigitPlusTerm<'_'>> {};

struct Language : sor<Win32Input> {};
} // namespace Grammar

export class EventManager {
private:
  std::atomic_flag  _running;
  std::atomic_flag  _inputWaiting;
  std::thread       _monitor;
  std::mutex        _queueMutex;
  std::queue<Event> _eventQueue;

  auto enqueue_event(Event event) {
    std::lock_guard lock(_queueMutex);
    _eventQueue.push(event);
  }

  auto monitor_loop() {
    using namespace tao::pegtl;
    while (_running.test()) {
      _inputWaiting.wait(false);
      std::string workingString;
      while (_kbhit() not_eq 0) {
        auto input{std::cin.get()};
        workingString += static_cast<char>(input);
        auto parserInput{memory_input(workingString, "")};
        if (parse<Grammar::Language>(parserInput)) {
          workingString.clear();
        }
      }
      _inputWaiting.clear();
      if (workingString.empty()) {
        continue;
      }
      auto parserInput{memory_input(workingString, "")};
      parse<Grammar::Language>(parserInput);
    }
  }

public:
  auto start() {
    _running.test_and_set();
    _running.notify_all();
    _inputWaiting.clear();
    _inputWaiting.notify_all();
    _monitor = std::thread(&EventManager::monitor_loop, this);
  }

  auto stop() {
    _running.clear();
    _running.notify_all();
    if (_monitor.joinable()) {
      _monitor.join();
    }
  }

  auto update() {
    if (_kbhit() not_eq 0) {
      _inputWaiting.test_and_set();
      _inputWaiting.notify_all();
    }
  }

  auto poll_events() {
    std::lock_guard lock(_queueMutex);
    if (_eventQueue.empty()) {
      return std::optional<Event>{};
    }
    auto result = _eventQueue.front();
    _eventQueue.pop();
    return std::optional<Event>{result};
  }
};
} // namespace libyunpa
