#include "hooking.h"

#define REGISTER_HOOK(pTarget, pDetour, ppOriginal) Hook(pTarget, pDetour, ppOriginal); \
originalFunctions.push_back(pTarget);

// Defining custom types of target function respectively.
using tPresent = HRESULT(STDMETHODCALLTYPE*) (IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
using tReset = HRESULT (STDMETHODCALLTYPE*) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

// You need these nulled function both to use in the hookFunc, and to pass MinHook.
tPresent oPresent = nullptr;
tReset oReset = nullptr;

HRESULT STDMETHODCALLTYPE hkPresent(IDirect3DDevice9* thisptr, const RECT* src, const RECT* dest, HWND wnd_override, const RGNDATA* dirty_region) {
    D3DCOLOR color = D3DCOLOR_XRGB(121, 97, 247);
    D3DRECT position = {600, 300, 700, 400};

    thisptr->Clear(1, &position, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
    return oPresent(thisptr, src, dest, wnd_override, dirty_region);
}

HRESULT STDMETHODCALLTYPE hkReset(IDirect3DDevice9* thisptr, D3DPRESENT_PARAMETERS* params) {
    return oReset(thisptr, params);
}

std::vector<void*> originalFunctions;

void hooks::Initialize()
{
    try {
        if (MH_Initialize() != MH_OK)
            throw std::exception("MH_Initialize failed!");

        // Getting the original address of Present and Reset function
        uintptr_t originalPresentAddress = FindPattern("gameoverlayrenderer.dll", "68 ? ? ? ? 68 ? ? ? ? FF 76 44") + 0x1;
        uintptr_t originalResetAddress = FindPattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18 85 F6 74 14 FF 75 E0 8B CE 53 FF 75 EC E8 ? ? ? ?") + 2;
        LOGHEX("OriginalPresentAddress", originalPresentAddress)
        LOGHEX("OriginalResetAddress", originalResetAddress)

        // Macro in order for hooking and saving original function.
        REGISTER_HOOK(**reinterpret_cast<void***>(originalPresentAddress), &hkPresent, &oPresent)
        REGISTER_HOOK(**reinterpret_cast<void***>(originalResetAddress), &hkReset, &oReset)

    } catch (const std::exception &ex) {
        MessageBoxA(nullptr, ex.what(), "Error", 0);
    }
}

void hooks::Uninitialize()
{
    for (auto& org : originalFunctions)
    {
        MH_DisableHook(org);
    }
    MH_Uninitialize();
}

