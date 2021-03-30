#pragma once

#include <functional>
#include <algorithm>
#include <random>
#include <vector>
#include <limits.h>

#include "random.h"
#include "Cluster.h"
#include "VectorUtilities.h"

using namespace std;

extern vector<vector<float> > g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int> > restrictionsList;
extern int dimension;
extern int K;


//Prints the final solution
void printSolution(const vector<Cluster>& clusters) {
	int total_points = g_points.size();

	for (int i = 0; i < K; i++) {
		//Print cluster centroid
		clusters[i].printClusterCentroid();
		//Print cluster points
		clusters[i].printClusterPoints();
	}
	cout << endl;

	/*
	//Print solution
	cout << "########################################################################################################################" << endl << endl;
	cout << "Vector solution: (";
	for (int i = 0; i < total_points - 1; i++)
		cout << g_points[i].getCluster() << ", ";

	cout << all_points[total_points - 1].getCluster() << ")" << endl;

	float lambda = calculateLambda(all_points, dimension, restrictions.size());
	float generalDeviation = calculateGeneralDeviation(clusters, K, dimension);
	int infeasibility = calculateSystemInfeasibility(all_points, restrictions);

	cout << "General deviation: " << generalDeviation << endl;
	cout << "Infeasibility: " << infeasibility << endl;
	cout << "Lambda: " << lambda << endl;
	cout << "Fitness: " << generalDeviation + infeasibility * lambda << endl;
	cout << "########################################################################################################################" << endl;
	cout << endl;
	*/
}

void calculateLowestInfeasibilityClusters(int p, vector<int> & liClusters, const vector<int> & shaping){
	int lifs = INT_MAX, ifs = 0;

	for (int i = 0; i < K; i++) {
		ifs = 0;
		for (int j = 0; j < restrictionsMap[p].size(); j++) {
			if (restrictionsMap[p][j].first == -1)
				if (shaping[restrictionsMap[p][j].second] == i)
					ifs++;
			if (restrictionsMap[p][j].first == 1)
				if (shaping[restrictionsMap[p][j].second] != i)
					ifs++;
		}

		if (ifs < lifs) {
			lifs = ifs;
			liClusters.clear();
			liClusters.push_back(i);
		}

		else if(ifs == lifs)
			liClusters.push_back(i);
	}
}


int calculateClosestCluster(int p, const vector<int> & liClusters, const vector<Cluster> & clusters) {
	double dist = 0.0, ldist = DBL_MAX;
	int closestCluster;

	for (int i = 0; i < liClusters.size(); i++) {
		dist = 0.0;

		for (int j = 0; j < dimension; j++) {
			dist += pow(clusters[i].getCentroidByPos(j) - g_points[p][j], 2.0);
		}

		dist = sqrt(dist);

		if (dist < ldist){
			ldist = dist;
			closestCluster = liClusters[i];
		}
	}

	return closestCluster;
}

void realocatePointToBestCluster(int p, vector<Cluster> & clusters, vector<int> & shaping){
	vector<int> liClusters;
	int bestCluster;

	if (shaping[p] == -1) {
		calculateLowestInfeasibilityClusters(p, liClusters, shaping);
		bestCluster = calculateClosestCluster(p, liClusters, clusters);
		clusters[bestCluster].addPoint(p);
		shaping[p] = bestCluster;
	}

	else {
		if (clusters[shaping[p]].getClusterSize() > 1) {
			calculateLowestInfeasibilityClusters(p, shaping, liClusters);
			bestCluster = calculateClosestCluster(p, liClusters, clusters);
			if (shaping[p] != bestCluster) {
				clusters[bestCluster].addPoint(p);
				shaping[p] = bestCluster;
			}
		}
	}
}

void initializeClusters(vector<Cluster> & clusters, vector<int> & shaping, int seed){

	bool repeat = true;
	vector<float> centroide(dimension);
	vector<int> index;
	initializeUniformInt(index, 0, g_points.size());

	while (repeat) {
		repeat = false;

		//-----Calculate clusters center randomly-----
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < dimension; j++)
				centroide[j] = Rand();

			Cluster c(centroide);
			clusters.push_back(c);
		}

		//-----Asociate each point to its best Cluster-----
		for (int p = 0; p < g_points.size(); p++)
			realocatePointToBestCluster(index[p], clusters, shaping);

		//printVectorElements(shaping);

		//-----Checking that all clusters are associated with at least one point-----
		for (int i = 0; i < K; i++)
			if (clusters[i].getClusterSize() < 1) {
				//cout << "Culpable: " << i << endl;

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
		clusters[i].recalculateCentroid();

	cout << "Clusters initialized = " << clusters.size() << endl << endl;

}