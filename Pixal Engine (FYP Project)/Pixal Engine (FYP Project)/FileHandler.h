#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Commons.h"

class FileHandler
{
private:
	FileHandler();
	static FileHandler* m_instance;

public:
	~FileHandler();
	static FileHandler* Instance();

	std::string ReadFile(std::string fileName);
	std::vector<std::string> SplitData(std::string data, std::string seperator);

	void WriteFile(std::string fileName, std::string fileData);
};

