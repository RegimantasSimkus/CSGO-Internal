#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <initializer_list>

namespace Utils
{
	static DWORD FindSignature(const char* szModule, const char* szPattern, const char* szMask)
	{
		MODULEINFO modInfo;

		HMODULE hModule = GetModuleHandleA(szModule);
		if (!hModule)
			return 0;
		GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

		DWORD masklen = strlen(szMask);

		DWORD dwBase = (DWORD)modInfo.lpBaseOfDll;
		DWORD dwSize = (DWORD)modInfo.SizeOfImage;

		dwSize -= masklen;

		bool found = true;
		char cur = 0;
		for (DWORD i = 0; i < dwSize; i++)
		{
			cur = *(char*)(dwBase + i);
			if (cur == szPattern[0])
			{
				found = true;
				for (DWORD c = 0; c < masklen; c++)
				{
					cur = *(char*)(dwBase + i + c);
					if (szMask[c] != '?' && cur != szPattern[c])
					{
						found = false;
						break;
					}
				}
				if (found)
					return dwBase + i;
			}
		}
		return 0;
	}

	template <typename T = void*>
	static T GetVFunc(void* pThis, int index)
	{
		void** vTable = *(void***)pThis;
		void* func = vTable[index];
		return (T)func;
	}

	template <typename ret = void*, typename... Args>
	static ret CallVFunc(void* pThis, int index, Args... args)
	{
		typedef ret(__thiscall* tFunc)(void*, decltype(args)...);
		tFunc fnFunc = GetVFunc<tFunc>(pThis, index);

		return fnFunc(pThis, args...);
	}
}

#endif