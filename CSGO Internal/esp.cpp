#include "esp.h"
#include "draw.h"

void ESP::DrawVisuals()
{
	C_BasePlayer* localplayer = I::IEntityList->GetClientEntity(I::IEngineClient->GetLocalPlayer());
	I::IEngineClient->GetScreenSize(scrw, scrh);

	if (!localplayer) return;

	DrawFOVCircle(localplayer);

	DrawLine(20, 20, 500, 500, 1, ImColor_Red);

	for (int i = 1; i < g_Globals->maxClients; i++)
	{
		C_BasePlayer* player = I::IEntityList->GetClientEntity(i);
		if (!player)
			continue;
		
		player_info_t pInfo;
		I::IEngineClient->GetPlayerInfo(i, &pInfo);

		DrawPlayer(player, localplayer, pInfo);
	}
}