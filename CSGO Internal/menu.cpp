#include "menu.h"
#include "EndScene.h"
#include <vector>
#include <string>
#include "settings.h"
#include "consolecommand.h"

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

std::vector<std::string> Split(std::string str, const char* split)
{
    size_t len = strlen(split);
    std::vector<std::string> vec;

    std::string part = "";
    for (int i = 0; i < str.length(); i++)
    {
        bool found = true;
        for (int c = 0; c < len; c++)
        {
            if (!(str[i + c] == split[c]))
            {
                found = false;
                break;

            }
        }
        if (found)
        {
            vec.push_back(part);
            part = "";
            i += len - 1;
        }
        else
        {
            part += str[i];
        }
    }
    if (part.length() != 0)
        vec.push_back(part);

    return vec;
}

void HandleDebugInput(char buff[])
{
    std::string str = std::string(buff);
    buff[0] = '\0'; // empty buffer

    Settings::Misc::Developer::PushLog(std::string("> ").append(str));

    std::vector<std::string> parameters = Split(str, " ");
    
    std::string& command = parameters.at(0);
    
    if (!g_ConsoleCommandManager->RunCommand(command.c_str(), parameters))
        Settings::Misc::Developer::PushLog(std::string("[ERROR] command '").append(command).append("' not found."));

    //if (command == "clear")
    //    Settings::Misc::Developer::Logs.clear();
    //else if (command == "netvar")
    //{
    //    if (parameters.size() <= 1)
    //    {
    //        Settings::Misc::Developer::PushLog("Missing argument #1: Expected a classname. Choose one from the following:");
    //        for (int i = DT::NetvarList.size()-1; i >= 0; i--)
    //        {
    //            Settings::Misc::Developer::PushLog(std::string("    ").append(DT::NetvarList.at(i).szClass));
    //        }
    //        return;
    //    }
    //    if (parameters.size() == 2)
    //    {
    //        std::string& table = parameters.at(1);
    //        char* szTable = toLower(table.c_str());
    //        for (int i = DT::NetvarList.size() - 1; i >= 0; i--)
    //        {
    //            char* szLower = toLower(DT::NetvarList.at(i).szClass);
    //            if (!strcmp(szTable, "*") || !strcmp(szTable, szLower))
    //            {
    //                Settings::Misc::Developer::PushLog(std::string(DT::NetvarList.at(i).szClass).append(":"));
    //                for (int n = 0; n < DT::NetvarList.at(i).netvars.size(); n++)
    //                {
    //                    Settings::Misc::Developer::PushLog(std::string("    ").append(DT::NetvarList.at(i).netvars.at(n).szNetVar).append("  ->  ").append(std::to_string((unsigned int)DT::NetvarList.at(i).netvars.at(n).offset)));
    //                }
    //            }
    //            delete[] szLower;
    //        }
    //        delete[] szTable;
    //    }

    //}
}

bool initialized = false;
void DrawMenu()
{
    if (!initialized)
    {
        initialized = true;
        Colors();
        return;
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Developer"))
        {
            ImGui::MenuItem("Debug Console", NULL, &Settings::Misc::Developer::DebugConsole);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (Settings::Misc::Developer::DebugConsole)
    {

        ImGui::Begin("Debug Console", &Settings::Misc::Developer::DebugConsole, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

        ImVec2 size = ImGui::GetContentRegionAvail();
        size.y -= 25;
        ImGui::BeginChild("##DEVELOPER_CONSOLE_BODY", size, true);
        {
            for (int i = 0; i < Settings::Misc::Developer::Logs.size(); i++)
            {
                Settings::Misc::Developer::log_t& log = Settings::Misc::Developer::Logs.at(i);
                ImGui::Text("%s", log.log.c_str());
            }
        }
        ImGui::EndChild();

        ImGui::PushItemWidth(size.x);
        if (ImGui::InputText("##DEVELOPER_CONSOLE_INPUT", Settings::Misc::Developer::InputBuff, 0xFF, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            HandleDebugInput(Settings::Misc::Developer::InputBuff);
        }
        ImGui::End();
    }

    static PAGE activePage = PAGE_AIM;
    ImGui::Begin("##Frame", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

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
        case PAGE_MOVEMENT:
        {
            ImGui::Checkbox("BunnyHop", &Settings::Movement::BunnyHop);
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