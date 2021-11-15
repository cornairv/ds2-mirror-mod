#include "pch.h"
#include "addresses.h"

#define ADDRESS(type, name, address) type name = reinterpret_cast<type>(address)

// rendering
ADDRESS(tRenderPostProcess, oRenderPostProcess, 0x14045ed20);
ADDRESS(byte**, pFrpgWindow, 0x141d06ef8);
ADDRESS(tSetUIRect, oSetUIRect, 0x140ed4010);
ADDRESS(void*, vtEnemyGauge, 0x1413aaaa0);
ADDRESS(void*, vtPhantomGauge, 0x1413c4738);
ADDRESS(void*, vtLockonTarget, 0x1413ad2d0);


// input
ADDRESS(byte**, pBindingManager, 0x141d52790);
ADDRESS(tSetupInputBinds, oSetupInputBinds, 0x140c8ec50);
ADDRESS(tMenuKeyOptionConstructor, oMenuKeyOptionConstructor, 0x14013e9e0);
ADDRESS(tMenuKeyOptionDestructor, oMenuKeyOptionDestructor, 0x1401456c0);
ADDRESS(void*, vtWeaponSwitchIcons, 0x1413abc30);


// audio
ADDRESS(tSet3DListenerAttributes, oSet3DListenerAttributes, 0x141a55ee6);


// misc
ADDRESS(byte**, pGameData, 0x141d278f0);

long long hashCheckCmps[] =
{
	0x1429c74be,
	0x14268e016,
	0
};



ADDRESS(tRenderGlowFilter, oRenderGlowFilter, 0x1401bb790);
ADDRESS(tGetMatrix, oGetMatrix, 0x141bc22d0);
ADDRESS(tGetMatrix, oGetMatrixInverse, 0x141bc2260);
ADDRESS(tLoader_CreateMovie, oLoader_CreateMovie, 0x141ba8200);
ADDRESS(tMovieDef_CreateInstance, oMovieDef_CreateInstance, 0x141bded00);
ADDRESS(tMovieRoot_GetVariable, oMovieRoot_GetVariable, 0x141ef5300);
ADDRESS(tValue_GetMember, oValue_GetMember, 0x141eef440);
ADDRESS(tValue_SetDisplayInfo, oValue_SetDisplayInfo, 0x141f13870);
ADDRESS(tValue_GetDisplayInfo, oValue_GetDisplayInfo, 0x141eedd90);

ADDRESS(void*, midRenderGlowFilter, 0x1401bc3fb);
ADDRESS(void*, midEndPostEffectScene, 0x1417137b1);

ADDRESS(void*, pKeybindData, 0x7FF3FB059930);//0x144740090);
ADDRESS(void*, pGameDataMan, 0x144740178);
ADDRESS(tApplyInputSettings, oApplyInputSettings, 0x14057b370);

ADDRESS(tSetInputBindings, oSetInputBindings, 0x140ab15f0);
ADDRESS(tGetInputBindings, oGetInputBindings, 0x140aaf010);
ADDRESS(tInitInputBinds, oInitInputBinds, 0x14057ae80);
ADDRESS(tInitInputBinds2, oInitInputBinds2, 0x14057b520);
ADDRESS(tInitInputBinds3, oInitInputBinds3, 0x14057b950);
ADDRESS(tGetMouseX, oGetMouseX, 0x1407f4dc0);
ADDRESS(tGetRightStickX, oGetRightStickX, 0x1407f5b50);
