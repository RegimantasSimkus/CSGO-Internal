#pragma once

#include <Windows.h>
#include <iostream>
#include "IPanel.h"
#include "IEngineVGui.h"
#include "ISurface.h"
#include "IEngineTool.h"
#include "IClientEntityList.h"
#include "IVEngineClient.h"
#include "IDebugOverlay.h"
#include "ICHLClient.h"
#include "IEngineTrace.h"

#ifdef _DEBUG
#include <vector>
#endif

using IPanel = IPanel;

namespace I
{

#ifdef _DEBUG
	struct interface_t
	{
		const char* szName;
		void* pInterface;
	};
	static std::vector<interface_t> vecInterfaces = {};
#endif

	template <typename T = void>
	static T* CreateInterface(const char* szModule, const char* szInterface)
	{
		typedef void* (*tCreateInterface)(const char* szName, int);
		tCreateInterface fnCreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandleA(szModule), "CreateInterface");
		T* ret = (T*)fnCreateInterface(szInterface, 0);

		vecInterfaces.push_back({ szInterface, ret });

		return ret;
	}

	static void PrintList()
	{
#ifdef _DEBUG
		for (int i = 0; i < vecInterfaces.size(); i++)
		{
			interface_t Interface = vecInterfaces.at(i);
			std::cout << Interface.szName << "\t->\t" << Interface.pInterface << "\n";
		}
		std::cout << std::endl;
#endif
	}

	static ::ICHLClient* CHLClient = CreateInterface<::ICHLClient>("client.dll", "VClient018");
	static void* ClientModeShared = **(void***)((*(DWORD**)CHLClient)[10] + 5);
	static ::IVEngineClient* IEngineClient = CreateInterface<IVEngineClient>("engine.dll", "VEngineClient014");
	static ::CEngineTool* IEngineTool = CreateInterface<::CEngineTool>("engine.dll", "VENGINETOOL003");
	static ::IClientEntityList* IEntityList = CreateInterface<::IClientEntityList>("client.dll", "VClientEntityList003");
	static ::ISurface* ISurface = CreateInterface<::ISurface>("vguimatsurface.dll", "VGUI_Surface031");
	static ::IPanel* IPanel = CreateInterface<::IPanel>("vgui2.dll", "VGUI_Panel009");
	static ::IEngineVGui* IEngineVGUI = CreateInterface<::IEngineVGui>("engine.dll", "VEngineVGui001");
	static ::CIVDebugOverlay* IDebugOverlay = CreateInterface<::CIVDebugOverlay>("engine.dll", "VDebugOverlay004");
	static ::IEngineTrace* EngineTrace = CreateInterface<::IEngineTrace>("engine.dll", "EngineTraceClient004");
}
