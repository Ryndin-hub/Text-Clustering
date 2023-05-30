#include "Lemma.h"

Lemma::Lemma(const std::string& word)
{
	this->m_word = word;
}

void Lemma::IncreaseCount()
{
	m_count++;
}

void Lemma::CalculateTF(int Cd)
{
	m_TF = m_count / double(Cd);
}

void Lemma::CalculateIDF(int D, int Dt)
{
	m_IDF = log(double(D) / double(Dt));
}

void Lemma::CalculateTFIDF()
{
	m_TFIDF = m_TF * m_IDF;
}
