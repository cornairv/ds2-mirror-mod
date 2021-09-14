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

void setupHooks()
{
	// patch executable hash checks (crashes game if hash mismatches)
	for (long long* ptr = hashCheckCmps; *ptr != 0; ptr++)
	{
		PatchCmp((void*)*ptr);
	}

	CHECK(DetourTransactionBegin());
	CHECK(DetourUpdateThread(GetCurrentThread()));

	// rendering
	ATTACH_HOOK(D3D11CreateDevice);
	ATTACH_HOOK(RenderPostProcess);
	//ATTACH_HOOK(SetLockonRect);
	//ATTACH_HOOK(SetEnemyRect);
	//ATTACH_HOOK(SetPhantomRect);

	// input
	ATTACH_HOOK(XInputGetState);
	ATTACH_HOOK(SetupInputBinds);
	ATTACH_HOOK(MenuKeyOptionConstructor);
	ATTACH_HOOK(MenuKeyOptionDestructor);
	//ATTACH_HOOK(XInputSetState);
	//ATTACH_HOOK(UpdateUIElement);
	ATTACH_HOOK(SetUIRect);

	// audio
	//ATTACH_HOOK(EventSystem_Create);

	CHECK(DetourTransactionCommit());
}