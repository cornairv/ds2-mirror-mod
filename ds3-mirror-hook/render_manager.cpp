#include "pch.h"
#include "render_manager.h"
#include "input_manager.h"
#include "addresses.h"
#include "logger.h"
#include "util.h"
#include <vector>
#include <set>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

void RenderManager::onRenderGlowFilter(ID3D11DeviceContext* ctx)
{
	mirrorScreen(ctx);
	mirror.didRenderGlowFilter = true;
}

// if FPS is low, DS3 skips some render passes so perform mirroring earlier
void RenderManager::onEndPostEffectScene(ID3D11DeviceContext* ctx)
{
	if (!mirror.didRenderGlowFilter)
	{
		mirrorScreen(ctx);
	}
	mirror.didRenderGlowFilter = false;
}

void RenderManager::mirrorScreen(ID3D11DeviceContext* ctx)
{

	// get current context
	ComPtr<ID3D11Device> d3d11Dev;
	ctx->GetDevice(&d3d11Dev);

	if (!mirror.initialized)
	{
		initResources(d3d11Dev.Get());
	}
	initContext(ctx, d3d11Dev.Get());

	if (InputManager::getInstance().toggleState)
	{
		ctx->VSSetShader(mirror.vertexShader, nullptr, 0);
		ctx->PSSetShader(mirror.pixelShader, nullptr, 0);
		ctx->OMSetBlendState(nullptr, nullptr, 0xffffffff);
		ctx->OMSetRenderTargets(1, &mirror.dstView, nullptr);
		ctx->PSSetShaderResources(0, 1, &mirror.srcView);
		ctx->PSSetSamplers(0, 1, &mirror.samplerState);
		ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ctx->IASetInputLayout(mirror.vertexLayout);
		ctx->IASetVertexBuffers(0, 1, &mirror.vertexBuffer, &mirror.vertexStride, &mirror.vertexOffset);
		ctx->Draw(mirror.vertexCount, 0);
		ctx->CopyResource(mirror.srcRenderTexture, mirror.dstRenderTexture);
	}
}

void RenderManager::initResources(ID3D11Device* d3d11Dev)
{
	HRESULT hr;

	// vertex buffer
	ID3DBlob* vsBlob;
	ID3DBlob* vsError;
	hr = D3DCompileFromFile(L"dsmirror\\mirror.hlsl", nullptr, nullptr, "vs_main", "vs_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &vsBlob, &vsError);
	if (hr != 0)
	{
		LOG << "D3DCompileFromFile (vs) returned " << std::hex << hr << ":\n" << (char*)vsError->GetBufferPointer() << LogEndl::ERRO;
	}
	CHECK(d3d11Dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &mirror.vertexShader));

	// pixel shader
	ID3DBlob* psBlob;
	ID3DBlob* psError;
	hr = D3DCompileFromFile(L"dsmirror\\mirror.hlsl", nullptr, nullptr, "ps_main", "ps_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &psBlob, &psError);
	if (hr != 0)
	{
		LOG << "D3DCompileFromFile (ps) returned " << std::hex << hr << ":\n" << (char*)psError->GetBufferPointer() << LogEndl::ERRO;
	}
	CHECK(d3d11Dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &mirror.pixelShader));

	// sampler state
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 1;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 1;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = 0;
	CHECK(d3d11Dev->CreateSamplerState(&samplerDesc, &mirror.samplerState));

	// vertex layout
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[2];
	D3D11_INPUT_ELEMENT_DESC& posDesc = vertexLayoutDesc[0];
	posDesc.SemanticName = "POS";
	posDesc.SemanticIndex = 0;
	posDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	posDesc.InputSlot = 0;
	posDesc.AlignedByteOffset = 0;
	posDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	posDesc.InstanceDataStepRate = 0;
	D3D11_INPUT_ELEMENT_DESC& texDesc = vertexLayoutDesc[1];
	texDesc.SemanticName = "TEX";
	texDesc.SemanticIndex = 0;
	texDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
	texDesc.InputSlot = 0;
	texDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	texDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texDesc.InstanceDataStepRate = 0;
	CHECK(d3d11Dev->CreateInputLayout(vertexLayoutDesc, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &mirror.vertexLayout));

	// vertex buffer
	float vertexData[][5] =
	{
		{ -1.0f,  1.0f, 0.5f, 0.0f, 0.0f },
		{ -1.0f, -3.0f, 0.5f, 0.0f, 2.0f },
		{  3.0f,  1.0f, 0.5f, 2.0f, 0.0f }
	};
	mirror.vertexStride = sizeof(vertexData[0]);
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.ByteWidth = sizeof(vertexData);
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = mirror.vertexStride;
	D3D11_SUBRESOURCE_DATA vertexResource;
	vertexResource.pSysMem = vertexData;
	vertexResource.SysMemPitch = 0;
	vertexResource.SysMemSlicePitch = 0;
	CHECK(d3d11Dev->CreateBuffer(&vertexBufferDesc, &vertexResource, &mirror.vertexBuffer));

	mirror.initialized = true;
}

void RenderManager::initContext(ID3D11DeviceContext* ctx, ID3D11Device* d3d11Dev)
{
	ID3D11RenderTargetView* renderTargetView[8] = { 0 };

	ctx->OMGetRenderTargets(8, renderTargetView, nullptr);

	ID3D11Resource* sourceRenderResource;
	renderTargetView[0]->GetResource(&sourceRenderResource);
	renderTargetView[0]->Release();

	// if the screen size changed, create resources again
	if (mirror.srcRenderTexture != sourceRenderResource)
	{
		// release previous 
		if (mirror.srcRenderTexture)
		{
			mirror.srcRenderTexture->Release();
			mirror.dstRenderTexture->Release();
			mirror.srcView->Release();
			mirror.dstView->Release();
		}

		mirror.srcRenderTexture = (ID3D11Texture2D*)sourceRenderResource;

		// create render texture for mirroring
		D3D11_TEXTURE2D_DESC texDesc;
		mirror.srcRenderTexture->GetDesc(&texDesc);

		CHECK(d3d11Dev->CreateTexture2D(&texDesc, nullptr, &mirror.dstRenderTexture));

		// create render target for texture
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;
		if (mirror.dstRenderTexture)
		{
			CHECK(d3d11Dev->CreateRenderTargetView(mirror.dstRenderTexture, &rtvDesc, &mirror.dstView));
		}
		else
		{
			LOG << __FUNCTION__ << " mirrorRenderTexture is null" << LogEndl::ERRO;
		}

		// create shader resource from original render texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		CHECK(d3d11Dev->CreateShaderResourceView(mirror.srcRenderTexture, &srvDesc, &mirror.srcView));
	}
}

void RenderManager::reset()
{

}

void RenderManager::setMovieDef(void* movieDef)
{
	gfx.movieDef = movieDef;
}

void RenderManager::setMovieInstance(void* movieDef, void* movieInstance)
{
	if (movieDef == gfx.movieDef)
	{
		gfx.movieRoot = static_cast<void**>(movieInstance)[3];
		CHECK_TRUE(oMovieRoot_GetVariable(gfx.movieRoot, &gfx.hudRoot, "_level0"));

		CHECK_TRUE(oValue_GetMember(gfx.hudRoot.objInterface, gfx.hudRoot.pData, "LockOn", &gfx.lockOn, true));
		for (int i = 0; i < 8; i++)
		{
			CHECK_TRUE(oValue_GetMember(gfx.hudRoot.objInterface, gfx.hudRoot.pData, ("EnemyTag" + std::to_string(i)).c_str(), &gfx.enemyTag[i], true));
		}
		for (int i = 0; i < 6; i++)
		{
			CHECK_TRUE(oValue_GetMember(gfx.hudRoot.objInterface, gfx.hudRoot.pData, ("RemotePCTag" + std::to_string(i)).c_str(), &gfx.remotePCTag[i], true));
		}

		if (config.invertWeaponSwitch)
		{
			CHECK_TRUE(oValue_GetMember(gfx.hudRoot.objInterface, gfx.hudRoot.pData, "PlayerHUD", &gfx.playerHud, true));
			CHECK_TRUE(oValue_GetMember(gfx.playerHud.objInterface, gfx.playerHud.pData, "ItemPanel", &gfx.itemPanel, true));
			CHECK_TRUE(oValue_GetMember(gfx.itemPanel.objInterface, gfx.itemPanel.pData, "Item_Left", &gfx.leftWeapon, true));
			CHECK_TRUE(oValue_GetMember(gfx.itemPanel.objInterface, gfx.itemPanel.pData, "Item_Right", &gfx.rightWeapon, true));
			CHECK_TRUE(oValue_GetDisplayInfo(gfx.leftWeapon.objInterface, gfx.leftWeapon.pData, gfx.leftWeaponDisplayInfo));
			CHECK_TRUE(oValue_GetDisplayInfo(gfx.rightWeapon.objInterface, gfx.rightWeapon.pData, gfx.rightWeaponDisplayInfo));
			CHECK_TRUE(oValue_SetDisplayInfo(gfx.leftWeapon.objInterface, gfx.leftWeapon.pData, gfx.rightWeaponDisplayInfo));
			CHECK_TRUE(oValue_SetDisplayInfo(gfx.rightWeapon.objInterface, gfx.rightWeapon.pData, gfx.leftWeaponDisplayInfo));
		}
	}
}

void RenderManager::modifyDisplayInfo(void* pData, double*& displayInfo)
{
	if (pData == gfx.leftWeapon.pData)
	{
		displayInfo = gfx.leftWeaponDisplayInfo;
	}
	else if (pData == gfx.rightWeapon.pData)
	{
		displayInfo = gfx.rightWeaponDisplayInfo;
	}
	else if (pData == gfx.lockOn.pData)
	{
		displayInfo[0] = 1920 - displayInfo[0];
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (pData == gfx.enemyTag[i].pData)
			{
				displayInfo[0] = 1920 - displayInfo[0];
			}
		}
		for (int i = 0; i < 6; i++)
		{
			if (pData == gfx.remotePCTag[i].pData && displayInfo[0] != 200)
			{
				displayInfo[0] = 1920 - displayInfo[0];
			}
		}
	}
}

bool RenderManager::shouldForceInitFirstFrame(void* movieDef)
{
	return movieDef && movieDef == gfx.movieDef;
}

////////// Rendering-related hooks //////////

extern "C" void hkRenderGlowFilter(ID3D11DeviceContext* ctx)
{
	RenderManager::getInstance().onRenderGlowFilter(ctx);
}

extern "C" void hkEndPostEffectScene(ID3D11DeviceContext* ctx)
{
	RenderManager::getInstance().onEndPostEffectScene(ctx);
}

void* hkLoader_CreateMovie(void* __this, char* filename, unsigned int loadConstants, size_t memoryArena)
{
	void* ret = oLoader_CreateMovie(__this, filename, loadConstants, memoryArena);

	if (ret)
	{
		std::string filenameStr(filename);
		if (filenameStr == "data1:/menu/01_000_fe.gfx")
		{
			RenderManager::getInstance().setMovieDef(ret);
		}
	}

	return ret;
}

void* hkMovieDef_CreateInstance(void* __this, void* memContext, bool initFirstFrame, void* actionControl, void* queue)
{
	initFirstFrame = initFirstFrame || RenderManager::getInstance().shouldForceInitFirstFrame(__this);
	void* ret = oMovieDef_CreateInstance(__this, memContext, initFirstFrame, actionControl, queue);

	if (ret)
	{
		RenderManager::getInstance().setMovieInstance(__this, ret);
	}

	return ret;
}

bool hkValue_SetDisplayInfo(void* __this, void* pData, double* displayInfo)
{
	RenderManager::getInstance().modifyDisplayInfo(pData, displayInfo);
	return oValue_SetDisplayInfo(__this, pData, displayInfo);
}
