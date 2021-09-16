#include "pch.h"
#include "fmod.h"
#include "addresses.h"
#include "input_manager.h"

int hkSet3DListenerAttributes(void* eventsystem, int listener, float* pos, float* vel, float* forward, float* up)
{
	if (InputManager::getInstance().toggleState)
	{
		// flip the up-vector to flip the audio
		for (int i = 0; i < 3; i++)
		{
			up[i] *= -1;
		}
	}
 	return oSet3DListenerAttributes(eventsystem, listener, pos, vel, forward, up);
}
