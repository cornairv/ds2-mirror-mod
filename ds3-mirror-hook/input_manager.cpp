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
			
			/*
			swapInputBindings();
			toggleState = !toggleState;
			if (config.invertWeaponSwitch)
			{
				RenderManager::getInstance().setInvertWeaponSwitch(toggleState);
			}
			if (!keyOptionMenuOpen)
			{
			}
			*/
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

void InputManager::modifyDirectInput(DWORD cbData, [[maybe_unused]] LPVOID lpvData)
{
	LOG << "cbData: " << cbData << LogEndl::INFO;
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
	InputBinding* inputBindings = derefOffsets<InputBinding*>(pKeybindData, { }, 0x2d * 0x14);
	//byte* invertMouseXAxis = derefOffsets<byte*>(pKeybindData, { }, 0x715);
	//byte* invertGamepadXAxis = derefOffsets<byte*>(pGameDataMan, { 0, 0x58 }, 0x12);

	if (config.invertDirections)
	{
		std::swap(inputBindings[3], inputBindings[4]);		// move left/right
		std::swap(inputBindings[11], inputBindings[12]);	// camera left/right
		//*invertMouseXAxis ^= 1;
		//*invertGamepadXAxis ^= 1;
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

void InputManager::setSwapInputBindings(bool swap)
{
	if (swap != inputSwapped)
	{
		swapInputBindings();
		inputSwapped = swap;
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

unsigned long long hkApplyInputSettings(void* __this, unsigned int unk)
{
	InputManager::getInstance().swapInputBindings();
	unsigned long long ret = oApplyInputSettings(__this, unk);
	InputManager::getInstance().swapInputBindings();
	return ret;
}

int* hkGetInputBindings(int* bindings)
{
	InputManager::getInstance().setSwapInputBindings(false);
	int* ret = oGetInputBindings(bindings);
	InputManager::getInstance().setSwapInputBindings(true);
	return ret;
}
void hkSetInputBindings(int* bindings)
{
	InputManager::getInstance().setSwapInputBindings(false);
	oSetInputBindings(bindings);
	InputManager::getInstance().setSwapInputBindings(true);
}

void* hkInitInputBinds(void* unk)
{
	void* ret = oInitInputBinds(unk);
	InputManager::getInstance().swapInputBindings();
	LOG << "InitInputBinds" << LogEndl::INFO;
	return ret;
}

bool hkInitInputBinds2(void* unk1, void* unk2)
{
	InputManager::getInstance().setSwapInputBindings(false);
	LOG << "InitInputBinds2" << LogEndl::INFO;
	bool ret = oInitInputBinds2(unk1, unk2);
	return ret;
}

void hkInitInputBinds3(void* unk)
{
	if (config.invertDirections && InputManager::getInstance().toggleState)
	{
		InputManager::getInstance().setSwapInputBindings(true);
	}
	oInitInputBinds3(unk);
	if (config.invertDirections && InputManager::getInstance().toggleState)
	{
		InputManager::getInstance().setSwapInputBindings(false);
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

