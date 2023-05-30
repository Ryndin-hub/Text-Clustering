#pragma once

#include "Text.h"
#include <vector>
#include <set>

class Collection
{
private:
	class Cluster
	{
	public:
		Cluster() = default;
		std::string name;
		std::map<std::string, bool> vectorSpace;
		std::map<std::string, double> distances;
	};

public:
	Collection() = default;
	void Init(const std::string& path);
	void CalculateDt();
	void CalculateTFIDF();
	void SortLemmas();
	void PrintSortedLemmas(const std::string& path);
	void SetVectorSpaceLemmas();
	void ClusterTexts();
	void InitializeClusters(std::vector<Cluster>* clusters);
	void CalculateClustersDistances(std::vector<Cluster>* clusters);
	void FindFeatures();
	double CalculateDistance(Cluster* a, Cluster* b);

private:
	std::vector<Text> m_texts;
	std::map<std::string, int> m_lemmasDt;
	std::set<std::string> m_vectorSpaceLemmas;
};

