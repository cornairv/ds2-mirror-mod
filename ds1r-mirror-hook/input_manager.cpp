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
			if (!keyOptionMenuOpen)
			{
				swapInputBindings();
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

void InputManager::swapInputBindings()
{
	byte* bindingManager = *pBindingManager;
	byte* bindingsStart = *(byte**)(bindingManager + 0x8);
	byte* bindingsEnd = *(byte**)(bindingManager + 0x10);
	for (byte* currentBinding = bindingsStart; currentBinding < bindingsEnd; currentBinding += 0x148)
	{
		//int inputType = *(int*)(currentBinding + 0x88);
		long long* bindData = *(long long**)currentBinding;
		swapInputBindings(bindData);
	}
}

void InputManager::swapInputBindings(long long* bindData)
{
	if (config.invertDirections)
	{
		std::swap(bindData[2], bindData[3]);	// move left/right
		std::swap(bindData[6], bindData[7]);	// camera left/right
	}
	if (config.invertWeaponSwitch)
	{
		std::swap(bindData[10], bindData[11]);	// switch weapons
	}
	if (config.invertAttacks)
	{
		std::swap(bindData[14], bindData[16]);	// light attack/block
		std::swap(bindData[15], bindData[17]);	// heavy attack/parry
	}
}

void InputManager::setKeyOptionMenuState(bool state)
{
	keyOptionMenuOpen = state;
	if (InputManager::getInstance().toggleState)
	{
		swapInputBindings();
	}
}

void hkSetupInputBinds(void* __this, void* pBindData)
{
	if (InputManager::getInstance().toggleState)
	{
		long long* bindData = *(long long**)pBindData;
		InputManager::getInstance().swapInputBindings(bindData);
	}
	oSetupInputBinds(__this, pBindData);
}

void* hkMenuKeyOptionConstructor(void* __this, void* unk1, void* unk2, void* unk3)
{
	InputManager::getInstance().setKeyOptionMenuState(true);
	return oMenuKeyOptionConstructor(__this, unk1, unk2, unk3);
}

void* hkMenuKeyOptionDestructor(void* __this, void* unk1, void* unk2, void* unk3)
{
	void* ret = oMenuKeyOptionDestructor(__this, unk1, unk2, unk3);
	InputManager::getInstance().setKeyOptionMenuState(false);
	return ret;
}
