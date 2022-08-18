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
	}
}