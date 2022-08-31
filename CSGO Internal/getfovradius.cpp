#include "esp.h"
#include "CSetupView.h"

float ESP::GetFOVRadius(float& fov, C_BasePlayer* localplayer)
{
	// localplayer should never really be a nullptr anyway as we won't need it when we're not valid
	if (!localplayer) { localplayer = I::IEntityList->GetClientEntity(I::IEngineClient->GetLocalPlayer()); }

	if (!localplayer)
		return 0.f;

	float segSize = ((float)scrw / ((Settings::Camera::ViewSetup != nullptr) ? Settings::Camera::ViewSetup->fov : localplayer->GetFOV()));
	
	return (fov * segSize)/2.f;
}