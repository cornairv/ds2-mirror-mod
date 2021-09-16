#include "pch.h"
#include "d3d11.h"
#include "logger.h"
#include "render_manager.h"

HRESULT WINAPI hkD3D11CreateDevice(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext)
{
    HRESULT ret = oD3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
    
    LOG << "pAdapter: " << std::hex << pAdapter
        << "\nDriverType: " << DriverType
        << "\nSoftware: " << Software
        << "\nFlags: " << Flags
        << "\npFeatureLevels: " << pFeatureLevels
        << "\nFeatureLevels: " << FeatureLevels
        << "\nSDKVersion: " << SDKVersion
        << "\nppDevice: " << ppDevice
        << "\npFeatureLevel: " << pFeatureLevel
        << "\nppImmediateContext: " << ppImmediateContext
        << LogEndl::INFO;

    if (ret == 0)
    {
        if (ppDevice)
        {
            RenderManager::getInstance().setD3d11Dev(*ppDevice);
        }
        if (ppImmediateContext)
        {
            RenderManager::getInstance().setD3d11Ctxt(*ppImmediateContext);
        }
    }
    return ret;
}