#include "esp.h"
#include "aim.h"

namespace ESP
{
	int scrw = 0;
	int scrh = 0;
}

namespace Aim
{
	C_BasePlayer* Target = nullptr;
	Vector RCSOffset;
}