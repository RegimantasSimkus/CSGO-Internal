#pragma once
#include "interfaces.h"
#include "C_BasePlayer.h"
#include "CUserCmd.h"

typedef bool(__stdcall* tCreateMove)(float flSampleTime, CUserCmd* cmd);
extern tCreateMove oCreateMove;
bool __stdcall hkCreateMove(float flSampleTime, CUserCmd* cmd);