#pragma once

#include <Xinput.h>

typedef DWORD (WINAPI* tXInputSetState)(DWORD, XINPUT_VIBRATION*);
extern tXInputSetState oXInputSetState;

DWORD WINAPI hkXInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);