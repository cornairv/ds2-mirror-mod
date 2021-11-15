#include "pch.h"
#include "dinput8.h"
#include "logger.h"
#include "hooks.h"

HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk) {
    HRESULT hr = oDirectInput8Create(inst_handle, version, r_iid, out_wrapper, p_unk);
    static bool initialized = false;
    if (hr == 0)
    {
        LOG << "hooked DirectInput8Create" << LogEndl::INFO;
        if (!initialized)
        {
            setupLateHooks();
        }
        initialized = true;
    }

    return hr;
}
