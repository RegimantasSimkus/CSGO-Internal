#include "hooks.h"

Hooks::Hooks()
{
	MH_Initialize();
}

Hooks::~Hooks()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

Hooks* g_Hooks = 0;