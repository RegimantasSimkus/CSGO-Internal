#pragma once
#include <string>
#include <vector>
#include <ctime>

class CViewSetup;

namespace Settings
{
	namespace Aim
	{
		extern bool Enabled;
		extern float FOV;
		extern float FOVLength; // The length of the hypotenuse/size of radius
		extern bool RecoilControl;
		extern bool Backtrack;
	}

	namespace ESP
	{
		extern bool Enabled;
	}

	namespace Camera
	{
		extern bool Enabled;
		extern float FOV;
		extern CViewSetup* ViewSetup;
	}

	namespace Movement
	{
		extern bool BunnyHop;
	}

	namespace Misc
	{
		namespace Developer
		{
			struct log_t
			{
				std::string log;
				time_t itime;
				const char* szTime;
			};
			extern void PushLog(std::string log);
			extern std::vector<log_t> Logs;
			extern bool DebugConsole;
			extern char InputBuff[0xFF];
		}
	}
}