#pragma once

#ifndef HOOKING_H
#define HOOKING_H

#include "MinHook/MinHook.h"
#pragma comment(lib, "minhook.x32.lib")
#include <vector>

class Hook
{
private:
	PVOID m_pTarget;
public:
	Hook(PVOID target, PVOID callback, PVOID* ret);
	Hook(DWORD target, PVOID callback, PVOID* ret);

	MH_STATUS Enable();
	MH_STATUS Disable();
	MH_STATUS Unhook();
};

class VMTHookManager
{
protected:
	PVOID* vTable;
	PVOID* oFuncs[256];
public:
	VMTHookManager(PVOID* _vTable)
	{
		vTable = _vTable;
	}
	~VMTHookManager()
	{
		//for (int i = 0; i < oFuncs.max_size(); i++)
		//{
		//	PVOID original = oFuncs.at(i);
		//	if (original)
		//	{
		//		Unhook(i);
		//	}
		//}
	}

	template <typename tCallback = void*>
	tCallback Hook(PVOID callback, int index)
	{
		PVOID func = vTable[index];
		
		//tCallback original = nullptr;
		//MH_CreateHook(func, reinterpret_cast<PVOID>(&callback), reinterpret_cast<PVOID*>(&original));

		tCallback original;

		MH_CreateHook(func, callback, reinterpret_cast<PVOID*>(&original));

		//DWORD oldProtection;
		//VirtualProtect(&vTable[index], sizeof(PVOID), PAGE_EXECUTE_READWRITE, &oldProtection);
		//*oFuncs[index] = func;
		//vTable[index] = callback;
		//VirtualProtect(&vTable[index], sizeof(PVOID), oldProtection, &oldProtection);
		return original;
	}

	void Unhook(int index)
	{
		PVOID original = oFuncs[index];

		MH_DisableHook((PVOID)vTable[index]);
		MH_RemoveHook((PVOID)vTable[index]);
	}

	template <typename tCallback = void*>
	tCallback GetVFunc(int index)
	{
		PVOID func = vTable[index];

		return (tCallback)func;
	}
};

#endif