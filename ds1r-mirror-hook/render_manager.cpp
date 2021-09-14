#include "pch.h"
#include "render_manager.h"
#include "input_manager.h"
#include "addresses.h"
#include "logger.h"

void RenderManager::mirrorScreen(void* unk1)
{

	// get current context
	byte* ptr = (byte*)unk1;
	ptr = *(byte**)(ptr + 0x90);
	ptr = *(byte**)(ptr + 0x20);
	ID3D11DeviceContext* ctx = (ID3D11DeviceContext*)ptr;

	if (!mirror.initialized)
	{
		initResources();
	}
	initContext(ctx);

	ctx->VSSetShader(mirror.vertexShader, nullptr, 0);
	ctx->PSSetShader(mirror.pixelShader, nullptr, 0);
	ctx->OMSetRenderTargets(1, &mirror.dstView, nullptr);
	ctx->PSSetShaderResources(0, 1, &mirror.srcView);
	ctx->PSSetSamplers(0, 1, &mirror.samplerState);
	ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ctx->IASetInputLayout(mirror.vertexLayout);
	ctx->IASetVertexBuffers(0, 1, &mirror.vertexBuffer, &mirror.vertexStride, &mirror.vertexOffset);
	ctx->Draw(mirror.vertexCount, 0);
	ctx->CopyResource(mirror.srcRenderTexture, mirror.dstRenderTexture);
}

void RenderManager::modifyPostProcess([[maybe_unused]] void* __this, [[maybe_unused]] void* unk1, [[maybe_unused]] void* unk2)
{
	// get AA mode
	byte* gameData = *pGameData;
	byte* pcOptionData = *(byte**)(gameData + 0x68);
	int aaMode = *(int*)(pcOptionData + 0xf0);

	// FXAA adds an extra post process stage, so check if it's enabled
	int finalPostProcessStage = 0x1e;	//no AA or temporal AA
	if (aaMode == 1)
	{
		finalPostProcessStage = 0x20;	// FXAA
	}
	else if (aaMode == 2)
	{
		finalPostProcessStage = 0x21;	// FXAA high
	}

	int postProcessStage = *(int*)((byte*)__this + 0x38);
	if (postProcessStage == finalPostProcessStage)
	{
		RenderManager::getInstance().mirrorScreen(unk1);
	}
}

void RenderManager::initResources()
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

void RenderManager::initContext(ID3D11DeviceContext* ctx)
{
	ID3D11RenderTargetView* renderTargetView;
	ctx->OMGetRenderTargets(1, &renderTargetView, nullptr);
	ID3D11Resource* sourceRenderResource;
	renderTargetView->GetResource(&sourceRenderResource);
	renderTargetView->Release();

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
		getRenderSize(texDesc.Width, texDesc.Height);
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;
		CHECK(d3d11Dev->CreateTexture2D(&texDesc, nullptr, &mirror.dstRenderTexture));

		// create render target for texture
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
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
		srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		CHECK(d3d11Dev->CreateShaderResourceView(mirror.srcRenderTexture, &srvDesc, &mirror.srcView));

		// reset weapon icon state
		rightWeaponIconObj = nullptr;
		leftWeaponIconObj = nullptr;
	}
}

void RenderManager::getRenderSize(UINT& width, UINT& height)
{
	UINT* dimensions = reinterpret_cast<UINT*>(*pFrpgWindow + 0x34);
	width = dimensions[0];
	height = dimensions[1];
}


void RenderManager::modifyUIRect(void* __this, float* newRect)
{
	void* vtable = *(void**)__this;
	int rectOffset = 0xC4;
	int idOffset = 0x208;
	if (vtable == vtWeaponSwitchIcons)
	{
		byte* bytes = (byte*)__this;
		int id = *(int*)(bytes + idOffset);
		float* rect = (float*)(bytes + rectOffset);
		if (id == 2)
		{
			rightWeaponIconObj = __this;
			memcpy_s(rightWeaponIconCoords, sizeof(float) * 4, newRect, sizeof(float) * 4);
			if (leftWeaponIconObj)
			{
				memcpy_s(rect, sizeof(float) * 4, leftWeaponIconCoords, sizeof(float) * 4);
			}
		}
		else if (id == 3)
		{
			leftWeaponIconObj = __this;
			memcpy_s(leftWeaponIconCoords, sizeof(float) * 4, newRect, sizeof(float) * 4);
			if (rightWeaponIconObj)
			{
				memcpy_s(rect, sizeof(float) * 4, rightWeaponIconCoords, sizeof(float) * 4);
			}
		}
	}
	else if (vtable == vtEnemyGauge || vtable == vtPhantomGauge || vtable == vtLockonTarget)
	{
		byte* bytes = (byte*)__this;
		float* rect = (float*)(bytes + rectOffset);
		UINT width, height;
		getRenderSize(width, height);
		rect[0] = width - rect[0];
		rect[2] = width - rect[2];
		std::swap(rect[0], rect[2]);
	}
}

void RenderManager::reset()
{

}


////////// Rendering-related hooks //////////

// intercept the final render pass before UI is drawn and flip the image
void hkRenderPostProcess(void* __this, void* unk1, void* unk2)
{
	oRenderPostProcess(__this, unk1, unk2);
	if (InputManager::getInstance().toggleState)
	{
		RenderManager::getInstance().modifyPostProcess(__this, unk1, unk2);
	}
}

// modify positions of UI elements
void hkSetUIRect(void* __this, float* rect)
{
	oSetUIRect(__this, rect);
	RenderManager::getInstance().modifyUIRect(__this, rect);
}
