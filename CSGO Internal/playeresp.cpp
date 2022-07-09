#include "esp.h"

void ESP::DrawPlayer(C_BasePlayer* player, C_BasePlayer* localplayer, player_info_t playerinfo)
{
	bool bSameTeam = player->GetTeam() == localplayer->GetTeam();

	matrix3x4_t bones[128];
	if (!player->SetupBones(bones, 128, 0x7FF00, g_Globals->curtime))
		return;

	static Vector VECTOR_HEADOFFSET = Vector(0, 0, 14);
	static Vector VECTOR_FEETOFFSET = Vector(0, 0, -8);

	Vector feetScreenPos;
	Vector feetPos = player->GetABSOrigin();
	feetPos = feetPos + VECTOR_FEETOFFSET;
	if (I::IDebugOverlay->ScreenPosition(feetPos, feetScreenPos))
		return;

	Color col = bSameTeam ? COLOR_GREEN : COLOR_RED;

	Vector headScreenPos;
	Vector headPos = bones[8].GetOrigin();
	headPos = headPos + VECTOR_HEADOFFSET;

	I::IDebugOverlay->ScreenPosition(headPos, headScreenPos);


	float height = feetScreenPos.y - headScreenPos.y;
	float width = height * 0.44;

	float offset = (width / 2);

	float left = headScreenPos.x - offset;
	float top = headScreenPos.y;
	float right = headScreenPos.x + offset;
	float bottom = headScreenPos.y + height;

	I::ISurface->SetDrawColor(col.r, col.g, col.b, 255);

	I::ISurface->DrawLine(left, top, right, top);
	I::ISurface->DrawLine(right, top, right, bottom);

	I::ISurface->DrawLine(right, bottom, left, bottom);
	I::ISurface->DrawLine(left, bottom, left, top);


	int textWidth, textHeight;
	I::ISurface->GetTextSize(293, playerinfo.name, textWidth, textHeight);
	I::ISurface->DrawPrintText(playerinfo.name, left + (((right - left)/2) - textWidth/2), feetScreenPos.y, 293, col);
}