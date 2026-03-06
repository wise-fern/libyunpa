export module libyunpa:Core;
export import :EventManager;
export import :SceneManager;
export import :Time;
export import ftxui;
export import std;

namespace libyunpa {
export class Core final {
private:
    Core() = default;
    static std::unique_ptr<Core> instance;
    static bool                  initialized;

public:
    Core(const Core &)            = delete;
    Core(Core &&)                 = delete;
    Core &operator=(const Core &) = delete;
    Core &operator=(Core &&)      = delete;
    ~Core();

private:
    GameTime      gameTime;
    EventManager  eventMan;
    SceneManager  sceneMan;
    ftxui::Screen screen{ftxui::Screen::Create(ftxui::Dimension::Full())};

    void game_loop();
    void render(const ScenePtr &scene);
    void run();
    void set_next_scene(ScenePtr nextScene);
    [[nodiscard]]
    ScenePtr get_current_scene() const;

public:
    static void Init();
    static void Run();
    static void SetNextScene(ScenePtr nextScene);
    static void Shutdown();

    [[nodiscard]]
    static ScenePtr GetCurrentScene();
};
} // namespace libyunpa
