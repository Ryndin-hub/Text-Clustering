#pragma once

#include "Text.h"
#include <vector>
#include <string>

class FilesReader
{
public:
	static std::vector<Text> Read(const std::string& path);

private:
	static Text ReadFile(const std::string& path);
};

