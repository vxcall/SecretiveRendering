#include "dllmain.h"
#include <Windows.h>
#include <iostream>
#include "debugMessage.h"
#include "hooking.h"
#include "findpattern.h"

void Detach()
{
    FREECONSOLE()
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    hooks::initialize();
    while (true)
    {
        Sleep(100);
    }
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(nullptr, 0, fMain, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    } else if (dwReason == DLL_PROCESS_DETACH && !lpReserved) {
        Detach();
    }
    return TRUE;
}