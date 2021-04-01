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
extern float lambda;


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


//Assigns a point to a cluster removing it from its current cluster and updating centroids
void assignPointToCluster(int point, int newCluster, vector<int> & shaping, vector<Cluster> & clusters) {
	int currentCluster = shaping[point];
	shaping[point] = newCluster;
	clusters[currentCluster].removePoint(point);
	clusters[newCluster].addPoint(point);
	clusters[currentCluster].calculateClusterCentroid();
	clusters[newCluster].calculateClusterCentroid();
}


//
int localSearch(vector<Cluster> & clusters, vector<int> & shaping, int seed){
	vector<pair<int, int>> neighbourhood;
	for (int p = 0; p < g_points.size(); p++)
		for (int k = 0; k < K; k++)
			if (k != shaping[p]) {
				neighbourhood.push_back(pair<int, int>{p, k});
			}

	vector<int> index;
	initializeUniformInt(index, 0, neighbourhood.size());

	int iters = 0;

	int point, newCluster, currentCluster;
	float currentFitness = calculateAggregate(clusters, shaping);
	float newFitness, generalDeviation;
	float currentIfs = calculateShapingInfeasibility(shaping), newIfs;
	float currentPointIfs, newPointIfs;
	bool bestNeightbourFound = false, betterNeighbourFound = false;
	

	while (iters < 100000 && !bestNeightbourFound) {
		shuffle(index.begin(), index.end(), std::default_random_engine(seed + iters));
		betterNeighbourFound = false;

		for (int i = 0; i < index.size(); i++) {
			if (iters == 100000)
				break;
			iters++;

			//cout << currentFitness << endl;
			point = neighbourhood[index[i]].first;
			currentCluster = shaping[point];
			newCluster = neighbourhood[index[i]].second;

			if (clusters[currentCluster].getClusterSize() > 1) {
				assignPointToCluster(point, newCluster, shaping, clusters);

				currentPointIfs = calculateIncrementInfeseability(point, currentCluster, shaping);
				newPointIfs = calculateIncrementInfeseability(point, newCluster, shaping);
				generalDeviation = calculateGeneralDeviation(clusters);
				newIfs = currentIfs + newPointIfs - currentPointIfs;
				
				newFitness = generalDeviation + (newIfs*lambda);

				if (newFitness < currentFitness) {
					currentIfs = newIfs;
					currentFitness = newFitness;
					neighbourhood[index[i]].second = currentCluster;
					betterNeighbourFound = true;
					break;
				}

				else
					assignPointToCluster(point, currentCluster, shaping, clusters);
			}
		}
		if(!betterNeighbourFound)
			bestNeightbourFound = true;
	}

	return iters;
}


void BL(int seed, int iters) {
	auto begin = std::chrono::high_resolution_clock::now();

	iters = 100000;
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size());
	initializeClusters(clusters, shaping);
	
	iters = localSearch(clusters, shaping, seed);

	auto end = std::chrono::high_resolution_clock::now();
	printSolution(clusters, shaping);
	std::cout << "Tiempo con Chrono: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	cout << "Numero de iteraciones: " << iters << endl;
}