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
ADDRESS(tEventSystem_Create, oEventSystem_Create, 0x14103b138);


// misc
ADDRESS(byte**, pGameData, 0x141d278f0);

long long hashCheckCmps[] =
{
	0x1429c74be,
	0x14268e016,
	0
};