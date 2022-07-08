#pragma once
#include "interfaces.h"
#include "C_BasePlayer.h"
#include "csgo.h"

namespace ESP
{
	extern int scrw;
	extern int scrh;

	static Color COLOR_RED = Color(255, 0, 0, 255);
	static Color COLOR_GREEN = Color(0, 255, 0, 255);
	static Color COLOR_BLUE = Color(0, 0, 255, 255);
	static Color COLOR_WHITE = Color(255, 255, 255, 255);
	static Color COLOR_BLACK = Color(0, 0, 0, 255);

	extern void DrawFOVCircle(C_BasePlayer* localplayer);
	extern void DrawPlayer(C_BasePlayer* player, C_BasePlayer* localplayer, player_info_t playerinfo);
	extern float GetFOVRadius(float& fov, C_BasePlayer* localplayer = nullptr);
	extern void DrawFOVHelp(C_BasePlayer* ply, C_BasePlayer* localplayer);
}