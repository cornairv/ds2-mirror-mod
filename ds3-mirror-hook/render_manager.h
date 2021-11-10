#pragma once

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

	// screen mirroring
	void mirrorScreen(ID3D11DeviceContext* ctx);
	void initResources(ID3D11Device* d3d11Dev);
	void initContext(ID3D11DeviceContext* ctx, ID3D11Device* d3d11Dev);
	void onRenderGlowFilter(ID3D11DeviceContext* ctx);
	void onEndPostEffectScene(ID3D11DeviceContext* ctx);

	// HUD
	struct GfxValue
	{
		void* unk1;
		void* unk2;
		void* objInterface;
		void* unk3;
		void* pData;
		void* unk5;
	};
	void setMovieDef(void* movieDef);
	void setMovieInstance(void* movieDef, void* movieInstance);
	void modifyDisplayInfo(void* objInterface, double*& displayInfo);
	bool shouldForceInitFirstFrame(void* movieDef);

private:
	struct gfx_resources
	{
		GfxValue hudRoot = {};
		GfxValue playerHud = {};
		GfxValue itemPanel = {};
		GfxValue lockOn = {};
		GfxValue enemyTag[8] = {{}};
		GfxValue remotePCTag[6] = {{}};
		GfxValue leftWeapon = {};
		GfxValue rightWeapon = {};
		double leftWeaponDisplayInfo[27];
		double rightWeaponDisplayInfo[27];
		void* movieDef = nullptr;
		void* movieRoot = nullptr;
	} gfx;

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
		bool didRenderGlowFilter = true;
	} mirror;
};

extern "C"
{
	void hkRenderGlowFilter(ID3D11DeviceContext* ctx);
	void hkEndPostEffectScene(ID3D11DeviceContext* ctx);
}

void* hkLoader_CreateMovie(void* __this, char* filename, unsigned int loadConstants, size_t memoryArena);
void* hkMovieDef_CreateInstance(void* __this, void* memContext, bool initFirstFrame, void* actionControl, void* queue);
bool hkValue_SetDisplayInfo(void* __this, void* pData, double* displayInfo);
