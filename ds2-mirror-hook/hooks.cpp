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
	void hkEndPostEffectSceneTrampoline();
}

void setupHooks()
{
	CHECK(DetourTransactionBegin());
	CHECK(DetourUpdateThread(GetCurrentThread()));

	// rendering
	CHECK(InjectCode(midRenderGlowFilter, hkRenderGlowFilterTrampoline));
	CHECK(InjectCode(midEndPostEffectScene, hkEndPostEffectSceneTrampoline));

	// UI
	ATTACH_HOOK(Loader_CreateMovie);
	ATTACH_HOOK(MovieDef_CreateInstance);
	ATTACH_HOOK(Value_SetDisplayInfo);

	// input
	ATTACH_HOOK(InitInputBinds);

	// audio
	ATTACH_HOOK(Set3DListenerAttributes);

	CHECK(DetourTransactionCommit());
}

// hooks that need to be set up after code is decrypted
void setupLateHooks()
{
	CHECK(DetourTransactionBegin());
	CHECK(DetourUpdateThread(GetCurrentThread()));

	// input
	ATTACH_HOOK(GetMouseX);
	ATTACH_HOOK(GetRightStickX);
	ATTACH_HOOK(XInputGetState);
	ATTACH_HOOK(XInputSetState);

	CHECK(DetourTransactionCommit());
}
