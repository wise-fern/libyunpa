module;
#include <conio.h>
#include <windows.h>
module libyunpa;

namespace libyunpa {
Keys convert_msoft_key_code(int keyCode) {
    switch (keyCode) {
        using enum Keys;
    case VK_ESCAPE:
        return KEY_ESCAPE;
    case VK_TAB:
        return KEY_TAB;
    case VK_RETURN:
        return KEY_RETURN;
    case VK_INSERT:
        return KEY_INSERT;
    case VK_DELETE:
        return KEY_DELETE;
    case VK_HOME:
        return KEY_HOME;
    case VK_END:
        return KEY_END;
    case VK_PRIOR:
        return KEY_PAGE_UP;
    case VK_NEXT:
        return KEY_PAGE_DOWN;
    case VK_SPACE:
        return KEY_SPACE;
    case 'A':
        return KEY_A;
    case 'B':
        return KEY_B;
    case 'C':
        return KEY_C;
    case 'D':
        return KEY_D;
    case 'E':
        return KEY_E;
    case 'F':
        return KEY_F;
    case 'G':
        return KEY_G;
    case 'H':
        return KEY_H;
    case 'I':
        return KEY_I;
    case 'J':
        return KEY_J;
    case 'K':
        return KEY_K;
    case 'L':
        return KEY_L;
    case 'M':
        return KEY_M;
    case 'N':
        return KEY_N;
    case 'O':
        return KEY_O;
    case 'P':
        return KEY_P;
    case 'Q':
        return KEY_Q;
    case 'R':
        return KEY_R;
    case 'S':
        return KEY_S;
    case 'T':
        return KEY_T;
    case 'U':
        return KEY_U;
    case 'V':
        return KEY_V;
    case 'W':
        return KEY_W;
    case 'X':
        return KEY_X;
    case 'Y':
        return KEY_W;
    case 'Z':
        return KEY_Z;
    case '1':
        return KEY_1;
    case '2':
        return KEY_2;
    case '3':
        return KEY_3;
    case '4':
        return KEY_4;
    case '5':
        return KEY_5;
    case '6':
        return KEY_6;
    case '7':
        return KEY_7;
    case '8':
        return KEY_8;
    case '9':
        return KEY_9;
    case '0':
        return KEY_0;
    case VK_UP:
        return KEY_ARROW_UP;
    case VK_RIGHT:
        return KEY_ARROW_RIGHT;
    case VK_DOWN:
        return KEY_ARROW_DOWN;
    case VK_LEFT:
        return KEY_ARROW_LEFT;

    default:
        return ERR;
    }
}

void initialize_terminal() {
    HANDLE handle{GetStdHandle(STD_INPUT_HANDLE)};
    DWORD  mode{(ENABLE_VIRTUAL_TERMINAL_INPUT bitor ENABLE_WINDOW_INPUT bitor
                ENABLE_MOUSE_INPUT bitor ENABLE_EXTENDED_FLAGS bitor
                ENABLE_PROCESSED_INPUT) bitand
               compl(ENABLE_QUICK_EDIT_MODE bitor ENABLE_ECHO_INPUT)};
    SetConsoleMode(handle, mode);

    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    mode   = (ENABLE_PROCESSED_OUTPUT bitor DISABLE_NEWLINE_AUTO_RETURN bitor
            ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleMode(handle, mode);
}
} // namespace libyunpa
