#include "hooking.h"
#include <Windows.h>
#include <d3d9.h>
#include <iostream>
#include "findpattern.h"
#include "debugMessage.h"

using tPresent = HRESULT(STDMETHODCALLTYPE*) (IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
using tReset = HRESULT (STDMETHODCALLTYPE*) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

tPresent oPresent = nullptr;
tReset oReset = nullptr;

HRESULT STDMETHODCALLTYPE hkPresent(IDirect3DDevice9* thisptr, const RECT* src, const RECT* dest, HWND wnd_override, const RGNDATA* dirty_region) {
    std::cout << "I'm in Present" << std::endl;
    D3DCOLOR color = D3DCOLOR_XRGB(255, 0, 0);
    D3DRECT position = {100, 100, 200, 200};

    thisptr->Clear(1, &position, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
    return oPresent(thisptr, src, dest, wnd_override, dirty_region);
}

HRESULT STDMETHODCALLTYPE hkReset(IDirect3DDevice9* thisptr, D3DPRESENT_PARAMETERS* params) {
    std::cout << "I'm in Reset" << std::endl;
    return oReset(thisptr, params);
}

void hooks::initialize() {
    try {
        if (MH_Initialize() != MH_OK)
        {
            throw std::exception("MH_Initialize failed!");
        }
        uintptr_t originalPresentAddress = FindPattern("gameoverlayrenderer.dll", "68 ? ? ? ? 68 ? ? ? ? FF 76 44") + 0x1;
        uintptr_t originalResetAddress = FindPattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18 85 F6 74 14 FF 75 E0 8B CE 53 FF 75 EC E8 ? ? ? ?") + 2;
        LOGHEX("OriginalPresentAddress", originalPresentAddress)
        LOGHEX("OriginalResetAddress", originalResetAddress)
        if (MH_CreateHook(**reinterpret_cast<void***>(originalPresentAddress), &hkPresent, reinterpret_cast<LPVOID*>(&oPresent)) != MH_OK)
        {
            throw std::exception("Present hooking failed!");
        }
        if (MH_EnableHook(**reinterpret_cast<void***>(originalPresentAddress)) != MH_OK)
        {
            throw std::exception("Enabling Present hook failed!");
        }

    } catch (const std::exception &ex) {
        MessageBoxA(nullptr, ex.what(), "Error", 0);
    }
}


