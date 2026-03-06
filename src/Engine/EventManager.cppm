export module libyunpa:EventManager;
export import :Events;
export import std;

namespace libyunpa {
export class EventManager {
private:
    std::atomic_flag  running;
    std::thread       monitor;
    std::queue<Event> eventQueue;
    std::mutex        queueMutex;

    void enqueue_event(Event event);
    void monitor_loop();

public:
    void                 start();
    void                 stop();
    std::optional<Event> poll_event();
};
} // namespace libyunpa
