#pragma once

#include <cfloat>
#include <iostream>
#include <vector>

#include "ExecutionParameters.h"
#include "Cluster.h"
#include "PAR.h"
#include "csv.h"


class COPKM : virtual public PAR {

public:
	void calculateLowestInfeasibilityClusters(int p, std::vector<int>& liClusters, const std::vector<int>& shaping);
	int calculateClosestCluster(int p, const std::vector<int>& liClusters, const std::vector<Cluster>& clusters);
	int calculateBestCluster(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	void assignUnclusteredPoint(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	bool assignClusteredPoint(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	bool realocatePointToBestCluster(int p, std::vector<Cluster>& clusters, std::vector<int>& shaping);
	void initializeClusters(std::vector<Cluster>& clusters, std::vector<int>& shaping, int seed);
	std::vector<float> execute();
};