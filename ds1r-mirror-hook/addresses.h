#pragma once

#include "pch.h"

// rendering
typedef void(__thiscall* tSetFloatingRect)(void*, float);
extern tSetFloatingRect oSetLockonRect;
extern tSetFloatingRect oSetEnemyRect;
extern tSetFloatingRect oSetPhantomRect;

typedef void(*tRenderPostProcess)(void*, void*, void*);
extern tRenderPostProcess oRenderPostProcess;

extern byte** pFrpgWindow;


// input
typedef int(__fastcall* tPropagateKeybinds)(void*);
extern tPropagateKeybinds oPropagateKeybinds;

typedef void(*tSetup_FrpgMenuDlgFeShortcut)(void*, int, void*, void*);
extern tSetup_FrpgMenuDlgFeShortcut oSetup_FrpgMenuDlgFeShortcut;

typedef int(__stdcall* tGetMenuState)();
extern tGetMenuState oGetMenuState;

typedef void(__stdcall* tVoidFunc)();
extern tVoidFunc oOncePerFrame;

typedef void(*tSetupInputBinds)(void*, void*);
extern tSetupInputBinds oSetupInputBinds;

typedef void* (*tMenuKeyOptionConstructor)(void*, void*, void*, void*);
extern tMenuKeyOptionConstructor oMenuKeyOptionConstructor;

typedef void*(*tMenuKeyOptionDestructor)(void*, void*, void*, void*);
extern tMenuKeyOptionDestructor oMenuKeyOptionDestructor;

typedef void* (*tMenuLoadInputBinds)(void*, void*);
extern tMenuLoadInputBinds oMenuLoadInputBinds;

typedef void(*tUpdateUIElement)(void*, void*);
extern tUpdateUIElement oUpdateUIElement;

typedef void(*tSetUIRect)(void*, float*);
extern tSetUIRect oSetUIRect;

extern void* vtWeaponSwitchIcons;
extern void* vtEnemyGauge;
extern void* vtPhantomGauge;
extern void* vtLockonTarget;

extern byte** pMenuManager;
extern byte** pGameDataManager;
extern byte** pBindingManager;


// audio
typedef int(__stdcall* tEventSystem_Create)(void**);
extern tEventSystem_Create oEventSystem_Create;


// misc
extern long long hashCheckCmps[];