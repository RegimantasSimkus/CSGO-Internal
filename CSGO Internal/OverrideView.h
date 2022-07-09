#pragma once
#include "CSetupView.h"

typedef int(__thiscall* tOverrideView)(void* pThis, CViewSetup* view);

extern tOverrideView oOverrideView;
extern int __fastcall hkOverrideView(void* pThis, void* _, CViewSetup* view);