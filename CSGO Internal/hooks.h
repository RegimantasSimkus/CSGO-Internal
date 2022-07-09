#pragma once

#ifndef HOOKS_H
#define HOOKS_H

#include "utils.h"
#include "hooking.h"
#include "PaintTraverse.h"
#include "CreateMove.h"
#include "EndScene.h"
#include "OverrideView.h"

class Hooks
{
public:
	// declare hooks

	Hooks();
	~Hooks();
};

extern Hooks* g_Hooks;

#endif