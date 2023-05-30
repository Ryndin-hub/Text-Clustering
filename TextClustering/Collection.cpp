#include "Collection.h"
#include "FilesReader.h"
#include <iostream>

void Collection::Init(const std::string& path)
{
	m_texts = FilesReader::Read(path);
}

void Collection::CalculateDt()
{
	for (auto& text : m_texts)
	{
		for (auto& lemma : *text.GetLemmas())
		{
			auto it = m_lemmasDt.find(lemma.second.GetWord());
			if (it == m_lemmasDt.end())
				m_lemmasDt.emplace(lemma.second.GetWord(), 0);

			m_lemmasDt[lemma.second.GetWord()]++;
		}
	}
}

void Collection::CalculateTFIDF()
{
	CalculateDt();

	for (auto& text : m_texts)
	{
		for (auto& lemma : *text.GetLemmas())
		{
			lemma.second.CalculateTF(text.GetWordCount());
			lemma.second.CalculateIDF(m_texts.size(), m_lemmasDt[lemma.second.GetWord()]);
			lemma.second.CalculateTFIDF();
		}
	}
}

void Collection::SortLemmas()
{
	for (auto& text : m_texts)
	{
		text.SortLemmas();
	}
}

void Collection::FindFeatures()
{
	for (auto& text : m_texts)
	{
#define MAX_FEATURES 1000
		text.FindFeatures(MAX_FEATURES);
	}
}

void Collection::PrintSortedLemmas(const std::string& path)
{
	for (auto& text : m_texts)
	{
		text.PrintSortedLemmas(path);
	}
}

void Collection::SetVectorSpaceLemmas()
{
	for (auto& text : m_texts)
	{
		for (auto& feature : *text.GetFeatures())
		{
			m_vectorSpaceLemmas.insert(feature);
		}
	}
}

void Collection::ClusterTexts()
{
	CalculateTFIDF();
	SortLemmas();
	FindFeatures();
	SetVectorSpaceLemmas();

	std::vector<Cluster> clusters;

	InitializeClusters(&clusters);
	CalculateClustersDistances(&clusters);

	while (clusters.size() > 1)
	{
		double smallestDistance = std::numeric_limits<double>::max();
		Cluster clusterA;
		Cluster clusterB;
		std::string clusterBName;
		for (auto& cluster : clusters)
		{
			for (auto& distance : cluster.distances)
			{
				if (distance.second < smallestDistance)
				{
					smallestDistance = distance.second;
					clusterA = cluster;
					clusterBName = distance.first;
				}
			}
		}

		auto it = std::find_if(clusters.begin(), clusters.end(),
			[&](Cluster& c) -> bool
			{
				return c.name == clusterBName;
			});
		clusterB = (*it);

		std::cout << clusterA.name << " " << clusterB.name << " " << smallestDistance << "\n";

		clusters.push_back(Cluster());
		Cluster* newCluster = &clusters.back();
		newCluster->name = clusterA.name + "+" + clusterB.name;
		for (auto& cluster : clusters)
		{
			if (cluster.name == clusterA.name || cluster.name == clusterB.name || cluster.name == newCluster->name) continue;
			double newDistance = (cluster.distances[clusterA.name] + cluster.distances[clusterB.name]) / 2;
			cluster.distances.emplace(newCluster->name, newDistance);
			newCluster->distances.emplace(cluster.name, newDistance);
			cluster.distances.erase(clusterA.name);
			cluster.distances.erase(clusterB.name);
		}

		auto clusterAName = clusterA.name;
		it = std::find_if(clusters.begin(), clusters.end(),
			[&](Cluster& c) -> bool
			{
				return c.name == clusterAName;
			});
		clusters.erase(it);
		it = std::find_if(clusters.begin(), clusters.end(),
			[&](Cluster& c) -> bool
			{
				return c.name == clusterBName;
			});
		clusters.erase(it);
	}
}

void Collection::InitializeClusters(std::vector<Cluster>* clusters)
{
	for (auto& text : m_texts)
	{
		Cluster cluster;
		cluster.name = text.GetName();
		for (auto lemma : m_vectorSpaceLemmas)
			cluster.vectorSpace.emplace(lemma, false);

		for (auto lemma : *text.GetFeatures())
			cluster.vectorSpace[lemma] = true;

		clusters->push_back(cluster);
	}
}

void Collection::CalculateClustersDistances(std::vector<Cluster>* clusters)
{
	for (int i = 0; i < clusters->size() - 1; ++i)
	{
		for (int j = i + 1; j < clusters->size(); ++j)
		{
			auto distance = CalculateDistance(&clusters->at(i), &clusters->at(j));
			clusters->at(i).distances.emplace(clusters->at(j).name, distance);
			clusters->at(j).distances.emplace(clusters->at(i).name, distance);
		}
	}
}

double Collection::CalculateDistance(Cluster* a, Cluster* b)
{
	int dif = 0;
	for (auto& lemma : a->vectorSpace)
	{
		if (lemma.second != b->vectorSpace[lemma.first]) dif++;
	}
	return sqrt(dif);
}
