#include "Text.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

Text::Text(const std::string& path)
{
	this->m_path = path;
}

void Text::AddLemma(const std::string& lemma)
{
	auto it = m_lemmas.find(lemma);
	if (it == m_lemmas.end())
		m_lemmas.emplace(lemma, Lemma(lemma));

	m_lemmas[lemma].IncreaseCount();
	m_wordCount++;
}

void Text::SortLemmas()
{
	for (auto it = m_lemmas.begin(); it != m_lemmas.end(); ++it) {
		m_sortedLemmas.push_back(it->second);
	}
	std::sort(m_sortedLemmas.begin(), m_sortedLemmas.end(),
		[](Lemma& a, Lemma& b) -> bool
		{
			return a.GetTFIDF() > b.GetTFIDF();
		});
}

void Text::PrintSortedLemmas(const std::string& path)
{
	std::string fileName = this->m_path.substr(this->m_path.find_last_of("\\") + 1);
	std::ofstream file(path + "\\" + fileName);

	for (auto& lemma : m_sortedLemmas)
	{
		file << lemma.GetWord();
		file << " ";
		file << lemma.GetTFIDF();
		file << "\n";
	}

	file.close();
}

std::string Text::GetName()
{
	std::string fileName = this->m_path.substr(this->m_path.find_last_of("\\") + 1);

	return fileName;
}

void Text::FindFeatures(int maxSize)
{
	int count = 0;
	for (auto& lemma : m_sortedLemmas)
	{
		m_features.push_back(lemma.GetWord());
		count++;
		if (count >= maxSize) break;
	}
}
