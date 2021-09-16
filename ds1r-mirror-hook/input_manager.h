#pragma once

#include <XInput.h>
#include <dinput.h>
#include <map>
#include "config.h"

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

	void modifySetXInput(XINPUT_VIBRATION* pVibration);

	void swapInputBindings();
	void swapInputBindings(long long* bindData);

	void setKeyOptionMenuState(bool state);

	void update();

	bool toggleState = true;

private:

	KeyWrapper toggleKey;
	bool keyOptionMenuOpen = false;
};

void hkSetupInputBinds(void* __this, void* pBindData);
void* hkMenuKeyOptionConstructor(void* __this, void* unk1, void* unk2, void* unk3);
void* hkMenuKeyOptionDestructor(void* __this, void* unk1, void* unk2, void* unk3);
