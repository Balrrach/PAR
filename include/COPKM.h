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


void initializeClusters(vector<Cluster>& clusters, vector<int>& shaping, int seed) {

	bool repeat = true;
	vector<double> centroide(dimension);
	vector<int> index;
	initializeUniformInt(index, 0, g_points.size());
	shuffle(index.begin(), index.end(), std::default_random_engine(seed));

	while (repeat) {
		repeat = false;

		//-----Calculate clusters center randomly-----
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < dimension; j++) {
				centroide[j] = Rand();
			}

			Cluster c(centroide);
			clusters.push_back(c);
		}

		//-----Asociate each point to its best Cluster-----
		for (int p = 0; p < g_points.size(); p++)
			realocatePointToBestCluster(index[p], clusters, shaping, true);

		//-----Checking that all clusters are associated with at least one point-----
		for (int i = 0; i < K; i++)
			if (clusters[i].getClusterSize() < 1) {
				repeat = true;
				clusters.clear();
				for (int j = 0; j < shaping.size(); j++)
					shaping[j] = -1;
				shuffle(index.begin(), index.end(), std::default_random_engine(seed));
				break;
			}

		//-----Reset-----
		//printVectorElements(index);			
		//for (int i = 0; i < g_points.size(); i++)
			//clusters[i];
	}

	//-----Recalculating the center of each cluster-----
	for (int i = 0; i < K; i++)
		clusters[i].calculateClusterCentroid();

	cout << "Clusters initialized = " << clusters.size() << endl << endl;
}


void COPKM(int seed, int iters){
	auto begin = std::chrono::high_resolution_clock::now();
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size(), -1);
	bool key;
	//vector<int> index;
	//initializeUniformInt(index, 0, g_points.size());
	Set_random(seed);

	initializeClusters(clusters, shaping, seed);

	bool repeat = true;
	int iter = 1;
	while (repeat) {
		//cout << "Iter- " << iter << "/" << iters << endl;
		repeat = false;

		// -----Change each point to the cluster that better fits it-----
		//shuffle(index.begin(), index.end(), std::default_random_engine(seed));
		for (int i = 0; i < g_points.size(); i++) {
			if (clusters[shaping[i]].getClusterSize() > 1) {
				key = realocatePointToBestCluster(i, clusters, shaping, false);
				if (key == true)
					repeat = true;
			}
		}

		// -----Recalculate the center of each cluster-----
		for (int i = 0; i < K; i++)
			clusters[i].calculateClusterCentroid();

		iter++;
	}

	cout << "Clustering completed in iteration : " << iter << endl << endl;

	auto end = std::chrono::high_resolution_clock::now();
	printSolution(shaping, clusters);
	std::cout << "Tiempo con Chrono: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
}