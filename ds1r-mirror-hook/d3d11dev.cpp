#include "pch.h"
#include "d3d11dev.h"
#include "logger.h"

#define LOG_FUNCTION LOG << std::hex << this << " Called function: " << __FUNCTION__ << LogEndl::INFO;

HRESULT hkID3D11Device::QueryInterface(REFIID riid, void** ppvObj)
{
    //LOG_FUNCTION;
    return d3d11Dev->QueryInterface(riid, ppvObj);
}
ULONG hkID3D11Device::AddRef()
{
    LOG_FUNCTION;
    return d3d11Dev->AddRef();
}
ULONG hkID3D11Device::Release()
{
    LOG_FUNCTION;
    return d3d11Dev->Release();
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateBuffer(pDesc, pInitialData, ppBuffer);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateShaderResourceView(pResource, pDesc, ppSRView);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateRenderTargetView(pResource, pDesc, ppRTView);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateClassLinkage(ID3D11ClassLinkage** ppLinkage)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateClassLinkage(ppLinkage);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateBlendState(pBlendStateDesc, ppBlendState);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateSamplerState(pSamplerDesc, ppSamplerState);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateQuery(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateQuery(pQueryDesc, ppQuery);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreatePredicate(const D3D11_QUERY_DESC* pPredicateDesc, ID3D11Predicate** ppPredicate)
{
    LOG_FUNCTION;
    return d3d11Dev->CreatePredicate(pPredicateDesc, ppPredicate);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateCounter(const D3D11_COUNTER_DESC* pCounterDesc, ID3D11Counter** ppCounter)
{
    LOG_FUNCTION;
    return d3d11Dev->CreateCounter(pCounterDesc, ppCounter);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext)
{
    LOG_FUNCTION;
    HRESULT hr = d3d11Dev->CreateDeferredContext(ContextFlags, ppDeferredContext);
    //*ppDeferredContext = new hkID3D11DeviceContext(*ppDeferredContext);
    return hr;
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void** ppResource)
{
    LOG_FUNCTION;
    return d3d11Dev->OpenSharedResource(hResource, ReturnedInterface, ppResource);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport)
{
    LOG_FUNCTION;
    return d3d11Dev->CheckFormatSupport(Format, pFormatSupport);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels)
{
    LOG_FUNCTION;
    return d3d11Dev->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}
void STDMETHODCALLTYPE hkID3D11Device::CheckCounterInfo(D3D11_COUNTER_INFO* pCounterInfo)
{
    LOG_FUNCTION;
    d3d11Dev->CheckCounterInfo(pCounterInfo);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CheckCounter(const D3D11_COUNTER_DESC* pDesc, D3D11_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szDescription, UINT* pDescriptionLength)
{
    LOG_FUNCTION;
    return d3d11Dev->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::CheckFeatureSupport(D3D11_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize)
{
    LOG_FUNCTION;
    return d3d11Dev->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData)
{
    LOG_FUNCTION;
    return d3d11Dev->GetPrivateData(guid, pDataSize, pData);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData)
{
    LOG_FUNCTION;
    return d3d11Dev->SetPrivateData(guid, DataSize, pData);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData)
{
    LOG_FUNCTION;
    return d3d11Dev->SetPrivateDataInterface(guid, pData);
}
D3D_FEATURE_LEVEL STDMETHODCALLTYPE hkID3D11Device::GetFeatureLevel()
{
    LOG_FUNCTION;
    return d3d11Dev->GetFeatureLevel();
}
UINT STDMETHODCALLTYPE hkID3D11Device::GetCreationFlags()
{
    LOG_FUNCTION;
    return d3d11Dev->GetCreationFlags();
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::GetDeviceRemovedReason()
{
    LOG_FUNCTION;
    return d3d11Dev->GetDeviceRemovedReason();
}
void STDMETHODCALLTYPE hkID3D11Device::GetImmediateContext(ID3D11DeviceContext** ppImmediateContext)
{
    LOG_FUNCTION;
    //hkD3d11Ctxt->AddRef();
    //*ppImmediateContext = hkD3d11Ctxt;
    return d3d11Dev->GetImmediateContext(ppImmediateContext);
}
HRESULT STDMETHODCALLTYPE hkID3D11Device::SetExceptionMode(UINT RaiseFlags)
{
    LOG_FUNCTION;
    return d3d11Dev->SetExceptionMode(RaiseFlags);
}
UINT STDMETHODCALLTYPE hkID3D11Device::GetExceptionMode()
{
    LOG_FUNCTION;
    return d3d11Dev->GetExceptionMode();
}