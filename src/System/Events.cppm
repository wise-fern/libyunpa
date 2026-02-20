module;
#ifdef WIN32
#include <conio.h>
#endif
export module libyunpa:Events;
export import std;

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
  NONE    = 0 << 0,
  SHIFT   = 1 << 0,
  ALT     = 1 << 1,
  CTRL    = 1 << 2,
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

// NOLINTEND(misc-confusable-identifiers)
class EventManager {
public:
#pragma region WIN32
#ifdef WIN32

  auto update() {
    if (_kbhit() not_eq 0) {}
  }

#endif
};
} // namespace libyunpa
