#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define NETVAR(funcName, retType, dtvar) retType funcName() const {return *(retType*)((DWORD)this + dtvar);};

