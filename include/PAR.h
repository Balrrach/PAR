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
extern float lambda;
extern float optimumDistance;


//Calculates infeseability of a given point in a given cluster k under a certain configuration shaping
int calculateIncrementInfeseability(int p, int k, const vector<int> & shaping) {
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


//Returns true if the shaping is valid
bool checkShaping(const vector<int> & shaping) {
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


float calculateAggregate(const vector<Cluster>& clusters, const vector<int>& shaping) {
	float generalDeviation = calculateGeneralDeviation(clusters);
	int infeasibility = calculateShapingInfeasibility(shaping);

	return generalDeviation + infeasibility * lambda;
}


//Calculates Error_distance
float calculateErrorDistance(const vector<Cluster>& clusters) {
	return abs(calculateGeneralDeviation(clusters) - optimumDistance);
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

	float generalDeviation = calculateGeneralDeviation(clusters);
	int infeasibility = calculateShapingInfeasibility(shaping);

	cout << "General deviation: " << generalDeviation << endl;
	cout << "Infeasibility: " << infeasibility << endl;
	cout << "Lambda: " << lambda << endl;
	cout << "Fitness: " << generalDeviation + infeasibility * lambda << endl;
	cout << "########################################################################################################################" << endl;
	cout << endl;
}