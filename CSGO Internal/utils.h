#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <sstream>

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

	static std::string HexByte(unsigned char byte)
	{
		static const char* bytes = "0123456789ABCDEF";

		int big = byte / 16;
		int smol = byte - (big * 16);

		std::stringstream str;
		str << bytes[big];
		str << bytes[smol];
		return str.str();
	}

	static std::string IntToHex(unsigned int num)
	{
		std::string hex = "";
		
		while (num > 0)
		{
			hex = HexByte(num & 0xFF) + hex;
			num = num >> 8;
		}
		hex = "0x" + hex;

		return hex;
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