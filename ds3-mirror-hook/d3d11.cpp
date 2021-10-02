#include "pch.h"
#include "d3d11.h"
#include "d3d11dev.h"
#include "d3d11ctxt.h"
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
    ID3D11Device* d3d11Dev;
    ID3D11DeviceContext *d3d11Ctxt;
    HRESULT ret = oD3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, &d3d11Dev, pFeatureLevel, &d3d11Ctxt);
    
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
        hkID3D11DeviceContext *hkD3d11Ctxt = new hkID3D11DeviceContext(d3d11Ctxt);
        hkID3D11Device* hkD3d11Dev = new hkID3D11Device(d3d11Dev, hkD3d11Ctxt);

        LOG << "Created device: " << std::hex << hkD3d11Dev << LogEndl::INFO;
        LOG << "Created context: " << std::hex << hkD3d11Ctxt << LogEndl::INFO;

        RenderManager::getInstance().setD3d11Dev(d3d11Dev);
        RenderManager::getInstance().setD3d11Ctxt(d3d11Ctxt);

        if (ppImmediateContext)
        {
            *ppImmediateContext = hkD3d11Ctxt;
        }
        else
        {
            hkD3d11Ctxt->Release();
        }
        if (ppDevice)
        {
            *ppDevice = hkD3d11Dev;
        }
        else
        {
            hkD3d11Dev->Release();
        }
    }
    return ret;
}