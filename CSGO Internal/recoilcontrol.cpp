#include "aim.h"

void Aim::RecoilControl(CUserCmd* cmd, C_BasePlayer* localplayer, Vector* angles, bool isAimbot)
{
	static Vector prevPunch;

	int shotsFired = localplayer->GetShotsFired();
	if (shotsFired <= 1)
	{
		if (!prevPunch.IsZero())
			prevPunch.Zero();

		if (!RCSOffset.IsZero())
			RCSOffset.Zero();

		return;
	}

	Vector punch = localplayer->GetPunchAngles();

	punch.x *= 2;
	punch.y *= 2;

	float offsetX = prevPunch.x - punch.x;
	float offsetY = prevPunch.y - punch.y;

	RCSOffset.x += offsetX;
	RCSOffset.y += offsetY;

	angles->x += isAimbot ? RCSOffset.x : offsetX;
	angles->y += isAimbot ? RCSOffset.y : offsetY;

	prevPunch = punch;
}