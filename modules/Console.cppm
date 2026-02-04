module;
#include <tao/pegtl.hpp>
#ifdef WIN32
#include <conio.h>
#include <windows.h>
#endif
export module libyunpa.Console;
import std;

namespace libyunpa {
export enum class Keys : std::int8_t;
auto ConvertAndTrim(std::string& input, char delim = ';') -> int;
auto ConvertMSVK(int keyCode) -> Keys;
auto ConvertCharacter(char input) -> Keys;

#pragma region DECMODE
export enum class DecMode : std::uint16_t {
  ApplicationCursorKeys = 1,
  SmoothScroll          = 4,
  AutoRepeatKeys        = 8,
  ShowCursor            = 25,
  ApplicationKeypadMode = 66,
  AnyEventTracking      = 1003,
  SendFocusEvents       = 1004,
  SGRMouseMode          = 1006,
  UseAlternateBuffer    = 1049,
  WindowsInputMode      = 9001
};

export auto DECSET(DecMode mode) {
  std::cout << std::format("\x1b[?{}h", std::to_underlying(mode));
}

export auto DECRST(DecMode mode) {
  std::cout << std::format("\x1b[?{}l", std::to_underlying(mode));
}

#pragma region Enums

export enum class Keys : std::int8_t {
  MISSING_KEY = -1,
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
  // NOLINTNEXTLINE(misc-confusable-identifiers)
  KEY_0,
  // NOLINTNEXTLINE(misc-confusable-identifiers)
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
  KEY_DELETE,
  KEY_INSERT,
  KEY_HOME,
  KEY_END,
  KEY_PAGE_UP,
  KEY_PAGE_DOWN,
  KEY_ARROW_UP,
  KEY_ARROW_RIGHT,
  KEY_ARROW_DOWN,
  KEY_ARROW_LEFT,
  KEY_TAB,
  KEY_BACKSPACE,
  KEY_RETURN,
  KEY_SPACE,
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

export enum class KeyMods : std::uint8_t {
  NONE    = 0 << 0,
  SHIFT   = 1 << 0,
  CTRL    = 1 << 1,
  ALT     = 1 << 2,
  CONTROL = CTRL
};

export KeyMods operator|(KeyMods lhs, KeyMods rhs) {
  return static_cast<KeyMods>(
    static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

export enum class Button : std::uint8_t {
  NONE,
  LEFT,
  MIDDLE,
  RIGHT,
  BACK,
  FORWARD,
  SCROLL_UP,
  SCROLL_DOWN
};

#pragma region Events

namespace Events {
export struct KeyEvent {
  bool    isKeyDown;
  Keys    key;
  KeyMods mods;
};

export struct MouseEvent {
  int    xCoord;
  int    yCoord;
  bool   isPress;
  Button button;
};
} // namespace Events

export using Event = std::variant<std::monostate, Events::KeyEvent>;

namespace Grammar {
using namespace tao;

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

using EventCallback = std::function<void(Event)>;
#pragma region Action

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

#pragma region EventManager

export class EventManager {
  std::atomic_flag _running;
  std::thread      _monitor;

  std::mutex        _queuetex;
  std::queue<Event> _eventQueue;

  auto _enqueueEvent(Event event) {
    std::lock_guard lock(_queuetex);
    _eventQueue.push(event);
  }

  auto _monitorLoop() {
    using namespace tao;
    _running.wait(false);
    while (_running.test()) {
      std::string workingString;
      while (_kbhit() not_eq 0) {
        auto input     = _getch();
        workingString += static_cast<char>(input);
      }
      if (workingString.empty()) {
        continue;
      }
      auto parserInput = pegtl::memory_input(workingString, "");
      pegtl::parse<Grammar::Language, Action>(parserInput, [&](Event event) {
        _enqueueEvent(event);
      });
    }
  }

public:
  EventManager() {
    using enum DecMode;
#ifdef WIN32
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  mode   = (ENABLE_PROCESSED_INPUT
                   bitor ENABLE_WINDOW_INPUT
                   bitor ENABLE_MOUSE_INPUT
                   bitor ENABLE_EXTENDED_FLAGS
                   bitor ENABLE_VIRTUAL_TERMINAL_INPUT)
          bitand compl(ENABLE_QUICK_EDIT_MODE bitor ENABLE_ECHO_INPUT);
    SetConsoleMode(handle, mode);

    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    mode   = (ENABLE_PROCESSED_OUTPUT
            bitor ENABLE_VIRTUAL_TERMINAL_PROCESSING
            bitor DISABLE_NEWLINE_AUTO_RETURN);
    SetConsoleMode(handle, mode);
    DECSET(WindowsInputMode);
#endif
    DECSET(ApplicationKeypadMode);
    DECRST(SmoothScroll);
    DECRST(AutoRepeatKeys);
    DECRST(ShowCursor);
    DECSET(ApplicationKeypadMode);
    DECSET(AnyEventTracking);
    DECSET(SendFocusEvents);
    DECSET(SGRMouseMode);
    DECSET(UseAlternateBuffer);
  }

  auto start() {
    _running.test_and_set();
    _running.notify_all();
    _monitor = std::thread(&EventManager::_monitorLoop, this);
  }

  auto stop() {
    _running.clear();
    _running.notify_all();
    if (_monitor.joinable()) {
      _monitor.join();
    }
  }

  auto pollEvents() {
    if (_eventQueue.empty()) {
      return std::optional<Event>{};
    }
    auto result = _eventQueue.front();
    _eventQueue.pop();
    return std::optional<Event>(result);
  }

  ~EventManager() {
    stop();
  }
};
} // namespace libyunpa

#pragma region Private

module :private;

namespace libyunpa {

#pragma region ConvMSVK

auto ConvertMSVK(int keyCode) -> Keys {
  switch (keyCode) {
    using enum Keys;
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  default : return ConvertCharacter(static_cast<char>(keyCode));
#ifdef WIN32
  case VK_RETURN : return KEY_RETURN;
  case VK_SPACE  : return KEY_SPACE;
  case VK_NUMPAD0: return KP_0;
  case VK_NUMPAD1: return KP_1;
  case VK_NUMPAD2: return KP_2;
  case VK_NUMPAD3: return KP_3;
  case VK_NUMPAD4: return KP_4;
  case VK_NUMPAD5: return KP_5;
  case VK_NUMPAD6: return KP_6;
  case VK_NUMPAD7: return KP_7;
  case VK_NUMPAD8: return KP_8;
  case VK_NUMPAD9: return KP_9;
  case VK_UP     : return KEY_ARROW_UP;
  case VK_DOWN   : return KEY_ARROW_DOWN;
  case VK_LEFT   : return KEY_ARROW_LEFT;
  case VK_RIGHT  : return KEY_ARROW_RIGHT;
  case VK_ESCAPE : return KEY_ESCAPE;
  case VK_TAB    : return KEY_TAB;
#endif
  }
}

#pragma region ConvChar

auto ConvertCharacter(char input) -> Keys {
  switch (input) {
    using enum Keys;
  case 'A': return KEY_A;
  case 'B': return KEY_B;
  case 'C': return KEY_C;
  case 'D': return KEY_D;
  case 'E': return KEY_E;
  case 'F': return KEY_F;
  case 'G': return KEY_G;
  case 'H': return KEY_H;
  case 'I': return KEY_I;
  case 'J': return KEY_J;
  case 'K': return KEY_K;
  case 'L': return KEY_L;
  case 'M': return KEY_M;
  case 'N': return KEY_N;
  case 'O': return KEY_O;
  case 'P': return KEY_P;
  case 'Q': return KEY_Q;
  case 'R': return KEY_R;
  case 'S': return KEY_S;
  case 'T': return KEY_T;
  case 'U': return KEY_U;
  case 'V': return KEY_V;
  case 'W': return KEY_W;
  case 'X': return KEY_X;
  case 'Y': return KEY_Y;
  case 'Z': return KEY_Z;
  case '0': return KEY_0;
  case '1': return KEY_1;
  case '2': return KEY_2;
  case '3': return KEY_3;
  case '4': return KEY_4;
  case '5': return KEY_5;
  case '6': return KEY_6;
  case '7': return KEY_7;
  case '8': return KEY_8;
  case '9': return KEY_9;
  default : return MISSING_KEY;
  }
}

#pragma region Conv&Trim

auto ConvertAndTrim(std::string& input, char delim) -> int {
  auto count  = input.find(delim);
  auto result = std::stoi(input.substr(0, count++));
  input       = input.substr(count);
  return result;
}
} // namespace libyunpa
