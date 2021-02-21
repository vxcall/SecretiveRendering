#include "hooking.h"
#include <Windows.h>
#include <d3d9.h>

HRESULT (STDMETHODCALLTYPE *original_present) (IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
HRESULT (STDMETHODCALLTYPE *original_reset) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

HRESULT STDMETHODCALLTYPE present(IDirect3DDevice9* thisptr, const RECT* src, const RECT* dest, HWND wnd_override, const RGNDATA* dirty_region) {
    return original_present(thisptr, src, dest, wnd_override, dirty_region);
}

HRESULT STDMETHODCALLTYPE reset(IDirect3DDevice9* thisptr, D3DPRESENT_PARAMETERS* params) {
    return original_reset(thisptr, params);
}

