#include "pch.h"
#include "d3d11ctxt.h"
#include "logger.h"

#define LOG_FUNCTION LOG << std::hex << this << " Called function: " << __FUNCTION__ << LogEndl::INFO;

HRESULT hkID3D11DeviceContext::QueryInterface(REFIID riid, void** ppvObj)
{
    //LOG_FUNCTION;
    return d3d11Ctxt->QueryInterface(riid, ppvObj);
}
ULONG hkID3D11DeviceContext::AddRef()
{
    LOG_FUNCTION;
    return d3d11Ctxt->AddRef();
}
ULONG hkID3D11DeviceContext::Release()
{
    LOG_FUNCTION;
    return d3d11Ctxt->Release();
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GetDevice(ID3D11Device** ppDevice)
{
    LOG_FUNCTION;
    hkD3d11Dev->AddRef();
    *ppDevice = hkD3d11Dev;
}
HRESULT STDMETHODCALLTYPE hkID3D11DeviceContext::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData)
{
    LOG_FUNCTION;
    return d3d11Ctxt->GetPrivateData(guid, pDataSize, pData);
}
HRESULT STDMETHODCALLTYPE hkID3D11DeviceContext::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData)
{
    LOG_FUNCTION;
    return d3d11Ctxt->SetPrivateData(guid, DataSize, pData);
}
HRESULT STDMETHODCALLTYPE hkID3D11DeviceContext::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData)
{
    LOG_FUNCTION;
    return d3d11Ctxt->SetPrivateDataInterface(guid, pData);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
    LOG_FUNCTION;
    d3d11Ctxt->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
    LOG_FUNCTION;
    d3d11Ctxt->Draw(VertexCount, StartVertexLocation);
}
HRESULT STDMETHODCALLTYPE hkID3D11DeviceContext::Map(ID3D11Resource* pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource)
{
    LOG_FUNCTION;
    return d3d11Ctxt->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::Unmap(ID3D11Resource* pResource, UINT Subresource)
{
    LOG_FUNCTION;
    d3d11Ctxt->Unmap(pResource, Subresource);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
    LOG_FUNCTION;
    d3d11Ctxt->IASetInputLayout(pInputLayout);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
{
    LOG_FUNCTION;
    d3d11Ctxt->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
    LOG_FUNCTION;
    d3d11Ctxt->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
    LOG_FUNCTION;
    d3d11Ctxt->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
    LOG_FUNCTION;
    d3d11Ctxt->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSSetShader(ID3D11GeometryShader* pShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSSetShader(pShader, ppClassInstances, NumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
    LOG_FUNCTION;
    d3d11Ctxt->IASetPrimitiveTopology(Topology);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::Begin(ID3D11Asynchronous* pAsync)
{
    LOG_FUNCTION;
    d3d11Ctxt->Begin(pAsync);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::End(ID3D11Asynchronous* pAsync)
{
    LOG_FUNCTION;
    d3d11Ctxt->End(pAsync);
}
HRESULT STDMETHODCALLTYPE hkID3D11DeviceContext::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags)
{
    LOG_FUNCTION;
    return d3d11Ctxt->GetData(pAsync, pData, DataSize, GetDataFlags);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue)
{
    LOG_FUNCTION;
    d3d11Ctxt->SetPredication(pPredicate, PredicateValue);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMSetBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMSetDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMSetDepthStencilState(pDepthStencilState, StencilRef);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer* const* ppSOTargets, const UINT* pOffsets)
{
    LOG_FUNCTION;
    d3d11Ctxt->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DrawAuto()
{
    LOG_FUNCTION;
    d3d11Ctxt->DrawAuto();
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    LOG_FUNCTION;
    d3d11Ctxt->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    LOG_FUNCTION;
    d3d11Ctxt->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
    LOG_FUNCTION;
    d3d11Ctxt->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DispatchIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
    LOG_FUNCTION;
    d3d11Ctxt->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState)
{
    LOG_FUNCTION;
    d3d11Ctxt->RSSetState(pRasterizerState);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports)
{
    LOG_FUNCTION;
    d3d11Ctxt->RSSetViewports(NumViewports, pViewports);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects)
{
    LOG_FUNCTION;
    d3d11Ctxt->RSSetScissorRects(NumRects, pRects);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CopySubresourceRegion(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox)
{
    LOG_FUNCTION;
    d3d11Ctxt->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource)
{
    LOG_FUNCTION;
    d3d11Ctxt->CopyResource(pDstResource, pSrcResource);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
    LOG_FUNCTION;
    d3d11Ctxt->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CopyStructureCount(ID3D11Buffer* pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView* pSrcView)
{
    LOG_FUNCTION;
    d3d11Ctxt->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4])
{
    LOG_FUNCTION;
    d3d11Ctxt->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView* pUnorderedAccessView, const UINT Values[4])
{
    LOG_FUNCTION;
    d3d11Ctxt->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView* pUnorderedAccessView, const FLOAT Values[4])
{
    LOG_FUNCTION;
    d3d11Ctxt->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
    LOG_FUNCTION;
    d3d11Ctxt->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView* pShaderResourceView)
{
    LOG_FUNCTION;
    d3d11Ctxt->GenerateMips(pShaderResourceView);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::SetResourceMinLOD(ID3D11Resource* pResource, FLOAT MinLOD)
{
    LOG_FUNCTION;
    d3d11Ctxt->SetResourceMinLOD(pResource, MinLOD);
}
FLOAT STDMETHODCALLTYPE hkID3D11DeviceContext::GetResourceMinLOD(ID3D11Resource* pResource)
{
    LOG_FUNCTION;
    return d3d11Ctxt->GetResourceMinLOD(pResource);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ResolveSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, ID3D11Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
    LOG_FUNCTION;
    d3d11Ctxt->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState)
{
    LOG_FUNCTION;
    d3d11Ctxt->ExecuteCommandList(pCommandList, RestoreContextState);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSSetShader(ID3D11HullShader* pHullShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSSetShader(ID3D11ComputeShader* pComputeShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSGetShader(ID3D11PixelShader** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSGetShader(ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout** ppInputLayout)
{
    LOG_FUNCTION;
    d3d11Ctxt->IAGetInputLayout(ppInputLayout);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppVertexBuffers, UINT* pStrides, UINT* pOffsets)
{
    LOG_FUNCTION;
    d3d11Ctxt->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IAGetIndexBuffer(ID3D11Buffer** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset)
{
    LOG_FUNCTION;
    d3d11Ctxt->IAGetIndexBuffer(pIndexBuffer, Format, Offset);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSGetShader(ID3D11GeometryShader** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology)
{
    LOG_FUNCTION;
    d3d11Ctxt->IAGetPrimitiveTopology(pTopology);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue)
{
    LOG_FUNCTION;
    d3d11Ctxt->GetPredication(ppPredicate, pPredicateValue);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMGetBlendState(ID3D11BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::OMGetDepthStencilState(ID3D11DepthStencilState** ppDepthStencilState, UINT* pStencilRef)
{
    LOG_FUNCTION;
    d3d11Ctxt->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer** ppSOTargets)
{
    LOG_FUNCTION;
    d3d11Ctxt->SOGetTargets(NumBuffers, ppSOTargets);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::RSGetState(ID3D11RasterizerState** ppRasterizerState)
{
    LOG_FUNCTION;
    d3d11Ctxt->RSGetState(ppRasterizerState);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports)
{
    LOG_FUNCTION;
    d3d11Ctxt->RSGetViewports(pNumViewports, pViewports);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects)
{
    LOG_FUNCTION;
    d3d11Ctxt->RSGetScissorRects(pNumRects, pRects);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSGetShader(ID3D11HullShader** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSGetShader(ID3D11DomainShader** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSGetShader(ID3D11ComputeShader** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
    LOG_FUNCTION;
    d3d11Ctxt->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::ClearState()
{
    LOG_FUNCTION;
    d3d11Ctxt->ClearState();
}
void STDMETHODCALLTYPE hkID3D11DeviceContext::Flush()
{
    LOG_FUNCTION;
    d3d11Ctxt->Flush();
}
D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE hkID3D11DeviceContext::GetType()
{
    LOG_FUNCTION;
    return d3d11Ctxt->GetType();
}
UINT STDMETHODCALLTYPE hkID3D11DeviceContext::GetContextFlags()
{
    LOG_FUNCTION;
    return d3d11Ctxt->GetContextFlags();
}
HRESULT STDMETHODCALLTYPE hkID3D11DeviceContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList)
{
    LOG_FUNCTION;
    return d3d11Ctxt->FinishCommandList(RestoreDeferredContextState, ppCommandList);
}