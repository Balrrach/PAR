#pragma once

#include <utility>
#include <vector>
#include <map>

using namespace std;


map<int, vector <pair<int, int> > > restrictionsMap;
vector<vector<int>> restrictionsList;
vector<vector<float>> g_points;
float optimumDistance;
int dimension;
int K;
float lambda;


class executionParameters {
public:
	static int seed;
	static int iters;

	executionParameters() {};
	void initialize() {
		seed = 4;
		iters = 100000;
	};
};

int executionParameters :: seed;
int executionParameters :: iters;