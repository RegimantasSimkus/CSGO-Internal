#include "OverrideView.h"
#include <iostream>
#include "camera.h"
#include "interfaces.h"
#include "esp.h"

tOverrideView oOverrideView;
int __fastcall hkOverrideView(void* pThis, void* _, CViewSetup* view)
{
	// calling this first to ensure that our variables are what is used
	// not sure if there are any downsides to this though
	int ret = oOverrideView(pThis, view); 
	if (!Settings::Camera::Enabled)
		return ret;

	// sets the FOV
	//*(float*)((uintptr_t)view + 0xB0) = 120.f;

	// we can be 6'6
	//Vector& origin = *(Vector*)((uintptr_t)view + 0xB8);
	//origin.z += 18;

	// tilt head sideways/apply roll
	//Vector& angles = *(Vector*)((uintptr_t)view + 0xC4);
	//angles.z = 10;

	Camera::SetupFOV(view);


	return ret;
}
