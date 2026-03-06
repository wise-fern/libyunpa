module;
#include <cstdio>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
module libyunpa;

namespace libyunpa {
int _kbhit() {
    static const auto STDIN{0};
    static auto       initialized{false};

    if (!initialized) {
        // Use termios to turn off line buffering
        termios term{};
        tcgetattr(STDIN, &term);
        term.c_lflag and_eq static_cast<tcflag_t>(compl ICANON);
        tcsetattr(STDIN, TCSANOW, &term);
        // NOLINTNEXTLINE(bugprone-unsafe-functions)
        setbuf(stdin, nullptr);
        initialized = true;
    }

    int bytesWaiting{};
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

int _getch() {
    if (_kbhit() == 0) {
        return 0;
    }
    return std::cin.get();
}
} // namespace libyunpa
