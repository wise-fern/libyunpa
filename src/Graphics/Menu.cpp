module libyunpa;

namespace libyunpa {
const TextOptions Menu::SelectedDefault{.bold      = true,
                                        .underline = UnderlineStyle::SINGLE,
                                        .color     = ftxui::Color::Red};
const TextOptions Menu::UnselectedDefault{};

Menu::Menu() : Menu("") {}

Menu::Menu(std::string_view title, std::function<void(int)> callback)
    : Menu(title,
           {.selected = SelectedDefault, .unselected = UnselectedDefault},
           std::move(callback)) {}

Menu::Menu(std::string_view         title,
           const MenuOptions       &options,
           std::function<void(int)> callback)
    : title(title),
      selectedOptions(options.selected),
      unselectedOptions(options.unselected),
      callback(std::move(callback)) {}

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
    case KEY_SPACE:
    case KEY_RETURN:
    case KP_ENTER:
        callback(index);
        break;
    default:
        return;
    }
}

void Menu::handle_key(const Events::KeyEvent &event) {
    if (not event.isKeyDown) {
        return;
    }
    handle_key(event.key);
}
} // namespace libyunpa
