#pragma once
#include "interfaces.h"
#include "C_BasePlayer.h"
#include "csgo.h"
#include "settings.h"
#include "draw.h"

namespace ESP
{
	using namespace ImGui::Draw;

	extern int scrw;
	extern int scrh;

	extern float GetFOVRadius(float& fov, C_BasePlayer* localplayer = nullptr);
	
	extern void DrawVisuals();
	extern void DrawFOVCircle(C_BasePlayer* localplayer);
	extern void DrawPlayer(C_BasePlayer* player, C_BasePlayer* localplayer, player_info_t playerinfo);
	extern void DrawFOVHelp(C_BasePlayer* ply, C_BasePlayer* localplayer);
}