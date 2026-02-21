module;

export module libyunpa:Utilities;
export import std;

namespace libyunpa {
auto ConvertAndTrim(std::string& input, char delim = ';') {
  auto count = input.find(delim);
  auto result = std::stoi(input.substr(0, count++));
  input = input.substr(count);
  return result;
}

export enum class DecMode : std::uint16_t {
  APPLICATION_CURSOR_KEYS = 1,
  SMOOTH_SCROLL = 4,
  AUTO_REPEAT_KEYS = 8,
  SHOW_CURSOR = 25,
  APPLICATION_KEYPA_MODE = 66,
  ANY_EVENT_MOUSE_TRACKING = 1003,
  SGR_MOUSE_MODE = 1006,
  ALTERNATE_SCREEN_BUFFER = 1049,
  WIN32_INPUT_MODE = 9001
};

export auto DECSET(DecMode mode) {
  std::cout << std::format("\x1b[?{}h", std::to_underlying(mode));
}

export auto DECRST(DecMode mode) {
  std::cout << std::format("\x1b[?{}l", std::to_underlying(mode));
}
} // namespace libyunpa
