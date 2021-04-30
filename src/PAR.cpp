#include "PAR.h"

using namespace std;

map<int, vector <pair<int, int> > > PAR::restrictionsMap;
vector<vector<int>> PAR::restrictionsList;
vector<vector<float>> PAR::g_points;
float PAR::optimumDistance;
int PAR::dimension;
int PAR::K;
float PAR::lambda;


//Calculates infeseability of a given point in a given cluster k under a certain configuration shaping
int PAR::calculateIncrementInfeseability(int p, int k, const vector<int>& shaping) {
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
bool PAR::checkShaping(const vector<int>& shaping) {
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
int PAR::calculateShapingInfeasibility(const vector<int>& shaping) {
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
float PAR::calculateGeneralDeviation(const vector<Cluster>& clusters) {
	float aux = 0;
	for (int i = 0; i < K; i++)
		aux += clusters[i].calculateIntraClusterMeanDeviation((new PAR)->g_points);

	return aux / K;
}


//Calculates fitness of a given shaping
float PAR::calculateFitness(const vector<Cluster>& clusters, const vector<int>& shaping) {
	float generalDeviation = calculateGeneralDeviation(clusters);
	int infeasibility = calculateShapingInfeasibility(shaping);

	return generalDeviation + infeasibility * lambda;
}


//Calculates Error_distance
float PAR::calculateErrorDistance(const vector<Cluster>& clusters) {
	return abs(calculateGeneralDeviation(clusters) - optimumDistance);
}


//Prints the final solution
void PAR::printSolution(const vector<Cluster>& clusters, const vector<int>& shaping) {
	int total_points = g_points.size();

	for (int i = 0; i < K; i++) {
		//Print cluster centroid
		clusters[i].printClusterCentroid(dimension);
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


//Cleans global variables
void PAR::cleanGlobals() {
	g_points.clear();
	restrictionsMap.clear();
	restrictionsList.clear();
	dimension = 0;
	K = 0;
	lambda = 0;
	optimumDistance = 0;
}


//Calculates lambda value
void PAR::calculateLambda() {
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

	lambda = max / restrictionsList.size();
}


//Creates the output data
vector<float> PAR::createOutput(const vector<Cluster>& clusters, const vector<int>& shaping, float time) {
	vector<float> sol;
	sol.push_back((float)(new PAR)->calculateShapingInfeasibility(shaping));
	sol.push_back((new PAR)->calculateErrorDistance(clusters));
	sol.push_back((new PAR)->calculateFitness(clusters, shaping));
	sol.push_back(time);
	return sol;
}