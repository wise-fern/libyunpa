module;

export module libyunpa:Menu;
import :Events;
import :Text;
import ftxui;
using namespace libyunpa;

namespace {
const auto DEFAULT_SELECTED = TextOptions{.color = ftxui::Color::Red,
  .backgroundColor                               = ftxui::Color::Black,
  .bold                                          = true,
  .italic                                        = true,
  .dim                                           = false,
  .inverted                                      = false,
  .underline                                     = Underline::SINGLE,
  .strikethrough                                 = false,
  .blink                                         = false};

const auto DEFAULT_UNSELECTED = TextOptions{.color = ftxui::Color::White,
  .backgroundColor                                 = ftxui::Color::Black,
  .bold                                            = false,
  .italic                                          = false,
  .dim                                             = false,
  .inverted                                        = false,
  .underline                                       = Underline::NONE,
  .strikethrough                                   = false,
  .blink                                           = false};
} // namespace

namespace libyunpa::Utils {
/// @brief Options to use when constructing a new Menu
export struct MenuOptions {
  /// @brief Options to use when rendering the selected item
  TextOptions selectedItem;
  /// @brief Options to use when rendering the unselectd items
  TextOptions unselectedItems;
  /// @brief Title of the menu
  std::string title;
  /// @brief Callback to invoke when an item is selected
  /// @param[in] selected int index of the selected item
  std::function<void(int)> intCallback;
  /// @overload
  /// @param[in] selected Text of the selected item
  std::function<void(std::string_view)> stringCallback;
};

namespace {
const auto DEFAULT_MENU_OPTIONS = MenuOptions{.selectedItem = DEFAULT_SELECTED,
  .unselectedItems = DEFAULT_UNSELECTED,
  .title           = "A Menu",
  .intCallback =
    [](int selected) {
      (void)selected;
    },
  .stringCallback =
    [](std::string_view selected) {
      (void)selected;
    }};
} // namespace

/// @brief A menu to help with user input
export class Menu {
private:
  TextOptions                           _selected;
  TextOptions                           _unselected;
  std::string                           _title;
  std::function<void(int)>              _intCallback;
  std::function<void(std::string_view)> _stringCallback;
  std::vector<std::string>              _items;
  int                                   _idx = 0;

public:
  /// @brief Contruct a new Menu with the given options
  /// @param[in] options
  Menu(const MenuOptions& options) :
      _selected(options.selectedItem),
      _unselected(options.unselectedItems),
      _title(options.title),
      _intCallback(options.intCallback),
      _stringCallback(options.stringCallback) {}

  Menu() : Menu(DEFAULT_MENU_OPTIONS) {}

  /// @brief Add an item to the menu
  /// @param[in] item
  void addItem(std::string_view item) {
    _items.emplace_back(item);
  }

  /// @brief Render the Menu
  [[nodiscard]]
  auto render() const {
    ftxui::Elements elements;
    for (int i = 0; i < static_cast<int>(_items.size()); ++i) {
      elements.push_back(RenderText((i == _idx) ? _selected : _unselected,
        _items[static_cast<std::size_t>(i)]));
    }
    return ftxui::window(ftxui::text(_title), ftxui::vbox(elements));
  }

  /// @brief Handle a KeyEvent
  /// @param[in] event
  auto handleKey(const Events::KeyEvent& event) {
    switch (event.key) {
      using enum Keys;
    case KEY_W:
    case KEY_ARROW_UP:
    case KP_8:
      if (--_idx < 0) {
        _idx = static_cast<int>(_items.size()) - 1;
      }
      return;
    case KEY_S:
    case KEY_ARROW_DOWN:
    case KP_2:
      if (++_idx >= static_cast<int>(_items.size())) {
        _idx = 0;
      }
      return;
    case KEY_RETURN:
    case KEY_SPACE : _intCallback(_idx); return;
    default        : break;
    }
  }
};
} // namespace libyunpa::Utils
