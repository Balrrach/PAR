#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#include "utilities.h"


class ExecutionParameters {
public:
	static std::map<int, std::vector <std::pair<int, int>>> restrictionsMap;
	static std::vector<std::vector<int>> restrictionsList;
	static std::vector<std::vector<float>> g_points;
	static int pointsSize;
	static float optimumDistance;
	static int dimension;
	static int K;
	static float lambda;
	static std::mt19937 rng;
	static int seed;
	static int maxIters;

	void initialize();

	void cleanGlobals();
	void calculateLambda();

	std::string algorithmError();
};