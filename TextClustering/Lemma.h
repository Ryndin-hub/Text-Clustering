#pragma once

#include <string>

class Lemma
{
public:
	Lemma() = default;
	Lemma(const std::string& word);
	void IncreaseCount();
	void CalculateTF(int Cd);
	void CalculateIDF(int D, int Dt);
	void CalculateTFIDF();
	const std::string& GetWord() { return m_word; }
	double GetTFIDF() { return m_TFIDF; }

private:
	std::string m_word;
	int m_count = 0;
	double m_TF;
	double m_IDF;
	double m_TFIDF;
};

