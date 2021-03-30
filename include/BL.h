#pragma once

#include <map>

#include "Cluster.h"
#include "PAR.h"

using namespace std;

extern vector<vector<float> > g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int> > restrictionsList;
extern int dimension;
extern int K;


void BL(int seed, int iters) {
	vector<Cluster> clusters;

	//initializeClusters(clusters, seed);

	printSolution(clusters);
}