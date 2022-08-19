#include "movement.h"

void Movement::BunnyHop(CUserCmd* cmd, C_BasePlayer* localplayer)
{
	if (!Settings::Movement::BunnyHop)
		return;

	if (cmd->buttons & IN_JUMP)
	{
		if (!(localplayer->GetFlags() & FL_ONGROUND))
		{
			cmd->buttons &= ~IN_JUMP;
		}
	}
}