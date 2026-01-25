#pragma once 
#include "Commons.h"
#include <map>

class CodeBlockVariableManager
{
private:
	CodeBlockVariableManager();

	static CodeBlockVariableManager* m_instance;
	std::map<std::string, DataContent> m_contents;

public:
	static inline CodeBlockVariableManager* Instance() 
	{
		if (!m_instance)
		{
			m_instance = new CodeBlockVariableManager();
		}
		return m_instance;
	}
	void Clear();

	void SetVariable(std::string name, DataContent value);
	DataContent GetVariable(std::string name);
};

