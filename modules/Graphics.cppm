module;

export module libyunpa.Graphics;
export import ftxui;
import std;

namespace libyunpa {
export struct TextOptions {
  ftxui::Color color      = ftxui::Color::White;
  ftxui::Color background = ftxui::Color::Black;
  bool         bold       = false;
  bool         italic     = false;
};

export auto RenderText(const TextOptions& options, std::string_view text) {
  auto result = ftxui::text(text)
              | ftxui::color(options.color)
              | ftxui::bgcolor(options.background);
  if (options.bold) {
    result = result | ftxui::bold;
  }
  if (options.italic) {
    result = result | ftxui::italic;
  }
  return result;
}

} // namespace libyunpa
