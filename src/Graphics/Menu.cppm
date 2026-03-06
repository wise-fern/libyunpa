export module libyunpa:Menu;
export import :Events;
export import :TextOptions;
export import std;
export import ftxui;

namespace libyunpa {
export struct MenuOptions {
    TextOptions selected;
    TextOptions unselected;
};

export class Menu {
public:
    static const TextOptions SelectedDefault;
    static const TextOptions UnselectedDefault;

private:
    std::string              title;
    std::vector<std::string> lines{};
    TextOptions              selectedOptions;
    TextOptions              unselectedOptions;
    int                      index{0};

public:
    Menu();
    Menu(std::string_view title);
    Menu(std::string_view title, const MenuOptions &options);
    void add_item(std::string_view item);
    void handle_key(Keys key);

    [[nodiscard]]
    ftxui::Element render() const;
};
} // namespace libyunpa
