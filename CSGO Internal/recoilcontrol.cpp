#include "aim.h"

void Aim::RecoilControl(CUserCmd* cmd, C_BasePlayer* localplayer, Vector& vec)
{
	static Vector prevPunch;

	int shotsFired = localplayer->GetShotsFired();
	if (shotsFired <= 1)
	{
		if (!prevPunch.IsZero())
			prevPunch.Zero();
		return;
	}

	Vector punch = localplayer->GetPunchAngles();

	punch.x *= 2;
	punch.y *= 2;

	vec.x += prevPunch.x - punch.x;
	vec.y += prevPunch.y - punch.y;

	prevPunch = punch;
} 