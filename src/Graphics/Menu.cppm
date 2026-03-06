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
    std::function<void(int)> callback;

public:
    Menu();
    Menu(
        std::string_view title, std::function<void(int)> callback = [](int) {});
    Menu(
        std::string_view         title,
        const MenuOptions       &options,
        std::function<void(int)> callback = [](int) {});
    void add_item(std::string_view item);
    void handle_key(Keys key);
    void handle_key(const Events::KeyEvent &event);

    [[nodiscard]]
    ftxui::Element render() const;
};
} // namespace libyunpa
