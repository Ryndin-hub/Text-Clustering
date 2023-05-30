#pragma once

#include "Lemma.h"
#include <map>
#include <string>
#include <vector>

class Text
{
public:
	Text(const std::string& path);
	void AddLemma(const std::string& lemma);
	std::map<std::string, Lemma>* GetLemmas() { return &m_lemmas; }
	int GetWordCount() { return m_wordCount; }
	void SortLemmas();
	void PrintSortedLemmas(const std::string& path);
	std::vector<Lemma>* GetSortedLemmas() { return &m_sortedLemmas; }
	std::string GetName();
	void FindFeatures(int maxSize);
	std::vector<std::string>* GetFeatures() { return &m_features; }

private:
	std::map<std::string, Lemma> m_lemmas;
	std::vector<Lemma> m_sortedLemmas;
	int m_wordCount = 0;
	std::string m_path;
	std::vector<std::string> m_features;
};

