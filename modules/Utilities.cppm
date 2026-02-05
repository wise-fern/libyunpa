module;

export module libyunpa.Utilities;
export import libyunpa.Console;
export import libyunpa.Graphics;
export import libyunpa.System;
import std;

namespace libyunpa {
#pragma region Menu

export struct MenuOptions {
  std::string title = "A menu";
  TextOptions selected;
  TextOptions unselected;
};

export class Menu {
private:
  std::string              _title;
  TextOptions              _selected;
  TextOptions              _unselected;
  std::vector<std::string> _items;
  int                      _idx = 0;

public:
  Menu(const MenuOptions& options) :
      _title(options.title),
      _selected(options.selected),
      _unselected(options.unselected) {}

  auto addItem(const std::string& item) {
    _items.push_back(item);
  }

  [[nodiscard]]
  auto render() const {
    ftxui::Elements elements;
    for (int i = 0; static_cast<std::size_t>(i) < _items.size(); ++i) {
      elements.push_back(RenderText(i == _idx ? _selected : _unselected,
        _items[static_cast<std::size_t>(i)]));
    }
    return ftxui::vbox(
      ftxui::hbox(ftxui::window(ftxui::text(_title), ftxui::vbox(elements))));
  }

  auto handleKey(const Keys& key) {
    switch (key) {
      using enum Keys;
    case KEY_D:
    case KEY_ARROW_DOWN:
    case KP_2:
      if (static_cast<std::size_t>(++_idx) >= _items.size()) {
        _idx = 0;
      }
      return;
    case KEY_W:
    case KEY_ARROW_UP:
    case KP_8:
      if (--_idx < 0) {
        _idx = static_cast<int>(_items.size()) - 1;
      }
      return;
    default: return;
    }
  }

  auto handleKey(const Events::KeyEvent& event) {
    if (not event.isKeyDown) {
      return;
    }
    handleKey(event.key);
  }
};

#pragma region Timer

export class Timer {
private:
  Duration                    _elapsed = Duration::zero();
  Duration                    _interval;
  std::function<void(Timer&)> _callback;
  bool                        _repeat;

public:
  Timer(Duration                       interval,
    const std::function<void(Timer&)>& callback,
    bool                               repeats = false) :
      _interval(interval), _callback(callback), _repeat(repeats) {}

  auto update(const Duration& elapsed) {
    if (_elapsed >= _interval) {
      return;
    }
    _elapsed += elapsed;
    if (_elapsed >= _interval) {
      if (_repeat) {
        _elapsed = Duration::zero();
      }
      _callback(*this);
    }
  }

  auto reset() {
    _elapsed = Duration::zero();
  }
};
} // namespace libyunpa
