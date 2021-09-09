#include "pch.h"
#include "render_manager.h"
#include "input_manager.h"
#include "addresses.h"
#include "logger.h"

void RenderManager::mirrorScreen([[maybe_unused]] void* __this, [[maybe_unused]] void* unk1, [[maybe_unused]] void* unk2)
{
	//LOG << "Render: " << std::hex << __this << "; " << unk1 << "; " << unk2 << LogEndl::INFO;
}

void RenderManager::mirrorRectPosition([[maybe_unused]] void* __this)
{

}


void RenderManager::reset()
{

}

RenderManager::ScreenQuadVertex* RenderManager::getScreenQuad()
{
	if (!screenQuad)
	{

	}
	return *screenQuad;
}


////////// Rendering-related hooks //////////

// intercept the final render pass before UI is drawn and flip the image
void hkRenderPostProcess(void* __this, void* unk1, void* unk2)
{
	if (InputManager::getInstance().toggleState)
	{
		int processType = *(int*)((byte*)__this + 0x38);
		if (processType == 0x1e || processType == 0x1f)
		{
			RenderManager::getInstance().mirrorScreen(__this, unk1, unk2);
		}
	}
	oRenderPostProcess(__this, unk1, unk2);
}