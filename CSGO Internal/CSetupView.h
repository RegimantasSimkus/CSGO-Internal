#pragma once
#include "Vector.h"

class CViewSetup
{
public:
	char __padding[0xB0];
	float fov;
	char __padding0[0x4];
	Vector origin;
	Vector angles;
};