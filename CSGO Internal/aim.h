#pragma once
#include "interfaces.h"
#include "C_BasePlayer.h"
#include "csgo.h"
#include "CUserCmd.h"

namespace Aim
{
	static C_BasePlayer* Target = nullptr;

	extern Vector& Aimbot(CUserCmd* cmd, C_BasePlayer* localplayer);
	extern C_BasePlayer* GetBestTarget(CUserCmd* cmd, C_BasePlayer* localplayer);
	extern void RecoilControl(CUserCmd* cmd, C_BasePlayer* localplayer, Vector& vec);
}