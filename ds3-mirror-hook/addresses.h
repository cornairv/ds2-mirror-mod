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
typedef int(*tSet3DListenerAttributes)(void*, int, void*, void*, void*, void*);
extern tSet3DListenerAttributes oSet3DListenerAttributes;


// misc
extern byte** pGameData;
extern long long hashCheckCmps[];



typedef void* (*tRenderGlowFilter)(void*, void*, void*);
extern tRenderGlowFilter oRenderGlowFilter;

typedef bool (*tGetMatrix)(void*, float*);
extern tGetMatrix oGetMatrix;
extern tGetMatrix oGetMatrixInverse;

typedef void* (*tLoader_CreateMovie)(void*, char*, unsigned int, size_t);
extern tLoader_CreateMovie oLoader_CreateMovie;

typedef void* (*tMovieDef_CreateInstance)(void*, void*, bool, void*, void*);
extern tMovieDef_CreateInstance oMovieDef_CreateInstance;

typedef bool (*tMovieRoot_GetVariable)(void*, void*, const char*);
extern tMovieRoot_GetVariable oMovieRoot_GetVariable;

typedef bool (*tValue_GetMember)(void* __this, void* pData, const char* name, void* member, bool isDisplayObj);
extern tValue_GetMember oValue_GetMember;

typedef bool (*tValue_SetDisplayInfo)(void* __this, void* pData, double* matrix);
extern tValue_SetDisplayInfo oValue_SetDisplayInfo;

typedef bool (*tValue_GetDisplayInfo)(void* __this, void* pData, double* matrix);
extern tValue_GetDisplayInfo oValue_GetDisplayInfo;