#pragma once

#include "d3d11dev.h"
#include <memory>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <map>
#include <thread>

class RenderManager
{
public:

	static RenderManager& getInstance()
	{
		static RenderManager singleton;
		return singleton;
	}
	RenderManager(RenderManager const&) = delete;
	void operator=(RenderManager const&) = delete;

	RenderManager() { }

	void reset();

	void modifyUIRect(void* __this, float* newRect);
	void modifyPostProcess(void* __this, void* unk1, void* unk2);
	void mirrorScreen(void* unk1);

	void getRenderSize(UINT& width, UINT& height);

	void setD3d11Dev(ID3D11Device* dev) { d3d11Dev = dev; }
	void setD3d11Ctxt(ID3D11DeviceContext* ctxt) { d3d11Ctxt = ctxt; }

	void initResources();
	void initContext(ID3D11DeviceContext* ctx);

	std::map<ID3D11Texture2D*, D3D11_TEXTURE2D_DESC> textureInfo;

private:

	struct mirror_resources
	{
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;
		ID3D11SamplerState* samplerState = nullptr;
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11InputLayout* vertexLayout = nullptr;
		UINT vertexStride = 0;
		UINT vertexOffset = 0;
		UINT vertexCount = 3;

		ID3D11Texture2D* srcRenderTexture = nullptr;
		ID3D11Texture2D* dstRenderTexture = nullptr;
		ID3D11ShaderResourceView* srcView = nullptr;
		ID3D11RenderTargetView* dstView = nullptr;

		bool initialized = false;
	} mirror;

	void* leftWeaponIconObj = nullptr;
	void* rightWeaponIconObj = nullptr;
	float leftWeaponIconCoords[4] = {};
	float rightWeaponIconCoords[4] = {};

	ID3D11Device* d3d11Dev = nullptr;
	ID3D11DeviceContext* d3d11Ctxt = nullptr;
};

void hkRenderPostProcess(void* __this, void* unk1, void* unk2);
void hkSetUIRect(void* __this, float* rect);
