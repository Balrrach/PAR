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
	vector<float> centroid(dimension, 0);
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


void findBestNeighbour(vector<Cluster> & clusters, vector<int> & shaping, vector<int> & index, vector<pair<int, int>> & neighbourhood, int seed, int & iters) {
	vector<int> shapingCopy(shaping);
	int point, newCluster, currentCluster, currentIfs, newIfs;
	float currentDistance, newDistance;

	shuffle(index.begin(), index.end(), std::default_random_engine(seed));
	for (int i = 0; i < index.size(); i++) {
		iters++;
		point = neighbourhood[index[i]].first;
		currentCluster = shaping[point];
		newCluster = neighbourhood[index[i]].second;

		if (clusters[currentCluster].getClusterSize() > 1) {
			currentIfs = calculateIncrementInfeseability(point, currentCluster, shaping);
			newIfs = calculateIncrementInfeseability(point, newCluster, shaping);

			if (newIfs < currentIfs) {
				currentDistance = calculateDistance(g_points[point], clusters[currentCluster].getCentroid());
				newDistance = calculateDistance(g_points[point], clusters[newCluster].getCentroid());
				if ((newIfs + newDistance) < (currentDistance + currentIfs)) {
					shaping[point] = newCluster;
					clusters[currentCluster].removePoint(point);
					clusters[newCluster].addPoint(point);
					break;
				}
			}
		}
	}
}


void BL(int seed, int iters) {
	iters = 100000;
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size());
	initializeClusters(clusters, shaping);

	vector<pair<int, int>> neighbourhood;
	for (int p = 0; p < g_points.size(); p++)
		for (int k = 0; k < K; k++)
			if (k != shaping[p]) {
				neighbourhood.push_back(pair<int, int>{p, k});
			}

	vector<int> index;
	initializeUniformInt(index, 0, neighbourhood.size());
	
	int i = 0;
	while (i < iters) {
		findBestNeighbour(clusters, shaping, index, neighbourhood, seed, i);
	}

	printSolution(clusters, shaping);
}