#pragma once

#include <algorithm>
#include <functional>
#include <limits.h>
#include <map>
#include <random>
#include <utility>
#include <vector>

#include "Cluster.h"
#include "random.h"
#include "utilities.h"


class PAR
{
public:
	static std::map<int, std::vector <std::pair<int, int> > > restrictionsMap;
	static std::vector<std::vector<int>> restrictionsList;
	static std::vector<std::vector<float>> g_points;
	static int pointsSize;
	static float optimumDistance;
	static int dimension;
	static int K;
	static float lambda;

	void cleanGlobals();
	void calculateLambda();


	//Execute
	virtual std::vector<int> execute();


	//Cluster related
	void createClusters(std::vector<Cluster> & clusters);
	float calculateGeneralDeviation(const std::vector<Cluster>& clusters);
	float calculateFitness(const std::vector<Cluster>& clusters, const std::vector<int>& shaping);
	float calculateErrorDistance(const std::vector<Cluster>& clusters);
	void transferPoint(int point, int currentCluster, int newCluster, std::vector<Cluster>& clusters);
	
	
	//Shaping Related
	bool checkShaping(const std::vector<int>& shaping);
	void updateShapping(int p, int newCluster, std::vector<int>& shaping);
	void fromShappingToClusters(const std::vector<int> & shapping, std::vector<Cluster> & clusters);
	int calculateIncrementInfeseability(int p, int k, const std::vector<int>& shaping);
	int calculateShapingInfeasibility(const std::vector<int>& shaping);
	float calculateShapingFitness(const std::vector<int> & shaping);
	void printShaping(const std::vector<int>& shaping);


	//Printers
	void printSolution(const std::vector<Cluster>& clusters, const std::vector<int>& shaping);
	void printSolution(const std::vector<int> & shaping);
	std::vector<float> createOutput(const std::vector<Cluster>& clusters, const std::vector<int>& shaping, float time);
	void printRestrictions();
	void printPoints();
};