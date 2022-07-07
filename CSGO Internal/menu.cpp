#include "menu.h"
#include "EndScene.h"
#include <vector>
#include <string>

void Colors()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImColor(16, 16, 16);
    style.Colors[ImGuiCol_ChildBg] = ImColor(24, 24, 24);
    style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
    style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
    style.Colors[ImGuiCol_Header] = ImColor(95, 30, 200);
    style.Colors[ImGuiCol_HeaderHovered] = ImColor(95, 30, 200);
    style.Colors[ImGuiCol_HeaderActive] = ImColor(95, 30, 200);

    style.Colors[ImGuiCol_Button] = ImColor(35, 35, 35);
    style.Colors[ImGuiCol_ButtonActive] = ImColor(38, 38, 38);
    style.Colors[ImGuiCol_ButtonHovered] = ImColor(40, 40, 40);
    style.Colors[ImGuiCol_FrameBgActive] = ImColor(37, 37, 37);
    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(41, 41, 41);
    style.Colors[ImGuiCol_FrameBg] = ImColor(37, 37, 37);
    style.WindowRounding = 6;
    style.WindowMinSize = ImVec2(515, 320);
    style.FrameRounding = 4;
}

enum PAGE
{
    PAGE_AIM,
    PAGE_ESP,
    PAGE_MOVEMENT
};

struct game_data
{
    std::string name;
    PAGE page;
};

std::vector<game_data> pages = {
    {"Aim", PAGE_AIM},
    {"ESP", PAGE_ESP},
    {"Movement", PAGE_MOVEMENT}
};

bool initialized = false;
void DrawMenu()
{
    if (!initialized)
    {
        initialized = true;
        Colors();
        return;
    }

    static PAGE activePage = PAGE_AIM;

    ImGui::Begin("Hello, world!", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);                          // Create a window called "Hello, world!" and append into it.

    ImGui::PushStyleColor(ImGuiCol_Border, ImColor(0, 0, 0, 255).Value);

    ImGui::Columns(2, 0, true);
    ImGui::SetColumnOffset(1, 165);
    ImGui::BeginChild("##Sidebar");
    {
        ImGui::SetCursorPosX(6);
        ImGui::SetCursorPosY(4);

        float width = ImGui::GetContentRegionAvail().x;
        float textWidth = ImGui::CalcTextSize("Bullyware v1.0").x;
        ImGui::SetCursorPosX(width / 2 - textWidth / 2);
        ImGui::Text("Bullyware v1.0");
        ImGui::SetCursorPosY(26);
        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(24, 0));
        for (unsigned int i = 0; i < pages.size(); i++)
        {
            game_data page = pages.at(i);
            bool selected = page.page == activePage;

            ImGui::SetCursorPosX(6);
            if (ImGui::Selectable(page.name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns))
            {
                activePage = page.page;
            }

        }
        ImGui::PopStyleVar();
    }
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::BeginChild("##Body");
    {

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(0, 0, 0, 0).Value);
        ImGui::SetCursorPosY(6);
        switch (activePage)
        {
        case PAGE_AIM:
        {

            ImGui::Columns(2, 0, false);
            ImGui::BeginChild("##Aim_Left");
            {
                static bool aimbotEnable = false;
                ImGui::Checkbox("Enabled", &aimbotEnable);
            }
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##Aim_Right");
            {

            }
            ImGui::EndChild();

            break;
        }
        }
        ImGui::PopStyleColor();

    }
    ImGui::EndChild();

    ImGui::PopStyleColor();

    ImGui::End();
}