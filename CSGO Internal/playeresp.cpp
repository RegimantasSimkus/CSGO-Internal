#include "esp.h"
#include <math.h>

// To rotate around a constant axis
// the originalAngle will always be the same here
void Rotate(Vector& pivot, Vector& out, float angle)
{

	float distance = pivot.Distance2D(out);

	float rad = RAD(angle);

	float c = cos(rad);
	float s = sin(rad);

	out.x = pivot.x + (c * distance);
	out.y = pivot.y + (s * distance);
}

void ESP::DrawPlayer(C_BasePlayer* player, C_BasePlayer* localplayer, player_info_t playerinfo)
{
	if (player == localplayer)
		return;

	if (player->GetHealth() <= 0)
		return;

	if (player->IsDormant())
		return;

	matrix3x4_t bones[128];
	if (!player->SetupBones(bones, 128, 0x7FF00, g_Globals->curtime))
		return;

	bool bSameTeam = player->GetTeam() == localplayer->GetTeam();
	ImColor col = bSameTeam ? ImColor_Green : ImColor_Red;

	Vector pos = player->GetABSOrigin();

	Vector center = pos + player->GetCollisionProperties()->Center();
	Vector mins = pos + player->GetCollisionProperties()->mins;
	Vector maxs = pos + player->GetCollisionProperties()->maxs;

	Vector tl = Vector(center.x, mins.y, maxs.z);
	Vector tr = Vector(center.x, maxs.y, maxs.z);

	Vector br = Vector(center.x, maxs.y, mins.z);
	Vector bl = Vector(center.x, mins.y, mins.z);

	// screen positions
	Vector topRight, topLeft, bottomLeft, bottomRight;


	Vector localPos = localplayer->GetOrigin() + localplayer->GetViewOffset();
	Vector angles = (center - localPos).Angle();

	// +/- 90 because the corners are relative
	Rotate(pos, tr, angles.y - 90.f);
	Rotate(pos, br, angles.y - 90.f);
	Rotate(pos, tl, angles.y + 90.f);
	Rotate(pos, bl, angles.y + 90.f);

	I::IDebugOverlay->ScreenPosition(tr, topRight);
	I::IDebugOverlay->ScreenPosition(tl, topLeft);
	I::IDebugOverlay->ScreenPosition(br, bottomRight);
	I::IDebugOverlay->ScreenPosition(bl, bottomLeft);

	// top
	DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, 1, col);

	// left
	DrawLine(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y, 1, col);

	// bottom
	DrawLine(bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, 1, col);

	// right
	DrawLine(bottomRight.x, bottomRight.y, topRight.x, topRight.y, 1, col);

	float width = bottomRight.x - bottomLeft.x;
	float height = bottomLeft.y - topLeft.y;

	float& x = bottomLeft.x;

	float& top = topRight.y;

	float& bottom = bottomLeft.y;
	bottom += 1.f; // margin to separate lines & text

	float& right = bottomRight.x;
	right += 1.f;

	float cx = bottomLeft.x + (bottomRight.x - bottomLeft.x) / 2.f;
	float cy = bottomLeft.y + (bottomRight.y - bottomLeft.y) / 2.f;

	DrawOutlinedText(playerinfo.name, cx, cy, 1, ImColor_White, true, false);

	{
		float bx = bottomRight.x + 5.f;
		float by = bottomRight.y;
		
		float tx = topRight.x + 5.f;

		float healthRatio = player->GetHealth() / 100.f;

		// the ratio used to determine the end of the bar
		float ratio = 1.f - healthRatio;
		
		float barX = topRight.x + 5.f + (ratio * (bx - (topRight.x + 5.f)));
		float barY = topRight.y +		(ratio * (by - topRight.y));

		DrawLine(tx, topRight.y, bx, by, 4.f, ImColor_Black);

		ImColor healthCol = ImColor(
			(UINT)((ratio) * 255.f),
			(UINT)(healthRatio * 255.f),
			0
		);

		DrawLine(
			barX,
			barY,
			bx,
			by,
			2.f,
			healthCol
		);
	}
}