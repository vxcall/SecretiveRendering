#pragma once
#include <Windows.h>
#include <d3d9.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

namespace imguiHook {
    void InitializeImgui(IDirect3DDevice9* pDevice);
}