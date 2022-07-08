#pragma once
#include "interfaces.h"
#include "C_BasePlayer.h"
#include "csgo.h"
#include "CUserCmd.h"

class Vector;

namespace Aim
{
	extern C_BasePlayer* Target;
	extern Vector RCSOffset;

	extern Vector& Aimbot(CUserCmd* cmd, C_BasePlayer* localplayer);
	extern C_BasePlayer* GetBestTarget(CUserCmd* cmd, C_BasePlayer* localplayer);
	extern void RecoilControl(CUserCmd* cmd, C_BasePlayer* localplayer, Vector& vec, bool isAimbot = false);
}