#include "dllmain.h"
#include <Windows.h>
#include <iostream>
#include "debugMessage.h"
#include "findpattern.h"

void Detach()
{
    FREECONSOLE()
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    uintptr_t present = FindPattern("gameoverlayrenderer.dll", "68 ? ? ? ? 68 ? ? ? ? FF 76 44") + 0x1;
    uintptr_t reset = FindPattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18 85 F6 74 14 FF 75 E0 8B CE 53 FF 75 EC E8 ? ? ? ?") + 2;

    LOGHEX("address of present", present)
    LOGHEX("address of reset", reset)

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        Sleep(10);
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