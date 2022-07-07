#pragma once
#include "esp.h"

void ESP::DrawFOVCircle(C_BasePlayer* localplayer)
{
	if (!localplayer) return;

	float segSize = ((float)scrw / (float)localplayer->GetFOV())/2;

	int fov = 15;


	int radius = fov * segSize;

	I::ISurface->SetDrawColor(255, 255, 255, 255);
	I::ISurface->DrawOutlinedCircle(scrw / 2, scrh / 2, radius, 64);
}