export module libyunpa:Console;
export import std;

namespace libyunpa {
export enum class DecModes : std::uint16_t {
    SHOW_CURSOR             = 25,
    ALTERNATE_SCREEN_BUFFER = 1049,
    WIN32_INPUT_MODE        = 9001
};

export void DECSET(DecModes mode);
export void DECRST(DecModes mode);
} // namespace libyunpa
