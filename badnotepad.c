#include <stdio.h>
#include <windows.h>
#include <string.h>
#pragma comment(lib, "user32.lib")



void ghostType(char *msg){
    INPUT ip;
    HKL kbl = GetKeyboardLayout(0);

    // Setup a generic keyboard event
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    for(int i = 0; i < strlen(msg); i++){
        // Press the "A" key
        ip.ki.wVk = VkKeyScanExA(msg[i], kbl); // virtual-key code for the "a" key
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));

        // Release the "A" key
        ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &ip, sizeof(INPUT));

        Sleep(500);
    }

    
}

int main(int argc, char *argv[]){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char *msg = "Shelled";

    printf("%x\n", 'a');
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    CreateProcess("C:\\Windows\\system32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    Sleep(1000);

    ghostType(msg);

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );
}



