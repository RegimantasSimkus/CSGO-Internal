#include "settings.h"

namespace Settings
{
	namespace Aim
	{
		bool Enabled = false;
		float FOV = 0.f;
		float FOVLength = 0.f; // The length of the hypotenuse/size of radius
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