#include "hooking.h"

Hook::Hook(PVOID target, PVOID callback, PVOID* ret)
{
	m_pTarget = target;
	MH_STATUS status = MH_CreateHook(target, callback, ret);
	if (status == MH_OK)
	{
		Enable();
	}
}

Hook::Hook(DWORD target, PVOID callback, PVOID* ret)
{
	Hook((PVOID)target, callback, ret);
}

MH_STATUS Hook::Enable()
{
	return MH_EnableHook(m_pTarget);
}

MH_STATUS Hook::Disable()
{
	return MH_DisableHook(m_pTarget);
}

MH_STATUS Hook::Unhook()
{
	return MH_RemoveHook(m_pTarget);
}