#include "esp.h"
#include <string>
#include "settings.h"

void ESP::DrawFOVHelp(C_BasePlayer* ply, C_BasePlayer* localplayer)
{
	matrix3x4_t bones[128];
	ply->SetupBones(bones, 128, 0x7FF00, g_Globals->curtime);

	Vector headPos = bones[8].GetOrigin();
	Vector headScreenPos;
	I::IDebugOverlay->ScreenPosition(headPos, headScreenPos);


	// center x center y
	float cx = scrw / 2.f;
	float cy = scrh / 2.f;


	float diffX = headScreenPos.x - cx;
	float diffY = headScreenPos.y - cy;

	float hypotenuse = ((diffX * diffX) + (diffY * diffY));


	if (hypotenuse < Settings::Aim::FOVLength)
		I::ISurface->SetDrawColor(0, 255, 0);
	else
		I::ISurface->SetDrawColor(255, 0, 0);

	I::ISurface->DrawLine(cx, cy, cx + diffX, cy + diffY);
	I::ISurface->DrawLine(cx, cy, cx + diffX, cy);
	I::ISurface->DrawLine(cx + diffX, cy, cx + diffX, cy + diffY);

	I::ISurface->DrawPrintText(std::to_string(hypotenuse).c_str(), cx + (diffX / 2), cy + (diffY / 2));
}