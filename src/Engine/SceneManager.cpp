module libyunpa;

namespace libyunpa {
bool SceneManager::empty() const {
    return scenes.empty();
}

void SceneManager::pop_scene() {
    if (scenes.empty()) {
        return;
    }
    scenes.pop();
    if (scenes.empty()) {
        return;
    }
    scenes.top()->on_reveal();
}

void SceneManager::transition_scene() {
    if (nextScene == nullptr) {
        return;
    }
    if (not scenes.empty()) {
        scenes.top()->on_bury();
    }
    scenes.push(nextScene);
    nextScene = nullptr;
}

void SceneManager::update(const GameTime &gameTime) {
    if (not scenes.empty() and scenes.top()->wants_exit()) {
        pop_scene();
    }
    if (nextScene not_eq nullptr) {
        transition_scene();
    }
    if (scenes.empty()) {
        return;
    }
    scenes.top()->update(gameTime);
}

void SceneManager::set_next_scene(ScenePtr scene) {
    this->nextScene = std::move(scene);
}

ScenePtr SceneManager::get_current_scene() const {
    if (scenes.empty()) {
        return ScenePtr{nullptr};
    }
    return scenes.top();
}

namespace {
    template <class... Ts> struct overload : Ts... {
        using Ts::operator()...;
    };
} // namespace

void SceneManager::handle_event(const Event &event) {
    auto handler = overload([&](Events::KeyEvent event) {
        if (pressedKeys.contains(event.key)) {
            if (event.isKeyDown) {
                return;
            }
            pressedKeys.erase(event.key);
        } else {
            if (event.isKeyDown) {
                pressedKeys.insert(event.key);
            }
        }
        scenes.top()->handle_event(event);
    });
    event.visit(handler);
}
} // namespace libyunpa
