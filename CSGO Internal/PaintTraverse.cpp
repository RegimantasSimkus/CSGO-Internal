#include "PaintTraverse.h"
#include "esp.h"

tPaintTraverse oPaintTraverse = 0;
void __stdcall hkPaintTraverse(void* panel, bool forcerepaint, bool allowforce)
{
	oPaintTraverse(I::IPanel, panel, forcerepaint, allowforce);
}