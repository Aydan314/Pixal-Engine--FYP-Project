#include "FileHandler.h"
FileHandler* FileHandler::m_instance = nullptr;

FileHandler::FileHandler()
{
}

FileHandler::~FileHandler()
{
	m_instance = nullptr;
}

FileHandler* FileHandler::Instance()
{
	if (!m_instance)
	{
		m_instance = new FileHandler();
	}
	return m_instance;
}

std::string FileHandler::ReadFile(std::string fileName)
{
	std::string fileContents;
	std::string line;
	std::ifstream file;

	file.open(fileName, std::ios::in);

	// Reads the file line by line adding it to a string //
	if (file)
	{
		while (getline(file, line))
		{
			fileContents += line + ((!file.eof()) ? "\n" : "");
		}
	}
	else std::cout << "!! Error in opening " << fileName << " !!\n";

	file.close();

	return fileContents;
}

std::vector<std::string> FileHandler::SplitData(std::string data, std::string seperator)
{
	std::vector<std::string> newData;
	std::string newWord;
	bool done = false;

	int startPos = 0;
	int endPos;

	while (!done)
	{
		// finds the position of the first seperator in the string //

		endPos = data.substr(startPos, data.size()).find(seperator);

		if (endPos < 0)
		{
			endPos = data.size();
			done = true;
		}

		// Adds the value between the start position and the seperator to an array //
		newWord = data.substr(startPos, endPos);

		newData.push_back(newWord);

		// The new start position is set to the position after the pervious seperator in order to find the new one //
		startPos = endPos + 1 + startPos;
	}

	return newData;
}

void FileHandler::WriteFile(std::string fileName, std::string fileData)
{
	std::ofstream file;
	file.open(fileName, std::ios::out);

	// Checks if the file is valid and writes to it //
	if (file)
	{
		file << fileData;
	}
	else std::cout << "!! Error in opening " << fileName << " !!\n";

	file.close();
}