#include "aim.h"
#include "settings.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // getasynckeystate

// return recoil control view
#define RETRCV() { RecoilControl(cmd, localplayer, cmd->viewangles); return cmd->viewangles; }

Vector& Aim::Aimbot(CUserCmd* cmd, C_BasePlayer* localplayer)
{
	if (!Settings::Aim::Enabled || !(GetAsyncKeyState(VK_LMENU)))
		RETRCV();

	Target = nullptr;

	int scrw, scrh;
	I::IEngineClient->GetScreenSize(scrw, scrh);

	float cx = scrw / 2.f;
	float cy = scrh / 2.f;

	int localTeam = localplayer->GetTeam();
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



		float diffX = screenPos.x - cx;
		float diffY = screenPos.y - cy;

		float hypotenuse = ((diffX * diffX) + (diffY * diffY));

		if (
			(Settings::Aim::FOV == 0.f || hypotenuse < Settings::Aim::FOVLength) &&
			(!Target || hypotenuse < lowestHypot)
			)
		{
			lowestHypot = hypotenuse;
			Target = player;
			targetHeadPos = headPos;
			targetHeadScreenPos = screenPos;
		}
	}

	if (!Target)
		RETRCV();

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

	RecoilControl(cmd, localplayer, delta, true);

	return delta;
}