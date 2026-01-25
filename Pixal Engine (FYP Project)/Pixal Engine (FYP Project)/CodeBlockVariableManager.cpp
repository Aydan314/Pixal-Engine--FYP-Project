#include "CodeBlockVariableManager.h"
CodeBlockVariableManager* CodeBlockVariableManager::m_instance;

CodeBlockVariableManager::CodeBlockVariableManager()
{
}

void CodeBlockVariableManager::Clear()
{
	m_contents.clear();
}

void CodeBlockVariableManager::SetVariable(std::string name, DataContent value)
{
	m_contents[name] = value;
}

DataContent CodeBlockVariableManager::GetVariable(std::string name)
{
	return m_contents[name];
}
