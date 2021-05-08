#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

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

	ExecutionParameters() {};
	void initialize();
	std::string algorithmError();
};