module;
#ifdef WIN32
#include <windows.h>
#endif
export module libyunpa:Helpers;
import :Keyboard;
import std;

namespace libyunpa {
enum class DecModes : std::uint16_t;
auto ConvertAndTrim(std::string& input, char delim = ';') -> int;
auto ConvertMSVK(int keyCode) -> Keys;
auto ConvertCharacter(char input) -> Keys;
auto DECSET(DecModes mode) -> void;
auto DECRST(DecModes mode) -> void;

// TODO Covnert from Microsoft Control Keys to KeyMods

auto ConvertAndTrim(std::string& input, char delim) -> int {
  auto count  = input.find(delim);
  auto result = std::stoi(input.substr(0, count++));
  input       = input.substr(count);
  return result;
}

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
  case '9': return ConvertCharacter(static_cast<char>(keyCode));
  default : return MISSING_KEY;
  }
}

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

enum class DecModes : std::uint16_t {
  APPLICATION_CURSOR_KEYS  = 1,
  AUTO_REPEAT_KEYS         = 8,
  SHOW_CURSOR              = 25,
  APPLICATION_KEYPAD_MODE  = 66,
  ANY_EVENT_MOUSE_TRACKING = 1003,
  SGR_MOUSE_MODE           = 1006,
  ALTERNATE_BUFFER         = 1049,
  WIN32_INPUT_MODE         = 9001
};

auto DECSET(DecModes mode) -> void {
  std::cout << std::format("\x1b[?{}h", std::to_underlying(mode));
}

void DECRST(DecModes mode) {
  std::cout << std::format("\x1b[?{}l", std::to_underlying(mode));
}
} // namespace libyunpa
