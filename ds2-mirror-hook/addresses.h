#pragma once

#include "pch.h"

// rendering
extern void* midRenderGlowFilter;
extern void* midEndPostEffectScene;

// ui
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

// input
typedef void (*tInitInputBinds)(void* unk);
extern tInitInputBinds oInitInputBinds;

typedef float (*tGetMouseX)(void* unk);
extern tGetMouseX oGetMouseX;

typedef float (*tGetRightStickX)(void* unk);
extern tGetRightStickX oGetRightStickX;

extern void* pKeybindData;

// audio
typedef int(*tSet3DListenerAttributes)(void*, int, void*, void*, void*, void*);
extern tSet3DListenerAttributes oSet3DListenerAttributes;

/* unused
typedef void* (*tRenderGlowFilter)(void*, void*, void*);
extern tRenderGlowFilter oRenderGlowFilter;
extern void* pGameDataMan;
*/
