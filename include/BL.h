#pragma once

#include <map>
#include <set>

#include "Cluster.h"
#include "PAR.h"
#include "random.h"

using namespace std;

extern vector<vector<float> > g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int> > restrictionsList;
extern int dimension;
extern int K;

//Returns true if the shaping is valid
bool checkShaping(const vector<int> & shaping){
	set<int> aux;
	for (int i = 0; i < K; i++)
		aux.insert(i);

	set<int>::iterator it;
	for (int i = 0; i < shaping.size(); i++) {
		it = aux.find(shaping[i]);
		if (it != aux.end())
			aux.erase(it);
	}
	
	if (aux.size() > 0)
		return false;
	else
		return true;
}


void initializeClusters(vector<Cluster>& clusters, vector<int> & shaping) {

	bool repeat = true;
	while (repeat) {
		//-----Asociate each point to a random Cluster-----
		for (int p = 0; p < g_points.size(); p++)
			shaping[p] = Randint(0, K-1);

		//-----Checking that all clusters are associated with at least one point-----
		for (int i = 0; i < K; i++)
			if (checkShaping(shaping)) {
				repeat = false;
			}
	}

	//-----Initializing clusters-----
	vector<double> centroid(dimension, 0);
	for (int i = 0; i < K; i++)
		clusters.push_back(Cluster (centroid));

	//-----Adding points to clusters-----
	for (int p = 0; p < g_points.size(); p++)
		clusters[shaping[p]].addPoint(p);

	//-----Recalculating the center of each cluster-----
	for (int i = 0; i < K; i++)
		clusters[i].calculateClusterCentroid();

	cout << "Clusters initialized = " << clusters.size() << endl << endl;
}


void BL(int seed, int iters) {
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size());
	initializeClusters(clusters, shaping);

	//bestNeighbour(cluster, shaping);

	printSolution(clusters, shaping);
}