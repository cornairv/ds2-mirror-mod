#pragma once

#include <memory>
#include <d3d11.h>
#include <d3dcompiler.h>

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

	void mirrorRectPosition(void* __this);
	void mirrorScreen(void* __this, void* unk1, void* unk2);

private:
	// lazy initialize resources
	typedef struct
	{
		float x, y, z, u, v;
	} ScreenQuadVertex;
	ID3D11VertexShader* getMirrorVertexShader();
	ID3D11PixelShader* getMirrorPixelShader();
	ScreenQuadVertex* getScreenQuad();
	std::unique_ptr<ScreenQuadVertex*> screenQuad = nullptr;
};

void hkRenderPostProcess(void* __this, void* unk1, void* unk2);
