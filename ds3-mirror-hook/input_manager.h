#pragma once

#include <dinput.h>
#include <map>
#include "xinput.h"
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
	void modifyGetXInput(XINPUT_STATE* pState);

	void swapInputBindings();

	void update();

	bool toggleState = true;

private:

	KeyWrapper toggleKey;
};

void hkInitInputBinds(void* unk);
float hkGetMouseX(void* unk);
float hkGetRightStickX(void* unk);
