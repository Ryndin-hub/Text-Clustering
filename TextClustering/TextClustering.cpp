#include <iostream>
#include <filesystem>
#include "Collection.h"

int main()
{
	std::string mainDirectoryPath = std::filesystem::current_path().string();
	if (mainDirectoryPath.substr(mainDirectoryPath.find_last_of("\\") + 1) == "TextClustering")
		mainDirectoryPath += "\\..";
	else if (mainDirectoryPath.substr(mainDirectoryPath.find_last_of("\\") + 1) == "Release")
		mainDirectoryPath += "\\..\\..";

	Collection collection;
	collection.Init(mainDirectoryPath + "\\Texts");
	collection.ClusterTexts();
	collection.PrintSortedLemmas(mainDirectoryPath + "\\SortedTFIDF");

	system("pause");
}
