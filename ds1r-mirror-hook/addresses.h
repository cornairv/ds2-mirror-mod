#pragma once

#include "pch.h"

// rendering
typedef void(__thiscall* tSetFloatingRect)(void*, float);
extern tSetFloatingRect oSetLockonRect;
extern tSetFloatingRect oSetEnemyRect;
extern tSetFloatingRect oSetPhantomRect;

typedef void(*tRenderPostProcess)(void*, void*, void*);
extern tRenderPostProcess oRenderPostProcess;

typedef void(*tSetUIRect)(void*, float*);
extern tSetUIRect oSetUIRect;
extern byte** pFrpgWindow;
extern void* vtWeaponSwitchIcons;
extern void* vtEnemyGauge;
extern void* vtPhantomGauge;
extern void* vtLockonTarget;


// input
typedef void(*tSetupInputBinds)(void*, void*);
extern tSetupInputBinds oSetupInputBinds;

typedef void* (*tMenuKeyOptionConstructor)(void*, void*, void*, void*);
extern tMenuKeyOptionConstructor oMenuKeyOptionConstructor;

typedef void*(*tMenuKeyOptionDestructor)(void*, void*, void*, void*);
extern tMenuKeyOptionDestructor oMenuKeyOptionDestructor;

extern byte** pBindingManager;


// audio
typedef int(*tEventSystem_Create)(void**);
extern tEventSystem_Create oEventSystem_Create;


// misc
extern byte** pGameData;
extern long long hashCheckCmps[];