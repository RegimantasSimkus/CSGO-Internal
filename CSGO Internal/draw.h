#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"

// use imgui_widgets.cpp as reference


namespace ImGui::Draw
{
	extern ImColor ImColor_White;
	extern ImColor ImColor_Black;
	extern ImColor ImColor_Red;
	extern ImColor ImColor_Green;

	extern void DrawLine(float x1, float y1, float x2, float y2, float thickness , ImColor& col);
	extern void DrawFilledRect(float x, float y, float w, float h, ImColor& col);
	extern void DrawCircle(float x, float y, float radius, ImColor& col);

	// 'DrawText' conflicts with the windows api macro
	extern void DrawText_(const char* text, float x, float y, ImColor& col, bool centerX, bool centerY);
	extern void DrawOutlinedText(const char* text, float x, float y, float thickness, ImColor& col, bool centerX, bool centerY);
}