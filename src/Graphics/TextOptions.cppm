export module libyunpa:TextOptions;
export import std;
export import ftxui;

namespace libyunpa {
export enum class UnderlineStyle : std::uint8_t {
    NONE,
    SINGLE,
    DOUBLE
};

export struct TextOptions {
    bool           bold{false};
    bool           italic{false};
    bool           dim{false};
    bool           blink{false};
    UnderlineStyle underline{UnderlineStyle::NONE};
    ftxui::Color   color{ftxui::Color::White};
    ftxui::Color   bgColor{ftxui::Color::Black};

    ftxui::Element operator()(std::string_view text) const;
};
} // namespace libyunpa
