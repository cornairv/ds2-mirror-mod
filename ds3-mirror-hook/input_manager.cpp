#include "pch.h"
#include "input_manager.h"
#include "render_manager.h"
#include "addresses.h"
#include "util.h"
#include "logger.h"
#include "config.h"
#include <map>
#include <dinput.h>
#include <vector>
#include <detours/detours.h>

KeyWrapper::KeyWrapper(int keyCode) : keyCode(keyCode)
{
	down = prevDown = GetKeyState(keyCode) & 0x8000;
}

void KeyWrapper::update()
{
	bool state = GetKeyState(keyCode) & 0x8000;
	pressed = state && !down;
	released = !state && down;
	down = state;
}

void InputManager::update()
{
	if (config.toggleKey != -1)
	{
		toggleKey.update();
		if (toggleKey.pressed)
		{
			toggleState = !toggleState;

			swapInputBindings();
			if (config.invertWeaponSwitch)
			{
				RenderManager::getInstance().setInvertWeaponSwitch(toggleState);
			}
		}
	}
}

void InputManager::modifySetXInput(XINPUT_VIBRATION* pVibration)
{
	if (toggleState)
	{
		std::swap(pVibration->wLeftMotorSpeed, pVibration->wRightMotorSpeed);
	}
}

void InputManager::modifyGetXInput(XINPUT_STATE* pState)
{
	if (toggleState && config.invertDirections)
	{
		safeNegate(pState->Gamepad.sThumbLX);
	}
}

struct InputBinding
{
	int gamepad;
	int keyboard;
	int keyboardModifier;
	int mouse;
	int mouseModifier;
};

void InputManager::swapInputBindings()
{
	InputBinding* inputBindings = derefOffsets<InputBinding*>(pKeybindData, { 0 }, 0x2d * 0x14);

	if (config.invertDirections)
	{
		std::swap(inputBindings[3], inputBindings[4]);		// move left/right
		std::swap(inputBindings[11], inputBindings[12]);	// camera left/right
	}
	if (config.invertWeaponSwitch)
	{
		std::swap(inputBindings[16], inputBindings[17]);	// switch weapons
	}
	if (config.invertAttacks)
	{
		std::swap(inputBindings[18], inputBindings[20]);	// light attack
		std::swap(inputBindings[19], inputBindings[21]);	// strong attack
	}
}

void hkInitInputBinds(void* unk)
{
	if (config.invertDirections && InputManager::getInstance().toggleState)
	{
		InputManager::getInstance().swapInputBindings();
	}
	oInitInputBinds(unk);
	if (config.invertDirections && InputManager::getInstance().toggleState)
	{
		InputManager::getInstance().swapInputBindings();
	}
}

float hkGetMouseX(void* unk)
{
	float ret = oGetMouseX(unk);
	if (config.invertDirections && InputManager::getInstance().toggleState)
	{
		ret *= -1;
	}
	return ret;
}

float hkGetRightStickX(void* unk)
{
	float ret = oGetRightStickX(unk);
	if (config.invertDirections && InputManager::getInstance().toggleState)
	{
		ret *= -1;
	}
	return ret;
}

