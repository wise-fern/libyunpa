module libyunpa;

namespace libyunpa {
void DECSET(DecModes mode) {
    std::cout << std::format("\x1b[?{}h", std::to_underlying(mode));
}

void DECRST(DecModes mode) {
    std::cout << std::format("\x1b[?{}l", std::to_underlying(mode));
}
} // namespace libyunpa
