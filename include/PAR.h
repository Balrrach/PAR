#pragma once

#include <functional>
#include <algorithm>
#include <random>
#include <vector>

#include "Random.h"
#include "VectorUtilities.h"

using namespace std;


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


void realocatePointToBestCluster(int p, vector<Cluster>& clusters){
	clusters[p % K].addPoint(p);
}

void initializeClusters(vector<Cluster> & clusters, int seed){

	bool repeat = true;
	vector<float> centroide(dimension);
	vector<int> index;
	initializeUniformInt(index, 0, g_points.size());

	while (repeat) {
		shuffle(index.begin(), index.end(), std::default_random_engine(seed));
		clusters.clear();

		//-----Calculate clusters center randomly-----
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < dimension; j++)
				centroide[j] = Rand();

			Cluster c(centroide);
			clusters.push_back(c);
		}

		//-----Asociate each point to its best Cluster-----
		for (int p = 0; p < g_points.size(); p++)
			realocatePointToBestCluster(index[p], clusters);

		//-----Checking that all clusters are associated with at least one point-----
		repeat = false;
		for (int i = 0; i < clusters.size(); i++)
			if (clusters[i].getClusterSize() < 1) {
				repeat = true;
				break;
			}

		//-----Reset-----
		//printVectorElements(index);			
			//for (int i = 0; i < g_points.size(); i++)									ESTO DEBERIA SER UN DESTROY
				//clusters[all_points[i].getCluster()].forceRemovePoint(all_points[i]);
	}

	//-----Recalculating the center of each cluster-----
	for (int i = 0; i < K; i++)
		clusters[i].recalculateCentroid();

	cout << "Clusters initialized = " << clusters.size() << endl << endl;

}