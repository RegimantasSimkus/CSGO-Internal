#include "PaintTraverse.h"
#include "esp.h"

tPaintTraverse oPaintTraverse = 0;
void __stdcall hkPaintTraverse(void* panel, bool forcerepaint, bool allowforce)
{
	oPaintTraverse(I::IPanel, panel, forcerepaint, allowforce);
	if (!(panel == I::IEngineVGUI->GetPanel(PANEL_TOOLS) && I::IEngineTool->m_bIsInGame))
		return;

	I::IEngineClient->GetScreenSize(ESP::scrw, ESP::scrh);

	C_BasePlayer* localplayer = I::IEntityList->GetClientEntity(I::IEngineClient->GetLocalPlayer());
	if (!localplayer) return;

	player_info_t playerinfo;
	for (int i = 0; i < g_Globals->maxClients; i++)
	{
		C_BasePlayer* player = I::IEntityList->GetClientEntity(i);
		if (!player)
			continue;

		if (player == localplayer)
			continue;

		if (player->IsDormant())
			continue;

		if (player->GetHealth() <= 0)
			continue;

		if (!(I::IEngineClient->GetPlayerInfo(i, &playerinfo)))
			continue;

		//ESP::DrawPlayer(player, localplayer, playerinfo);
		ESP::DrawFOVHelp(player, localplayer);
	}
	
	ESP::DrawFOVCircle(localplayer);
}