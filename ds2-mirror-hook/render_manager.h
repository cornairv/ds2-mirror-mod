#pragma once

#include <memory>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <map>
#include <thread>
#include <wrl/client.h>
#include <string>

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

	void onGetShader(void* shader, std::wstring name);

	// screen mirroring
	void mirrorScreen(ID3D11DeviceContext* ctx);
	void initResources(ID3D11Device* d3d11Dev);
	void initContext(ID3D11DeviceContext* ctx, ID3D11Device* d3d11Dev);
	void onRenderGlowFilter(ID3D11DeviceContext* ctx);
	void onEndPostEffectScene(ID3D11DeviceContext* ctx);
	void onRenderPass(void* drawCtx);
	bool shouldSkipDraw(ID3D11DeviceContext* ctx);
	void onDraw(ID3D11DeviceContext* ctx);
	void setAntiAliasingEnabled(bool* enabled);

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
	void setInvertWeaponSwitch(bool swap);

private:

	ID3D11PixelShader* antiAliasingShader = nullptr;
	bool antiAliasingEnabled = false;

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
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> vertexLayout;
		UINT vertexStride = 0;
		UINT vertexOffset = 0;
		UINT vertexCount = 3;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> srcRenderTexture;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> dstRenderTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srcView;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> dstView;

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

void* hkGetShader(void* unk, wchar_t* name);
bool hkRenderPass(void* param1, int param2, int param3, void* param4, int param5);
void hkAddAntiAliasingPass(void* param1, void* param2, int param3, int param4, void* param5);
void hkDraw(ID3D11DeviceContext** pCtx, void* unk, UINT VertexCount, UINT StartVertexCount);
