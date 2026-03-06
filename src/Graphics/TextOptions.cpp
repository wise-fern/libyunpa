module libyunpa;

namespace libyunpa {
ftxui::Element TextOptions::operator()(std::string_view text) const {
    auto result{ftxui::text(text)};
    if (bold) {
        result or_eq ftxui::bold;
    }
    if (italic) {
        result or_eq ftxui::italic;
    }
    if (dim) {
        result or_eq ftxui::dim;
    }
    if (blink) {
        result or_eq ftxui::blink;
    }
    switch (underline) {
        using enum UnderlineStyle;
    case SINGLE:
        result or_eq ftxui::underlined;
        break;
    case DOUBLE:
        result or_eq ftxui::underlinedDouble;
        break;
    case NONE:
        break;
    }
    result or_eq ftxui::color(color);
    result or_eq ftxui::bgcolor(bgColor);

    return result;
}
} // namespace libyunpa
