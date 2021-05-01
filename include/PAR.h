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


class PAR {

public:
	static std::map<int, std::vector <std::pair<int, int> > > restrictionsMap;
	static std::vector<std::vector<int>> restrictionsList;
	static std::vector<std::vector<float>> g_points;
	static float optimumDistance;
	static int dimension;
	static int K;
	static float lambda;

	void cleanGlobals();
	void calculateLambda();

	int calculateIncrementInfeseability(int p, int k, const std::vector<int>& shaping);
	int calculateShapingInfeasibility(const std::vector<int>& shaping);
	float calculateGeneralDeviation(const std::vector<Cluster>& clusters);
	float calculateFitness(const std::vector<Cluster>& clusters, const std::vector<int>& shaping);
	float calculateErrorDistance(const std::vector<Cluster>& clusters);

	bool checkShaping(const std::vector<int>& shaping);
	void printSolution(const std::vector<Cluster>& clusters, const std::vector<int>& shaping);
	std::vector<float> createOutput(const std::vector<Cluster>& clusters, const std::vector<int>& shaping, float time);
};