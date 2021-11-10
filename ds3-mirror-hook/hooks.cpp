#include "pch.h"
#include "hooks.h"
#include "d3d11.h"
#include "xinput.h"
#include "fmod.h"
#include "render_manager.h"
#include "input_manager.h"
#include "addresses.h"
#include "logger.h"
#include "util.h"
#include <detours/detours.h>

#define ATTACH_HOOK(name) CHECK(DetourAttach(&(PVOID&)o##name, hk##name))

extern "C"
{
	void hkRenderGlowFilterTrampoline();
}

void setupHooks()
{
	CHECK(DetourTransactionBegin());
	CHECK(DetourUpdateThread(GetCurrentThread()));

	// rendering
	//ATTACH_HOOK(D3D11CreateDevice);
	//ATTACH_HOOK(RenderGlowFilter);
	CHECK(InjectCode((void*)0x1401bc3fb, hkRenderGlowFilterTrampoline));
	//ATTACH_HOOK(GetMatrix);
	//ATTACH_HOOK(GetMatrixInverse);
	ATTACH_HOOK(Loader_CreateMovie);
	ATTACH_HOOK(MovieDef_CreateInstance);
	//ATTACH_HOOK(MovieRoot_GetVariable);
	//ATTACH_HOOK(Value_GetMember);
	ATTACH_HOOK(Value_SetDisplayInfo);
	//ATTACH_HOOK(Value_GetDisplayInfo);

	CHECK(DetourTransactionCommit());
}