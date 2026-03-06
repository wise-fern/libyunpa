module libyunpa;

namespace libyunpa {
void DECSET(DecModes mode) {
    auto output{std::format("\x1b[?{}h", std::to_underlying(mode))};
    std::cout << output;
}

void DECRST(DecModes mode) {
    auto output{std::format("\x1b[?{}l", std::to_underlying(mode))};
    std::cout << output;
}

int convert_and_trim(std::string &input, char delim) {
    auto count(input.find(delim));
    auto result{std::stoi(input.substr(0, count++))};
    input = input.substr(count);
    return result;
}
} // namespace libyunpa
