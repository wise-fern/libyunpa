export module libyunpa:Windows;
export import :Events;

namespace libyunpa {
Keys convert_msoft_key_code(int keyCode);
void initialize_terminal();
} // namespace libyunpa
