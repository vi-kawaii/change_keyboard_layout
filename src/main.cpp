#include "windows.h"
#include "iostream"

int main() {
    HWND hwnd;
    HKL currentLayout;

    for (;;) {
        if (hwnd != GetForegroundWindow()) {
            std::cout << "window changed" << std::endl;
            hwnd = GetForegroundWindow();

            DWORD threadID = GetWindowThreadProcessId(hwnd, NULL);
            if (currentLayout != GetKeyboardLayout(threadID)) {
                currentLayout = GetKeyboardLayout(threadID);

                if ((intptr_t)currentLayout == 0x4090409) { // en
                    LoadKeyboardLayoutW(L"00000419", 0x00000001); // ru
                    std::cout << "changed to ru" << std::endl;
                } else if ((intptr_t)currentLayout == 0x4190419) { // ru
                    LoadKeyboardLayoutW(L"00000409", 0x00000001); // en
                    std::cout << "changed to en" << std::endl;
                }
            }
        }

        if (hwnd) {
            DWORD threadID = GetWindowThreadProcessId(hwnd, NULL);
            currentLayout = GetKeyboardLayout(threadID);
            // eng = 0x4090409
            // ru = 0x4190419
        }

        Sleep(500);
    }
}