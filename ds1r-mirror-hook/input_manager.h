#pragma once

#include <XInput.h>
#include <dinput.h>
#include <map>
#include "config.h"

struct KeyBinding
{
	UINT modCode;	// 0x12c = no modifier
	UINT code;		// bit 3: 0 = keyboard, 1 = mouse
};

class KeyWrapper
{
public:
	KeyWrapper(int keyCode);
	void update();
	bool down = false;
	bool pressed = false;
	bool released = false;

private:
	int keyCode;
	bool prevDown = false;
};

class InputManager
{
public:

	static InputManager& getInstance()
	{
		static InputManager singleton;
		return singleton;
	}
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	InputManager() : toggleKey(config.toggleKey) { }

	void modifyDirectInput(DWORD cbData, LPVOID lpvData);
	void modifyGetXInput(XINPUT_STATE* pState);
	void modifySetXInput(XINPUT_VIBRATION* pVibration);
	void modifyWeaponIcons(void* obj);

	void swapInputBindings();
	void swapInputBindings(long long* bindData);

	void setKeyOptionMenuState(bool state);

	bool toggleState = true;

private:
	void modifyMouseInput(DIMOUSESTATE2* state);
	void modifyKeyboardInput(byte* state);
	bool getKeyBinding(int index, int& key, int& modifier);

	bool rightClicking = false;
	bool leftClicking = false;
	static std::map<int, int> keyMap;
	static std::map<int, int> modifierKeyMap;
	float* leftWeaponCoords = nullptr;
	float* rightWeaponCoords = nullptr;
	KeyWrapper toggleKey;
	bool keyOptionMenuOpen = false;
};

int __fastcall hkPropagateKeybinds(void* inputStructure);
void __fastcall hkSetup_FrpgMenuDlgFeShortcut(void* __this, int __edx, void* unk1, void* unk2, void* unk3);

void hkUpdateInput(void* __this, void* unk);
void hkSetupInputBinds(void* __this, void* pBindData);
void* hkMenuKeyOptionConstructor(void* __this, void* unk1, void* unk2, void* unk3);
void* hkMenuKeyOptionDestructor(void* __this, void* unk1, void* unk2, void* unk3);
void* hkMenuLoadInputBinds(void* dst, void* src);


bool isMenuOpen();
unsigned int getIngameTime();
