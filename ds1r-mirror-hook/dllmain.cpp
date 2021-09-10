#include "pch.h"
#include "hooks.h"
#include "d3d11.h"
#include "xinput.h"
#include "dinput8.h"
#include "config.h"
#include "logger.h"

tD3D11CreateDevice oD3D11CreateDevice = D3D11CreateDevice;
tXInputGetState oXInputGetState = XInputGetState;
tXInputSetState oXInputSetState = XInputSetState;
tDirectInput8Create oDirectInput8Create;

bool APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, [[maybe_unused]] LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        LOG << "Hooked dinput8.dll" << LogEndl::INFO;

        DisableThreadLibraryCalls(hModule);
        
        configure("dsmirror\\dsmirror.ini");

        // load original dinput8.dll or user-specified dll
        HMODULE dinputDll;
        std::string dinputDllName;
        if (config.loadDll.empty())
        {
            char dinputDllPath[MAX_PATH];
            CHECK_TRUE(GetSystemDirectoryA(dinputDllPath, MAX_PATH));
            dinputDllName = std::string(dinputDllPath) + "\\dinput8.dll";
        }
        else
        {
            dinputDllName = config.loadDll;
        }
        LOG << "Loading DLL: " << dinputDllName << LogEndl::INFO;
        dinputDll = LoadLibraryA(dinputDllName.c_str());
        if (!dinputDll)
        {
            LOG << "Failed to load " << dinputDllName << LogEndl::ERRO;
            return false;
        }

        oDirectInput8Create = (tDirectInput8Create)GetProcAddress(dinputDll, "DirectInput8Create");
        CHECK_TRUE(oDirectInput8Create != nullptr);

        setupHooks();
        LOG << "Finished hook" << LogEndl::ERRO;

        return true;

    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {

    }

    return true;
}

