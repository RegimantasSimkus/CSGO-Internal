#pragma once
#include "interfaces.h"
#include "C_BasePlayer.h"
#include "csgo.h"
#include "CUserCmd.h"
#include "settings.h"

class Vector;

namespace Aim
{
	struct backtrack_t
	{
		int index = 0;
		Vector headPos;
		int tick;
	};

	extern std::vector<backtrack_t> backtrackData[64];

	extern C_BasePlayer* Target;
	extern Vector RCSOffset;

	extern Vector& Aimbot(CUserCmd* cmd, C_BasePlayer* localplayer);
	extern C_BasePlayer* GetBestTarget(CUserCmd* cmd, C_BasePlayer* localplayer);
	extern void RecoilControl(CUserCmd* cmd, C_BasePlayer* localplayer, Vector& vec, bool isAimbot = false);
	extern void Backtrack(CUserCmd* cmd, C_BasePlayer* localplayer);
}