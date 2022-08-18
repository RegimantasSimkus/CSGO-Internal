#include "menu.h"
#include "EndScene.h"
#include <vector>
#include <string>
#include "settings.h"

// For GetFOVRadius
#include "esp.h"

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
    style.Colors[ImGuiCol_SliderGrab] = ImColor(95, 30, 200);
    style.Colors[ImGuiCol_SliderGrabActive] = ImColor(95, 30, 200);

    style.FramePadding = ImVec2(2, 4.f);

    style.GrabRounding = 2;
    style.WindowRounding = 6;
    style.WindowMinSize = ImVec2(515, 320);
    style.FrameRounding = 4;
}

enum PAGE
{
    PAGE_AIM,
    PAGE_ESP,
    PAGE_MOVEMENT,
    PAGE_CAMERA
};

struct game_data
{
    std::string name;
    PAGE page;
};

std::vector<game_data> pages = {
    {"Aim", PAGE_AIM},
    {"ESP", PAGE_ESP},
    {"Movement", PAGE_MOVEMENT},
    {"Camera", PAGE_CAMERA}
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
    ImGui::Begin("##Frame", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);                          // Create a window called "Hello, world!" and append into it.

    ImGui::PushStyleColor(ImGuiCol_Border, ImColor(0, 0, 0, 255).Value);

    ImGui::Columns(2, 0, false);
    ImGui::SetColumnWidth(0, 165);
    ImGui::BeginChild("##Sidebar");
    {
        ImGui::SetCursorPosX(6);
        ImGui::SetCursorPosY(4);

        int width = ImGui::GetContentRegionAvail().x;
        int textWidth = ImGui::CalcTextSize("Bullyware v1.0").x;
        ImGui::SetCursorPosX(width / 2 - textWidth / 2);
        ImGui::Text("Bullyware v1.0");
        ImGui::SetCursorPosY(26);
        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(6, 0));
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

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));
    ImGui::BeginChild("##Body", ImVec2(), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
    {
        ImGui::PopStyleVar();

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(0, 0, 0, 0).Value);
        ImGui::SetCursorPosY(6);
        switch (activePage)
        {
        case PAGE_AIM:
        {
            ImGui::Checkbox("Enable", &Settings::Aim::Enabled);
            ImGui::LabelText("##FOVLabel", "FOV");
            if (ImGui::SliderFloat("##FOV", &Settings::Aim::FOV, 0, 180))
            {
                float rad = ESP::GetFOVRadius(Settings::Aim::FOV);
                Settings::Aim::FOVLength = rad * rad;
            }

            ImGui::Checkbox("Recoil Control", &Settings::Aim::RecoilControl);
            ImGui::Checkbox("Backtrack", &Settings::Aim::Backtrack);

            break;
        }
        case PAGE_ESP:
        {
            ImGui::Checkbox("Enable", &Settings::ESP::Enabled);
            break;
        }
        case PAGE_CAMERA:
        {
            ImGui::Checkbox("Enable", &Settings::Camera::Enabled);
            ImGui::LabelText("##FOVLabel", "FOV");
            ImGui::SliderFloat("##FOV", &Settings::Camera::FOV, 1.f, 170.f);
            break;
        }
        }
        ImGui::PopStyleColor();
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::End();
}