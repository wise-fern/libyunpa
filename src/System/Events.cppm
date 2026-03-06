export module libyunpa:Events;
export import std;

namespace libyunpa {
export enum class Keys : std::uint8_t {
    ERR,
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
    KEY_Y,
    KEY_X,
    KEY_Z,
    KEY_ESCAPE,
    KEY_TAB,
    KEY_RETURN,
    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_SPACE,
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
    KEY_ARROW_UP,
    KEY_ARROW_RIGHT,
    KEY_ARROW_DOWN,
    KEY_ARROW_LEFT,
    KP_0,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,
    KP_9,
    KP_ENTER
};

export enum class KeyMods : std::uint16_t {
    NONE          = 0 << 0,
    RIGHT_ALT     = 1 << 0,
    LEFT_ALT      = 1 << 1,
    RIGHT_CTRL    = 1 << 2,
    LEFT_CTRL     = 1 << 3,
    SHIFT         = 1 << 4,
    NUMLOCK_ON    = 1 << 5,
    SCROLLLOCK_ON = 1 << 6,
    CAPSLOCK_ON   = 1 << 7,
    ENHANCED      = 1 << 8,
    ALT           = RIGHT_ALT bitor LEFT_ALT,
    CTRL          = RIGHT_CTRL bitor LEFT_CTRL
};

export constexpr auto operator|(KeyMods lhs, KeyMods rhs) {
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

export using Event = std::variant<Events::KeyEvent>;
} // namespace libyunpa
