#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <limits.h>
#include <map>
#include <random>
#include <utility>
#include <vector>
#include <math.h>

#include "Cluster.h"
#include "ExecutionParameters.h"
#include "Random.h"


class PAR : public ExecutionParameters
{
protected:
	int evaluationsCounter;
	std::uniform_int_distribution<int> randomPoint;
	std::uniform_int_distribution<int> randomCluster;

	PAR();

	//Execute
	virtual std::vector<float> execute();

	//Initializer
	void initializeRandomSolution(std::vector<Cluster> & clusters, std::vector<int> & shaping);

	//Cluster related
	void createClusters(std::vector<Cluster> & clusters);
	float calculateGeneralDeviation(const std::vector<Cluster>& clusters);
	float calculateErrorDistance(const std::vector<Cluster>& clusters);
	void transferPoint(int point, int currentCluster, int newCluster, std::vector<Cluster>& clusters);
	void forceTransferPoint(int p, int currentCluster, int newCluster, std::vector<Cluster> & clusters);
	void checkClusters(const std::vector<Cluster> & clusters);
	
	//Shaping Related
	bool checkShaping(const std::vector<int>& shaping);
	void fixShaping(std::vector<int> & newDescendant);
	void updateShapping(int p, int newCluster, std::vector<int>& shaping);
	void fromShappingToClusters(const std::vector<int> & shapping, std::vector<Cluster> & clusters);
	int calculateIncrementInfeseability(int p, int k, const std::vector<int>& shaping);
	int calculateShapingInfeasibility(const std::vector<int>& shaping);
	float calculateShapingFitness(const std::vector<int> & shaping);

	//Printers
	void printSolution(const std::vector<Cluster>& clusters, const std::vector<int>& shaping);
	void printSolution(const std::vector<int> & shaping);
	void printShaping(const std::vector<int> & shaping);
	void printRestrictions();
	void printPoints();
	std::vector<float> createOutput(const std::vector<Cluster> & clusters, const std::vector<int> & shaping, float time);
	std::vector<float> createOutput(const std::vector<int> & shaping, float time);

	//Others
	float calculateFitness(const std::vector<Cluster> & clusters, const std::vector<int> & shaping);
};
