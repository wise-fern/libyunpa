module;
#ifdef WIN32
#include <conio.h>
#endif
#include <cassert>
#include <tao/pegtl.hpp>

module libyunpa;

namespace {
namespace Grammar {
    using namespace tao::pegtl;

    struct ESC : one<'\x1b'> {};

    struct CSI : seq<ESC, one<'['>> {};

    template <char delim = ';'>
    struct DigitPlusTerm : seq<plus<digit>, one<delim>> {};

    struct Win32Input : seq<CSI,
                            DigitPlusTerm<>,
                            DigitPlusTerm<>,
                            DigitPlusTerm<>,
                            DigitPlusTerm<>,
                            DigitPlusTerm<>,
                            DigitPlusTerm<'_'>> {};

    struct Language : sor<Win32Input> {};
} // namespace Grammar

using EnqueueCallback = std::function<void(libyunpa::Event)>;

template <typename Rule> struct Action {
    template <typename ActionInput>
    static void apply(const ActionInput & /*input*/,
                      const EnqueueCallback & /*callback*/) {}
};
#ifdef WIN32
template <> struct Action<Grammar::Win32Input> {
    template <typename ActionInput>
    static void apply(const ActionInput     &actionInput,
                      const EnqueueCallback &callback) {
        using namespace libyunpa;
        std::string input{actionInput.string()};
        input = input.substr(2);
        auto key_code{convert_and_trim(input)};
        [[maybe_unused]]
        auto scan_code{convert_and_trim(input)};
        [[maybe_unused]]
        auto unicode_code{convert_and_trim(input)};
        auto is_key_down{convert_and_trim(input) == 1};
        [[maybe_unused]]
        auto control_keys{convert_and_trim(input)};
        auto repeat_count{convert_and_trim(input, '_')};
        assert(repeat_count == 1);
        auto event{Events::KeyEvent{.isKeyDown = is_key_down,
                                    .key  = convert_msoft_key_code(key_code),
                                    .mods = KeyMods::NONE}};
        callback(event);
    }
};
#endif
} // namespace

namespace libyunpa {
void EventManager::enqueue_event(Event event) {
    std::lock_guard lock(queueMutex);
    eventQueue.push(event);
}

void EventManager::monitor_loop() {
    auto callback = [&](Event event) {
        enqueue_event(event);
    };
    std::string in_string;
    while (running.test()) {
        while (_kbhit() not_eq 0) {
            auto input{_getch()};
            in_string += static_cast<char>(input);
            auto parserInput{tao::pegtl::memory_input(in_string, "")};
            if (tao::pegtl::parse<Grammar::Language, Action>(parserInput,
                                                             callback)) {
                in_string.clear();
            }
        }
        if (in_string.empty()) {
            continue;
        }
        auto parserInput{tao::pegtl::memory_input(in_string, "")};
        tao::pegtl::parse<Grammar::Language, Action>(parserInput, callback);
        in_string.clear();
    }
}

void EventManager::start() {
#ifdef WIN32
    initialize_terminal();
#endif
    using enum DecModes;
    DECSET(APPLICATION_CURSOR_KEYS);
    DECRST(SMOOTH_SCROLL_MODE);
    DECRST(SHOW_CURSOR);
    DECSET(APPLICATION_KEYPAD_MODE);
    DECSET(ALTERNATE_SCREEN_BUFFER);
    DECSET(WIN32_INPUT_MODE);
    DECRST(AUTO_REPEAT_KEYS);
    running.test_and_set();
    running.notify_all();
    monitor = std::thread(&EventManager::monitor_loop, this);
    DECRST(AUTO_REPEAT_KEYS);
}

void EventManager::stop() {
    running.clear();
    running.notify_all();
    if (monitor.joinable()) {
        monitor.join();
    }
    DECSET(DecModes::SHOW_CURSOR);
    DECRST(DecModes::WIN32_INPUT_MODE);
    DECRST(DecModes::ALTERNATE_SCREEN_BUFFER);
}

std::optional<Event> EventManager::poll_event() {
    std::lock_guard lock(queueMutex);
    if (eventQueue.empty()) {
        return {};
    }
    auto result{eventQueue.front()};
    eventQueue.pop();
    return result;
}
} // namespace libyunpa
