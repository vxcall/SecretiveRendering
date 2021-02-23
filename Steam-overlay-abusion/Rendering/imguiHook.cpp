#include "imguiHook.h"

WNDPROC oWndProc;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT STDMETHODCALLTYPE hkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

// This is a key.
HWND window;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM gamePid) {
    DWORD hPid = NULL;
    // Getting current referring process's pid and assigning into hPid.
    GetWindowThreadProcessId(hwnd, &hPid);

    // Compare if current referring process is same as the process this hack is being injected.
    if (hPid != gamePid) {
        return TRUE;
    } else {
        window = hwnd;
        return FALSE;
    }
}

void imguiHook::InitializeImgui(IDirect3DDevice9* pDevice) {
    EnumWindows(EnumWindowsProc, GetCurrentProcessId());

    // Alternative way to get handle of window. This is much easier but I just go with the former.
    //D3DDEVICE_CREATION_PARAMETERS parameters;
    //pDevice->GetCreationParameters(&parameters);
    //window = parameters.hFocusWindow;

    if (window != NULL) {
        oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, LONG_PTR(hkWndProc)));
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();
        // Perform final ImGui setup.
        ImGui_ImplWin32_Init (window);
        ImGui_ImplDX9_Init(pDevice);
    }
}