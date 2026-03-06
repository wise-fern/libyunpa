export module libyunpa:Utils;
export import std;

namespace libyunpa {
export enum class DecModes : std::uint16_t {
    APPLICATION_CURSOR_KEYS = 1,
    SMOOTH_SCROLL_MODE      = 4,
    AUTO_REPEAT_KEYS        = 8,
    SHOW_CURSOR             = 25,
    APPLICATION_KEYPAD_MODE = 66,
    ALTERNATE_SCREEN_BUFFER = 1049,
    WIN32_INPUT_MODE        = 9001
};

export void DECSET(DecModes mode);
export void DECRST(DecModes mode);
int         convert_and_trim(std::string &input, char delim = ';');
} // namespace libyunpa
