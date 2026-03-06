module libyunpa;

namespace libyunpa {
void Scene::on_bury() {}

void Scene::on_reveal() {}

ScenePtr Scene::get_parent() const {
    return parent;
}

bool Scene::wants_exit() const {
    return wantsExit;
}

Scene::Scene() : Scene(nullptr) {}

Scene::Scene(ScenePtr parent) : parent(std::move(parent)) {}

void Scene::request_exit() {
    wantsExit = true;
}
} // namespace libyunpa
