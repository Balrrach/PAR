#pragma once

#include <cfloat>
#include <iostream>
#include <vector>

#include "ExecutionParameters.h"
#include "Cluster.h"
#include "PAR.h"
#include "CSV.h"
#include "Random.h"


class BL : public PAR {

public:
	std::vector<float> execute();
	BL();

protected:
	int BLMaxIters;
	int BLCurrentIfs;

	void assignPointToCluster(int point, int newCluster, std::vector<int>& shaping, std::vector<Cluster>& clusters);
	void initializeNeighbourhood(const std::vector<int>& shaping);
	int localSearch(std::vector<Cluster>& clusters, std::vector<int>& shaping);
	
	void initializeIfs(const std::vector<int> & shaping);
	void updateIfs(int newIfs);
	float exploreNeighbour(std::vector<Cluster> & currentClusters, std::vector<int> & currentShaping, int & point, int & newCluster, int & newIfs);

	float BLCore(std::vector<Cluster> & clusters, std::vector<int> & shaping);

private:
	std::uniform_int_distribution<int> randomNeighbour;
	std::vector<std::pair<int, int>> neighbourhood;
	std::vector<int> index;
	int calculateNewFitness(std::vector<Cluster> & currentClusters, std::vector<int> & currentShaping, int point, int newCluster, int oldCluster, float & newFitness);
};
