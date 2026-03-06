module libyunpa;

namespace libyunpa {
const TextOptions Menu::SelectedDefault{.bold      = true,
                                        .underline = UnderlineStyle::SINGLE,
                                        .color     = ftxui::Color::Red};
const TextOptions Menu::UnselectedDefault{};

Menu::Menu() : Menu("") {}

Menu::Menu(std::string_view title)
    : Menu(title,
           {.selected = SelectedDefault, .unselected = UnselectedDefault}) {}

Menu::Menu(std::string_view title, const MenuOptions &options)
    : title(title),
      selectedOptions(options.selected),
      unselectedOptions(options.unselected) {}

ftxui::Element Menu::render() const {
    using namespace ftxui;
    std::vector<ftxui::Element> elements;
    elements.reserve(lines.size());
    for (int i = 0; i < static_cast<int>(lines.size()); i++) {
        elements.push_back(
            (i == index
                 ? selectedOptions(lines[static_cast<std::size_t>(i)])
                 : unselectedOptions(lines[static_cast<std::size_t>(i)])) |
            ftxui::center);
    }
    return hbox(window(text(title), vbox(elements)));
}

void Menu::add_item(std::string_view item) {
    lines.emplace_back(item);
}

void Menu::handle_key(Keys key) {
    switch (key) {
        using enum Keys;
    case KEY_W:
    case KEY_ARROW_UP:
    case KP_8:
        if (--index < 0) {
            index = static_cast<int>(lines.size()) - 1;
        }
        break;
    case KEY_S:
    case KEY_ARROW_DOWN:
    case KP_2:
        if (++index >= static_cast<int>(lines.size())) {
            index = 0;
        }
        break;
    default:
        return;
    }
}
} // namespace libyunpa
