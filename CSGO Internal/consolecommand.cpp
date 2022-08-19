#include "consolecommand.h"

CConsoleCommandManager::CConsoleCommandManager()
{
}

CConsoleCommandManager::~CConsoleCommandManager()
{
	//for (int i = 0; i < m_Commands.size(); i++)
	//{
	//	delete m_Commands.at(i);
	//}


	// looks like clear deallocates all the memory it contains
	m_Commands.clear();
}

void CConsoleCommandManager::AddConsoleCommand(const char* command, void(*fnCallback)(CConsoleCommandManager* commandmanager, std::vector<std::string>& arguments), const char* help)
{
	CConsoleCommand* cmd = new CConsoleCommand();
	cmd->szCommand = command;
	cmd->fnCallback = fnCallback;
	cmd->szHelp = help;

	m_Commands.push_back(cmd);
}

bool CConsoleCommandManager::RunCommand(const char* command, std::vector<std::string>& arguments)
{
	for (int i = 0; i < m_Commands.size(); i++)
	{
		if (!strcmp(m_Commands.at(i)->szCommand, command))
		{
			m_Commands.at(i)->fnCallback(this, arguments);
			return true;
		}
	}
	return false;
}

CConsoleCommandManager* g_ConsoleCommandManager = new CConsoleCommandManager();
