#include "aim.h"

std::vector<Aim::backtrack_t> Aim::backtrackData[64] = {};

void Aim::Backtrack(CUserCmd* cmd, C_BasePlayer* localplayer)
{
	//Vector localpos = localplayer->GetOrigin() + localplayer->GetViewOffset();
	for (int i = 1; i < g_Globals->maxClients; i++)
	{
		if (backtrackData[i].size() > 8)
		{
			backtrackData[i].pop_back();
			continue;
		}

		C_BasePlayer* player = I::IEntityList->GetClientEntity(i);

		if (!player) continue;
		if (player->IsDormant()) continue;
		if (player->GetHealth() <= 0) continue;
		
		matrix3x4_t bones[128];
		player->SetupBones(bones, 128, 0x7FF00, g_Globals->curtime);

		Vector headPos = bones[8].GetOrigin();

		backtrackData[i].insert(backtrackData[i].begin(), { i, headPos, cmd->tick_count });
	}
}
