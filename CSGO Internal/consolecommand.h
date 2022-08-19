#pragma once
#include <vector>
#include <string>

class CConsoleCommandManager
{
public:
	class CConsoleCommand
	{
	public:
		const char* szCommand;
		const char* szHelp = nullptr;
		void(*fnCallback)(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments);
	};

	std::vector<CConsoleCommand*> m_Commands;
	unsigned short m_iCommands = 0;

	CConsoleCommandManager();
	~CConsoleCommandManager();

	void AddConsoleCommand(const char* command, void(*fnCallback)(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments), const char* help = nullptr);
	bool RunCommand(const char* command, std::vector<std::string>& arguments);
};


namespace ConsoleCommands
{
	// Populates g_ConsoleCommandManager
	extern void _POPULATE_CONSOLE_COMMANDS();
}

extern CConsoleCommandManager* g_ConsoleCommandManager;