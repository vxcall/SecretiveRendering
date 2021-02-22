#pragma once
#include "MinHook.h"
#include <d3d9.h>
#include <iostream>
#include <vector>
#include "findpattern.h"
#include "debugMessage.h"

namespace hooks {
    void Initialize();

    template<typename T>
    inline void Hook(void* pTarget, void* pDetour, T** ppOriginal)
    {
        MH_STATUS creationStatus = MH_CreateHook(pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
        if (creationStatus != MH_OK)
            std::cout << "MH_CreateHook() failed" << std::endl;
        MH_STATUS enableStatus = MH_EnableHook(pTarget);
        if (enableStatus != MH_OK)
            std::cout << "MH_EnableHook() failed" << std::endl;
    }
    void Uninitialize();
}