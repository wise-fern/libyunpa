module;
#ifdef WIN32
#include <conio.h>
#else
#include <cstdio>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#endif
#include <tao/pegtl.hpp>
export module libyunpa:Events;
export import :Utilities;
export import std;
#ifndef WIN32
// NOLINTNEXTLINE
int kbhit() {
  struct timeval tval = {.tv_sec = 0, .tv_usec = 0};
  fd_set         readfds;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  return static_cast<int>(select(1, &readfds, nullptr, nullptr, &tval) > 0);
}

// NOLINTNEXTLINE
int getch() {
  termios oldt{};
  termios newt{};
  int     chr{};

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag and_eq static_cast<tcflag_t>(compl(ICANON bitor ECHO));
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  chr = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return chr;
}
#endif
using namespace std;

namespace libyunpa {
// NOLINTBEGIN(misc-confusable-identifiers)
export enum Keys : uint8_t {
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
  KP_9,
  KEY_TAB,
  KEY_RETURN,
  KEY_SPACE,
  KEY_BACKSPACE,
  KEY_ARROW_UP,
  KEY_ARROW_RIGHT,
  KEY_ARROW_DOWN,
  KEY_ARROW_LEFT,
  KEY_INSERT,
  KEY_DELETE,
  KEY_HOME,
  KEY_END,
  KEY_PAGE_UP,
  KEY_PAGE_DOWN
};
export enum class KeyMods : std::uint8_t {
  NONE = 0 << 0,
  SHIFT = 1 << 0,
  ALT = 1 << 1,
  CTRL = 1 << 2,
  CONTROL = CTRL
};

export auto operator|(const KeyMods& lhs, const KeyMods& rhs) {
  return static_cast<KeyMods>(static_cast<int>(lhs) bitor
                              static_cast<int>(rhs));
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
struct DigitPlusTerm : seq<tao::pegtl::plus<digit>, one<delim>> {};

struct Win32InputString :
    seq<CSI,
        DigitPlusTerm<>,
        DigitPlusTerm<>,
        DigitPlusTerm<>,
        DigitPlusTerm<>,
        DigitPlusTerm<>,
        DigitPlusTerm<'_'>> {};

struct Language : sor<Win32InputString> {};
} // namespace Grammar

template <typename Rule> struct Action : tao::pegtl::nothing<Rule> {
  template <typename ActionInput>
  static void apply(const ActionInput& /*input*/,
                    std::queue<Event>& /*eventQueue*/) {}
};

template <> struct Action<Grammar::Win32InputString> {
  template <typename ActionInput>
  static void apply(const ActionInput& input,
                    std::queue<Event>& /*eventQueue*/) {
    std::string inputString = input.string();
    inputString = inputString.substr(2);
    [[maybe_unused]] auto vKeyCode = ConvertAndTrim(inputString);
    [[maybe_unused]] auto vScanCode = ConvertAndTrim(inputString);
    [[maybe_unused]] auto unicodeChar = ConvertAndTrim(inputString);
    [[maybe_unused]] auto isKeyDown = ConvertAndTrim(inputString) == 1;
    [[maybe_unused]] auto controlKeyState = ConvertAndTrim(inputString);
  }
};

// NOLINTEND(misc-confusable-identifiers)
class EventManager {
private:
  std::queue<Event> _eventQueue;

public:
  auto update() {
    if (kbhit() != 0) {
      std::string workingString;
      while (kbhit() != 0) {
        auto input = getch();
        workingString += static_cast<char>(input);
        auto parserInput = tao::pegtl::memory_input(workingString, "");
        if (tao::pegtl::parse<Grammar::Language>(parserInput)) {
          workingString.clear();
        }
      }
      auto parserInput = tao::pegtl::memory_input(workingString, "");
      if (tao::pegtl::parse<Grammar::Language>(parserInput, _eventQueue)) {
        workingString.clear();
      }
    }
  }
};
} // namespace libyunpa
