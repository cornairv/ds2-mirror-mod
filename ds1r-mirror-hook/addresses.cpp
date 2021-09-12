#include "pch.h"
#include "addresses.h"

#define ADDRESS(type, name, address) type name = reinterpret_cast<type>(address)

// rendering
ADDRESS(tSetFloatingRect, oSetLockonRect, 0x00c82a80);
ADDRESS(tSetFloatingRect, oSetEnemyRect, 0x00fae900);
ADDRESS(tSetFloatingRect, oSetPhantomRect, 0x00fa8c90);
ADDRESS(tRenderPostProcess, oRenderPostProcess, 0x14045ed20);
ADDRESS(byte**, pFrpgWindow, 0x141d06ef8);

// input
ADDRESS(tSetup_FrpgMenuDlgFeShortcut, oSetup_FrpgMenuDlgFeShortcut, 0x00c82f00);
ADDRESS(tGetMenuState, oGetMenuState, 0x00c2abe0);
ADDRESS(tPropagateKeybinds, oPropagateKeybinds, 0x00f73ff0);
ADDRESS(tVoidFunc, oOncePerFrame, 0x00BAC020);
ADDRESS(byte**, pMenuManager, 0x013786d0);
ADDRESS(byte**, pGameDataManager, 0x01378700);
ADDRESS(byte**, pBindingManager, 0x141d52790);
ADDRESS(tUpdateInput, oUpdateInput, 0x14017f0a0);
ADDRESS(tSetupInputBinds, oSetupInputBinds, 0x140c8ec50);
ADDRESS(tMenuKeyOptionConstructor, oMenuKeyOptionConstructor, 0x14013e9e0);
ADDRESS(tMenuKeyOptionDestructor, oMenuKeyOptionDestructor, 0x1401456c0);
ADDRESS(tMenuLoadInputBinds, oMenuLoadInputBinds, 0x140145350);

// audio
ADDRESS(tEventSystem_Create, oEventSystem_Create, 0x006ed0ee);

// misc
long long hashCheckCmps[] =
{
	0x1429c74be,
	0x14268e016,
	0
};