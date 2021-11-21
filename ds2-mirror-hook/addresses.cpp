#include "pch.h"
#include "addresses.h"

#define ADDRESS(type, name, address) type name = reinterpret_cast<type>(address)

// rendering
ADDRESS(void*, midRenderGlowFilter, 0x1401bc3fb);
ADDRESS(void*, midEndPostEffectScene, 0x1417137b1);

//ui
ADDRESS(tLoader_CreateMovie, oLoader_CreateMovie, 0x141ba8200);
ADDRESS(tMovieDef_CreateInstance, oMovieDef_CreateInstance, 0x141bded00);
ADDRESS(tMovieRoot_GetVariable, oMovieRoot_GetVariable, 0x141ef5300);
ADDRESS(tValue_GetMember, oValue_GetMember, 0x141eef440);
ADDRESS(tValue_SetDisplayInfo, oValue_SetDisplayInfo, 0x141f13870);
ADDRESS(tValue_GetDisplayInfo, oValue_GetDisplayInfo, 0x141eedd90);

// input
ADDRESS(tInitInputBinds, oInitInputBinds, 0x14057b950);
ADDRESS(tGetMouseX, oGetMouseX, 0x1407f4dc0);
ADDRESS(tGetRightStickX, oGetRightStickX, 0x1407f5b50);
ADDRESS(void*, pKeybindData, 0x144740090);

// audio
ADDRESS(tSet3DListenerAttributes, oSet3DListenerAttributes, 0x141a55ee6);

/* unused
ADDRESS(tRenderGlowFilter, oRenderGlowFilter, 0x1401bb790);
ADDRESS(void*, pGameDataMan, 0x144740178);
*/

ADDRESS(tGetShader, oGetShader, 0x140af2420);
ADDRESS(tRenderPass, oRenderPass, 0x140962b40);
ADDRESS(tAddAntiAliasingPass, oAddAntiAliasingPass, 0x140b83fe0);
ADDRESS(tDraw, oDraw, 0x140f1cb10);
