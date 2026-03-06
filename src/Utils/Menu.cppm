export module libyunpa:Menu;
export import std;
export import ftxui;

namespace libyunpa {
export struct MenuOptions {};

export class Menu {
private:
    std::vector<std::string> lines;

public:
    void add_item(std::string_view item);

    [[nodiscard]]
    ftxui::Element render() const;
};
} // namespace libyunpa
