export module libyunpa:Scene;
export import ftxui;
export import std;

namespace libyunpa {
class GameTime;

namespace Events {
    struct KeyEvent;
}
export class Scene;
export using ScenePtr = std::shared_ptr<Scene>;

export class Scene {
private:
    ScenePtr parent;
    bool     wantsExit{false};

protected:
    void request_exit();

public:
    Scene();
    Scene(ScenePtr parent);
    Scene(const Scene &)            = default;
    Scene(Scene &&)                 = default;
    Scene &operator=(const Scene &) = default;
    Scene &operator=(Scene &&)      = default;
    virtual ~Scene()                = default;

    virtual void on_bury();
    virtual void on_reveal();
    virtual void update(const GameTime &)               = 0;
    virtual void handle_event(const Events::KeyEvent &) = 0;

    [[nodiscard]]
    virtual ftxui::Element render() const = 0;
    [[nodiscard]]
    bool wants_exit() const;
    [[nodiscard]]
    ScenePtr get_parent() const;
};
} // namespace libyunpa
