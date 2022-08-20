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

    for (int i = 0; i < len; i++)
    {
        buff[i] = std::tolower(str[i]);
    }

    return buff;
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
                    I::IEngineClient->GetPlayerInfo(i, &info);                                                         // should create myself a function to convert a number to hex, would come in very handy
                    Settings::Misc::Developer::PushLog(std::string(std::to_string(i)).append(") ").append(info.name).append(" (").append(Utils::IntToHex((uintptr_t)ply)).append(")")); //.append(" [").append(std::to_string((long double)((uintptr_t)ply))).append("]"));
                }
            }
        }
    }

    void _POPULATE_CONSOLE_COMMANDS()
    {
        g_ConsoleCommandManager->AddConsoleCommand("help", Help, "Prints out a list of every available console command.");
        g_ConsoleCommandManager->AddConsoleCommand("clear", Clear, "Clears the console.");
        g_ConsoleCommandManager->AddConsoleCommand("netvar", Netvar, "Shows a list of every netvar & offset. Use '*' as the first argument to display every netvar.");
        g_ConsoleCommandManager->AddConsoleCommand("getplayer", GetPlayer);
    }
}

using namespace ConsoleCommands;

