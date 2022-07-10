#include "draw.h"

namespace ImGui::Draw
{

	// use imgui_widgets.cpp as reference
	ImColor ImColor_White = ImColor(255, 255, 255);
	ImColor ImColor_Black = ImColor(0, 0, 0);
	ImColor ImColor_Green = ImColor(0, 255, 0);
	ImColor ImColor_Red = ImColor(255, 0, 0);

	void DrawLine(float x1, float y1, float x2, float y2, float thickness, ImColor& col)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), col, thickness);
	}

	void DrawFilledRect(float x, float y, float w, float h, ImColor& col)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), col, 0.f);
	}

	void DrawCircle(float x, float y, float radius, ImColor& col)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddCircle(ImVec2(x, y), radius, col);
	}

	void DrawText_(const char* text, float x, float y, ImColor& col, bool centerX, bool centerY)
	{
		ImVec2 pos = ImVec2(x, y);
		ImVec2 textSize = ImGui::CalcTextSize(text);

		if (centerX)
			pos.x -= (textSize.x * 0.5f);

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddText(pos, col, text);
	}

	void DrawOutlinedText(const char* text, float x, float y, float thickness, ImColor& col, bool centerX, bool centerY)
	{
		for (float _x = -thickness; _x <= thickness; _x++)
		{
			for (float _y = -thickness; _y <= thickness; _y++)
			{
				if (_x == 0.f && _y == 0.f) continue;

				DrawText_(text, x + _x, y + _y, ImColor_Black, centerX, centerY);
			}
		}
		DrawText_(text, x, y, col, centerX, centerY);
	}
}