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


int calculateIncrementInfeseability(int p, int k, vector<int> shaping) {
	int incrementIfs = 0; 

	for (int r = 0; r < restrictionsMap[p].size(); r++) {
		if (restrictionsMap[p][r].first == -1)
			if (k == shaping[restrictionsMap[p][r].second])
				incrementIfs++;
		if (restrictionsMap[p][r].first == 1)
			if (k != shaping[restrictionsMap[p][r].second])
				incrementIfs++;
	}

	return incrementIfs;
}


void calculateLowestInfeasibilityClusters(int p, vector<int> & liClusters, const vector<int> & shaping, bool start){
	int lifs = INT_MAX, clusterIfs = 0;
	//vector<int> index;

	for (int k = 0; k < K; k++) {
		clusterIfs = calculateIncrementInfeseability(p, k, shaping);

		if (clusterIfs < lifs) {
			lifs = clusterIfs;
			liClusters.clear();
			liClusters.push_back(k);
		}

		else if (clusterIfs == lifs)
			liClusters.push_back(k);
	}
}


int calculateClosestCluster(int p, const vector<int> & liClusters, const vector<Cluster> & clusters) {
	float sum = 0.0, dist = 0.0, ldist = DBL_MAX;
	int closestCluster = -1;
	for (int i = 0; i < liClusters.size(); i++) {
		sum = 0.0;

		for (int j = 0; j < dimension; j++) {
			sum += pow(clusters[liClusters[i]].getCentroidByPos(j) - g_points[p][j], 2.0);
		}

		dist = sqrt(sum);

		if (dist < ldist){
			ldist = dist;
			closestCluster = liClusters[i];
		}
	}

	return closestCluster;
}

bool realocatePointToBestCluster(int p, vector<Cluster> & clusters, vector<int> & shaping, bool start){
	vector<int> liClusters;
	int bestCluster = -1, currentCluster = shaping[p];

	if (currentCluster == -1) {
		calculateLowestInfeasibilityClusters(p, liClusters, shaping, start);
		bestCluster = calculateClosestCluster(p, liClusters, clusters);
		clusters[bestCluster].addPoint(p);
		shaping[p] = bestCluster;
		return true;
	}

	else {
		if (clusters[shaping[p]].getClusterSize() > 1) {
			calculateLowestInfeasibilityClusters(p, liClusters, shaping, start);
			bestCluster = calculateClosestCluster(p, liClusters, clusters);
			if (currentCluster != bestCluster) {
				clusters[currentCluster].removePoint(p);
				clusters[bestCluster].addPoint(p);
				shaping[p] = bestCluster;
				return true;
			}
		}
	}

	return false;
}


//Calculates infeasibility of a given shaping
int calculateShapingInfeasibility(const vector<int> & shaping) {
	int sifs = 0;
	for (int i = 0; i < restrictionsList.size(); i++) {
		if (restrictionsList[i][0] == -1)
			if (shaping[restrictionsList[i][1]] == shaping[restrictionsList[i][2]])
				sifs++;

		if (restrictionsList[i][0] == 1)
			if (shaping[restrictionsList[i][1]] != shaping[restrictionsList[i][2]])
				sifs++;
	}

	return sifs;
}


//Calculates general deviation
float calculateGeneralDeviation(const vector<Cluster> & clusters) {
	float aux = 0;
	for (int i = 0; i < K; i++)
		aux += clusters[i].calculateIntraClusterMeanDeviation();

	return aux / K;
}


//Calculates lambda value
float calculateLambda(){
	//Maximum distance calculation
	float max = 0.0, dist;

	for (int i = 0; i < g_points.size(); i++) {
		for (int j = 0; j < g_points.size(); j++) {
			if (j > i) {
				dist = calculateDistance(g_points[i], g_points[j]);;

				if (max < dist)
					max = dist;
			}
		}
	}

	return max / restrictionsList.size();
}


float calculateAggregate(const vector<Cluster>& clusters, const vector<int>& shaping) {
	float lambda = calculateLambda();
	float generalDeviation = calculateGeneralDeviation(clusters);
	int infeasibility = calculateShapingInfeasibility(shaping);

	return generalDeviation + infeasibility * lambda;
}


//Prints the final solution
void printSolution(const vector<Cluster>& clusters, const vector<int> & shaping) {
	int total_points = g_points.size();

	for (int i = 0; i < K; i++) {
		//Print cluster centroid
		clusters[i].printClusterCentroid();
		//Print cluster points
		clusters[i].printClusterPoints();
	}
	cout << endl;

	//Print solution
	cout << "########################################################################################################################" << endl << endl;
	cout << "Vector solution: (";
	for (int i = 0; i < total_points - 1; i++)
		cout << shaping[i] << ", ";
	cout << shaping[total_points - 1] << ")" << endl;

	float lambda = calculateLambda();
	float generalDeviation = calculateGeneralDeviation(clusters);
	int infeasibility = calculateShapingInfeasibility(shaping);

	cout << "General deviation: " << generalDeviation << endl;
	cout << "Infeasibility: " << infeasibility << endl;
	cout << "Lambda: " << lambda << endl;
	cout << "Fitness: " << generalDeviation + infeasibility * lambda << endl;
	cout << "########################################################################################################################" << endl;
	cout << endl;
}
