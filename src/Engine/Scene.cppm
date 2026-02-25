export module libyunpa:Scene;
export import :Time;
export import std;

namespace libyunpa {
export class Scene;
export using ScenePtr = std::shared_ptr<Scene>;

export class Scene {
private:
  ScenePtr _parent;
  bool     _wantsExit{false};

protected:
  auto request_exit() {
    _wantsExit = true;
  }

public:
  Scene() : Scene(nullptr) {}

  Scene(ScenePtr parent) : _parent(std::move(parent)) {}

  Scene(Scene &)                  = default;
  Scene(Scene &&)                 = default;
  Scene &operator=(const Scene &) = default;
  Scene &operator=(Scene &&)      = default;
  virtual ~Scene()                = default;

  auto wants_exit() const {
    return _wantsExit;
  }

  virtual void on_bury() {}

  virtual void on_reveal() {}

  virtual void update(const GameTime &) = 0;
};
} // namespace libyunpa
