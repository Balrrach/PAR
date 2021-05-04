#pragma once

#include <cfloat>
#include <iostream>
#include <vector>

#include "ExecutionParameters.h"
#include "Cluster.h"
#include "PAR.h"
#include "csv.h"
#include "random.h"


class BL : public PAR {

public:
	void assignPointToCluster(int point, int newCluster, std::vector<int>& shaping, std::vector<Cluster>& clusters);
	void generateNeighbourhood(std::vector<std::pair<int, int>>& neighbourhood, const std::vector<int>& shaping);
	int localSearch(std::vector<Cluster>& clusters, std::vector<int>& shaping, int seed, int maxIter);
	void initializeClusters(std::vector<Cluster>& clusters, std::vector<int>& shaping);
	std::vector<float> execute();
};