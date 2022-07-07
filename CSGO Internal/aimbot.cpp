#include "aim.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // getasynckeystate
Vector& Aim::Aimbot(CUserCmd* cmd, C_BasePlayer* localplayer)
{
	if (!(GetAsyncKeyState(VK_LMENU)))
		return cmd->viewangles;


	int localTeam = localplayer->GetTeam();

	int scrw, scrh;
	I::IEngineClient->GetScreenSize(scrw, scrh);

	Target = nullptr;
	float lowestHypot = 0.f;
	Vector targetHeadPos;
	Vector targetHeadScreenPos;
	for (int i = 0; i < g_Globals->maxClients; i++)
	{
		C_BasePlayer* player = I::IEntityList->GetClientEntity(i);
		if (!player || player->GetTeam() == localTeam || player->IsDormant() || player->GetHealth() <= 0)
			continue;

		matrix3x4_t bones[128];
		//player->SetupBones(bones, 128, 0x7FF00, g_Globals->curtime);
		if (!player->SetupBones(bones, 128, 0x7FF00, g_Globals->curtime))
			continue;

		Vector headPos = bones[8].GetOrigin();

		Vector screenPos;
		if (I::IDebugOverlay->ScreenPosition(headPos, screenPos))
			continue;

		float diffX = screenPos.x - ((float)scrw / 2);
		float diffY = screenPos.y - ((float)scrh / 2);

		float hypotSqr = (diffX * diffX) + (diffY * diffY);
		if (!Target || hypotSqr < lowestHypot)
		{
			lowestHypot = hypotSqr;
			Target = player;
			targetHeadPos = headPos;
			targetHeadScreenPos = screenPos;
		}
	}

	if (!Target)
		return cmd->viewangles;

	// where we shoot from :D
	Vector localEyePos = localplayer->GetOrigin().Add(localplayer->GetViewOffset());
	
	Vector delta = { targetHeadPos.x - localEyePos.x, targetHeadPos.y - localEyePos.y, targetHeadPos.z - localEyePos.z };

	float hypot = sqrt((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
	float pitch = -asin(delta.z / hypot) * (180 / PI);
	float yaw = atan2(delta.y, delta.x) * (180 / PI);

	// using the delta structure to prevent having to create a new vector
	delta.x = pitch;
	delta.y = yaw;
	delta.z = 0;

	return delta;
}