#pragma once

#include <iostream>
#include <Chrono>
#include <vector>
#include <map>

#include "Cluster.h"
#include "PAR.h"

using namespace std;

extern vector<vector<float> > g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int> > restrictionsList;
extern int dimension;
extern int K;


void COPKM(int seed, int iters){
	auto begin = std::chrono::high_resolution_clock::now();
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size(), -1);

	initializeClusters(clusters, shaping, seed);

	printSolution(shaping, clusters);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Tiempo con Chrono: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
}