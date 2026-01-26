module;
#include <cstdint>
export module libyunpa:Keyboard;

namespace libyunpa {
/// @brief Represents character and function keys on a (US) keyboard
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

/// @brief Represents modifier keys on a (US) keyboard
export enum class KeyMods : std::uint8_t {
  NONE    = 0 << 0,
  ALT     = 1 << 0,
  SHIFT   = 1 << 1,
  CTRL    = 1 << 2,
  CONTROL = CTRL
};
} // namespace libyunpa
