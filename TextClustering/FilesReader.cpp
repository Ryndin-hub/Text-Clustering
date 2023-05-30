#include "FilesReader.h"
#include <string>
#include <filesystem>
#include <fstream>

Text FilesReader::ReadFile(const std::string& path)
{
	std::ifstream file(path);
	std::string word;
	Text text(path);

	while (file >> word)
	{
		text.AddLemma(word);
	}

	return text;
}

std::vector<Text> FilesReader::Read(const std::string& path)
{
	std::vector<Text> texts;

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string fileName = entry.path().string();
		if (fileName.substr(fileName.find_last_of(".") + 1) == "txt")
		{
			texts.push_back(ReadFile(fileName));
		}
	}

	return texts;
}