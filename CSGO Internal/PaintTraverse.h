#pragma once

class IPanel;

#include "csgo.h"

typedef void(__thiscall* tPaintTraverse)(IPanel* pThis, void* panel, bool forcerepaint, bool allowforce);
extern tPaintTraverse oPaintTraverse;
void __stdcall hkPaintTraverse(void* panel, bool forcerepaint, bool allowforce);