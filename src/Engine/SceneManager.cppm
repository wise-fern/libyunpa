export module libyunpa:SceneManager;
export import :Events;
export import :Scene;
export import std;

namespace libyunpa {
export class SceneManager {
private:
    ScenePtr             nextScene{nullptr};
    std::stack<ScenePtr> scenes;
    std::set<Keys>       pressedKeys;

    void pop_scene();
    void transition_scene();

public:
    void update(const GameTime &gameTime);
    void handle_event(const Event &event);
    void set_next_scene(ScenePtr nextScene);

    [[nodiscard]]
    ScenePtr get_current_scene() const;
    [[nodiscard]]
    bool empty() const;
};

} // namespace libyunpa
