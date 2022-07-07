#pragma once
#include "netvars.h"
#include "macros.h"

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_LOOKSPIN		(1 << 25)

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_ANIMDUCKING			(1<<2)	// Player flag -- Player is in the process of crouching or uncrouching but could be in transition


// m_lifeState values
#define	LIFE_ALIVE				0 // alive
#define	LIFE_DYING				1 // playing death animation or still falling off of a ledge waiting to hit ground
#define	LIFE_DEAD				2 // dead. lying still.
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

class IClientNetworkable
{
public:
	virtual void Func0();
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void Func5();
	virtual void Func6();
	virtual void Func7();
	virtual void Func8();
	virtual bool __thiscall IsDormant(void);
	virtual void Func9();
};

class C_BasePlayer
{
public:

	int x;
	IClientNetworkable* ClientNetworkable;

	/*
	.text:001E5145 8D 4B 08                                                        lea     ecx, [ebx+8] // ebx is player
	.text:001E5148 8B 30                                                           mov     esi, [eax]
	.text:001E514A 8B 01                                                           mov     eax, [ecx]
	.text:001E514C 8B 40 24                                                        mov     eax, [eax+24h] *(*(ebx + 8) + 0x24)()
	.text:001E514F FF D0                                                           call    eax
	.text:001E5151 84 C0                                                           test    al, al
	.text:001E5153 BA 54 12 B7 00                                                  mov     edx, offset aActive ; "active"
	.text:001E5158 B9 5C 12 B7 00                                                  mov     ecx, offset aDormant ; "dormant"
	*/


	//virtual Vector GetABSOrigin(); // 10
	//virtual int GetTeam(); // 88

	bool IsDormant() const
	{
		void* networkable = (void*)((DWORD)this + 0x8);

		typedef bool(__thiscall* tIsDormant)(void*);
		tIsDormant fnIsDormant = (tIsDormant)((*(void***)networkable)[9]);
		return fnIsDormant(networkable);
	}

	Vector& GetABSOrigin() const
	{
		void* pThis = (void*)this;

		typedef Vector&(__thiscall* tGetABSOrigin)(void*);
		tGetABSOrigin fnGetABSOrigin = (tGetABSOrigin)((*(void***)pThis)[10]);
		return fnGetABSOrigin(pThis);
	}

	bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) const
	{
		void* renderable = (void*)((DWORD)this + 0x4);

		typedef bool(__thiscall* tSetupBones)(void* pThis, void* matrixOut, int bones, int mask, float currenttime);
		tSetupBones fnSetupBones = (tSetupBones)((*(void***)renderable)[13]);
		return fnSetupBones(renderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

	NETVAR(GetHealth, int, DT::DT_BasePlayer::m_iHealth);
	NETVAR(GetFOV, int, DT::DT_BasePlayer::m_iFOVStart);
	NETVAR(GetFlags, int, DT::DT_BasePlayer::m_fFlags);
	NETVAR(GetLifeState, int, DT::DT_BasePlayer::m_lifeState);
	NETVAR(GetOrigin, Vector, DT::DT_BaseEntity::m_vecOrigin);
	NETVAR(GetTeam, int, DT::DT_BaseEntity::m_iTeamNum);
	NETVAR(GetViewOffset, Vector, DT::DT_CSPlayer::m_vecViewOffset_0_);
	NETVAR(GetPunchAngles, Vector, DT::DT_Local::m_aimPunchAngle);
	NETVAR(GetShotsFired, int, DT::DT_CSLocalPlayerExclusive::m_iShotsFired);
	//bool IsDormant()
	//{
	//	typedef bool(__thiscall* tIsDormant)(void* pThis);
	//}
	
};