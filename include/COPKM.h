#pragma once

#include <cfloat>
#include <chrono>
#include <iostream>
#include <vector>

#include "ExecutionParameters.h"
#include "Cluster.h"
#include "PAR.h"
#include "csv.h"


class COPKM : public PAR {

public:
	void calculateLowestInfeasibilityClusters(int p, std::vector<int>& liClusters, const std::vector<int>& shaping);
	int calculateClosestCluster(int p, const std::vector<int>& liClusters, const std::vector<Cluster>& clusters);
	void transferPoint(int p, int currentCluster, int newCluster, std::vector<Cluster>& clusters);
	void updateShapping(int p, int newCluster, std::vector<int>& shaping);
	int calculateBestCluster(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	void assignUnclusteredPoint(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	bool assignClusteredPoint(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	bool realocatePointToBestCluster(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	void initializeClusters(std::vector<Cluster>& clusters, std::vector<int>& shaping, int seed);
	std::vector<float> executeCOPKM();
};