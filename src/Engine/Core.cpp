module;
#include <cassert>
module libyunpa;

namespace libyunpa {
std::unique_ptr<Core> Core::instance{nullptr};
bool                  Core::initialized{false};

ScenePtr Core::get_current_scene() const {
    return sceneMan.get_current_scene();
}

void Core::set_next_scene(ScenePtr nextScene) {
    sceneMan.set_next_scene(std::move(nextScene));
}

Core::~Core() {
    eventMan.stop();
}

// NOLINTNEXTLINE(misc-no-recursion)
void Core::render(const ScenePtr &scene) {
    if (scene == nullptr) {
        return;
    }
    render(scene->get_parent());
    ftxui::Render(screen, scene->render());
}

void Core::game_loop() {
    while (true) {
        gameTime.update();
        sceneMan.update(gameTime);
        while (const auto event = eventMan.poll_event()) {
            sceneMan.handle_event(event.value());
        }
        if (sceneMan.empty()) {
            return;
        }
        screen.Clear();
        render(sceneMan.get_current_scene());
        std::cout << std::format("\x1b[1;1H{}", screen.ToString());
    }
}

void Core::run() {
    eventMan.start();
    gameTime.reset();
    game_loop();
    eventMan.stop();
}

void Core::Run() {
    assert(instance != nullptr);
    instance->run();
}

void Core::SetNextScene(ScenePtr nextScene) {
    assert(instance != nullptr);
    instance->set_next_scene(std::move(nextScene));
}

ScenePtr Core::GetCurrentScene() {
    assert(instance != nullptr);
    return instance->get_current_scene();
}

void Core::Init() {
    if (initialized) {
        return;
    }
    instance.reset(new Core());
    initialized = true;
}

void Core::Shutdown() {
    instance.reset();
}
} // namespace libyunpa
