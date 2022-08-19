#include "settings.h"

namespace Settings
{
	namespace Aim
	{
		bool Enabled = false;
		float FOV = 0.f;
		float FOVLength = 0.f; // The length of the hypotenuse/size of radius
		bool RecoilControl = false;
		bool Backtrack = false;
	}
	namespace ESP
	{
		bool Enabled = false;
	}
	namespace Camera
	{
		float FOV = 75.f;
		bool Enabled = false;
		CViewSetup* ViewSetup = nullptr;
	}

	namespace Movement
	{
		bool BunnyHop = false;
	}

	namespace Misc
	{
		namespace Developer
		{

			std::vector<log_t> Logs;
			void PushLog(std::string log)
			{
				time_t t = time(NULL);
				

				Logs.push_back({log, time(NULL), std::to_string(t).c_str()});
			}
			bool DebugConsole = false;
			char InputBuff[0xFF];
		}
	}
}