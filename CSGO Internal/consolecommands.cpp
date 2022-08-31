#include "consolecommand.h"
#include "settings.h"
#include "netvars.h"
#include "csgo.h"
#include "utils.h"

char* toLower(const char* str)
{
    size_t len = strlen(str);
    char* buff = new char[len + 1];
    buff[len] = '\0';

    for (size_t i = 0; i < len; i++)
    {
        buff[i] = std::tolower(str[i]);
    }

    return buff;
}

// we look for the needle within the haystack
bool stringContains(const char* haystack, const char* needle)
{
    size_t len = strlen(haystack);
    size_t needleLen = strlen(needle);

    if (needleLen > len)
        return false;

    bool bFound = false;
    for (size_t i = 0; i < len - (needleLen - 1); i++)
    {
        bFound = true;
        for (size_t j = 0; j < needleLen; j++)
        {
            if (haystack[i + j] != needle[j])
            {
                bFound = false;
                break;
            }
        }
        if (bFound)
            return true;
    }
    return false;
}

namespace ConsoleCommands
{
    void Help(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments)
    {
        for (int i = 0; i < commandmanager->m_Commands.size(); i++)
        {
            CConsoleCommandManager::CConsoleCommand*& cmd = commandmanager->m_Commands.at(i);
            Settings::Misc::Developer::PushLog(std::string(cmd->szCommand).append(":"));
            if (cmd->szHelp)
                Settings::Misc::Developer::PushLog(std::string("    - ").append(cmd->szHelp));
        }
    }

    void Clear(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments)
    {
        Settings::Misc::Developer::Logs.clear();
    }

    void Netvar(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments)
    {
        if (arguments.size() <= 1)
        {
            Settings::Misc::Developer::PushLog("Missing argument #1: Expected a classname. Choose one from the following:");
            for (int i = DT::NetvarList.size() - 1; i >= 0; i--)
            {
                Settings::Misc::Developer::PushLog(std::string("    ").append(DT::NetvarList.at(i).szClass));
            }
            return;
        }
        if (arguments.size() == 2)
        {
            std::string& table = arguments.at(1);
            char* szTable = toLower(table.c_str());
            for (int i = DT::NetvarList.size() - 1; i >= 0; i--)
            {
                char* szLower = toLower(DT::NetvarList.at(i).szClass);
                if (!strcmp(szTable, "*") || !strcmp(szTable, szLower))
                {
                    Settings::Misc::Developer::PushLog(std::string(DT::NetvarList.at(i).szClass).append(":"));
                    for (int n = 0; n < DT::NetvarList.at(i).netvars.size(); n++)
                    {
                        Settings::Misc::Developer::PushLog(std::string("    ").append(DT::NetvarList.at(i).netvars.at(n).szNetVar).append("  ->  ").append(Utils::IntToHex(DT::NetvarList.at(i).netvars.at(n).offset)));
                    }
                }
                delete[] szLower;
            }
            delete[] szTable;
        }
    }

    void GetPlayer(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments)
    {
        if (arguments.size() < 2)
        {
            for (int i = 1; i < g_Globals->maxClients; i++)
            {
                C_BasePlayer* ply = I::IEntityList->GetClientEntity(i);
                if (ply)
                {
                    player_info_t info;
                    I::IEngineClient->GetPlayerInfo(i, &info);
                    Settings::Misc::Developer::PushLog(std::string(std::to_string(i)).append(") ").append(info.name).append(" (").append(Utils::IntToHex((uintptr_t)ply)).append(")"));
                }
            }
        }
        else
        {
            std::string& name = arguments.at(1);

            char* szName = toLower(name.c_str());
            for (int i = 1; i < g_Globals->maxClients; i++)
            {
                C_BasePlayer* ply = I::IEntityList->GetClientEntity(i);
                if (ply)
                {
                    player_info_t info;
                    I::IEngineClient->GetPlayerInfo(i, &info);
                    
                    char* szInfoName = toLower(info.name);
                    std::cout << "stringContains: (" << szInfoName << ") (" << szName << ") " << stringContains(szInfoName, szName) << ")\n";
                    if (stringContains(szInfoName, szName))
                    {
                        Settings::Misc::Developer::PushLog(std::string(std::to_string(i)).append(") ").append(info.name).append(" (").append(Utils::IntToHex((uintptr_t)ply)).append(")"));
                    }

                    delete[] szInfoName;
                }
            }

            delete[] szName;
        }
    }

    void _POPULATE_CONSOLE_COMMANDS()
    {
        g_ConsoleCommandManager->AddConsoleCommand("help", Help, "Prints out a list of every available console command.");
        g_ConsoleCommandManager->AddConsoleCommand("clear", Clear, "Clears the console.");
        g_ConsoleCommandManager->AddConsoleCommand("netvar", Netvar, "Shows a list of every netvar & offset. Use '*' as the first argument to display every netvar.");
        g_ConsoleCommandManager->AddConsoleCommand("getplayer", GetPlayer, "Get details about players in your game.");
    }
}

using namespace ConsoleCommands;

