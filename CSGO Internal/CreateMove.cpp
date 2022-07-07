#include "CreateMove.h"
#include "movement.h"
#include "aim.h"

tCreateMove oCreateMove = 0;
bool __stdcall hkCreateMove(float flSampleTime, CUserCmd* cmd)
{
	const bool ret = oCreateMove(flSampleTime, cmd);
	if (cmd->command_number == 0)
		return ret;

	C_BasePlayer* localplayer = (C_BasePlayer*)I::IEntityList->GetClientEntity(I::IEngineClient->GetLocalPlayer());

	Movement::BunnyHop(cmd, localplayer);


	Vector aimAngles = Aim::Aimbot(cmd, localplayer);

	cmd->viewangles = aimAngles;

	return true;
}