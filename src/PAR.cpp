#include "PAR.h"

using namespace std;

map<int, vector <pair<int, int> > > PAR::restrictionsMap;
vector<vector<int>> PAR::restrictionsList;
vector<vector<float>> PAR::g_points;
int PAR::pointsSize;
float PAR::optimumDistance;
int PAR::dimension;
int PAR::K;
float PAR::lambda;
std::mt19937 PAR::rng;


PAR::PAR(){ 
	Set_random((new ExecutionParameters)->seed);
	rng = mt19937((new ExecutionParameters)->seed);
}

vector<float> PAR::execute() { return {}; }


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
	for (int i = 0; i < K; i++)
		if (find(shaping.begin(), shaping.end(), i) == shaping.end())
			return false;

	return true;
}


//Changes a set of points from cluster until strong conditions are met
void PAR::fixShaping(vector<int> & shaping)
{
	while (checkShaping(shaping) == false)
		for (int i = 0; i < K; i++)
			if (find(shaping.begin(), shaping.end(), i) == shaping.end())
				shaping[Randint(0, pointsSize-1)] = i;
}

//void PAR::fixShaping(vector<int> & newDescendant)
//{
//	while (checkShaping(newDescendant) == false) {
//		set<int> aux, missingClusters;
//		for (int i = 0; i < K; i++)
//			missingClusters.insert(i);
//
//		for (const int & i : newDescendant)
//			aux.insert(i);
//
//		for (const auto & i : aux)
//			missingClusters.erase(i);
//	}
//}


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


float PAR::calculateShapingFitness(const std::vector<int> & shaping)
{
	vector<Cluster> clusters;
	fromShappingToClusters(shaping, clusters);
	return calculateFitness(clusters, shaping);
}


//Calculates general deviation
float PAR::calculateGeneralDeviation(const vector<Cluster>& clusters) {
	float aux = 0;
	for (int i = 0; i < K; i++)
		aux += clusters[i].calculateIntraClusterMeanDeviation(g_points);

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
	cout << "#####################---Estadisticos---#####################" << endl;
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
	cout << "###########################################################" << endl;
	cout << endl;
}


void PAR::printSolution(const std::vector<int> & shaping)
{
	vector<Cluster> clusters;
	fromShappingToClusters(shaping, clusters);
	printSolution(clusters, shaping);
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
	sol.push_back((float)calculateShapingInfeasibility(shaping));
	sol.push_back(calculateGeneralDeviation(clusters));
	sol.push_back(calculateFitness(clusters, shaping));
	sol.push_back(time);
	return sol;
}

std::vector<float> PAR::createOutput(const std::vector<int> & shaping, float time)
{
	vector<Cluster> clusters;
	fromShappingToClusters(shaping, clusters);
	return createOutput(clusters, shaping, time);
}


void PAR::printRestrictions()
{
	int k = 0, l = 0;
	for (int c = 0; c < restrictionsList.size(); c++) {
		if (restrictionsList[c][2] == -1) {
			cout << "Restriccion CL numero " << c << " : (" << restrictionsList[c][0] << " , " << restrictionsList[c][1] << ")" << endl;
			k++;
		}
		if (restrictionsList[c][2] == 1) {
			cout << "Restriccion ML numero " << c << " : (" << restrictionsList[c][0] << " , " << restrictionsList[c][1] << ")" << endl;
			l++;
		}
	}

	cout << endl;

	for (int i = 0; i < g_points.size(); i++)
		for (int j = 0; j < restrictionsMap[i].size(); j++)
			cout << "Restriccion " << j << " asociada al punto " << i << " de tipo " << restrictionsMap[i][j].first << " pareja: " << restrictionsMap[i][j].second << endl;
}


void PAR::printPoints()
{
	for (auto i : g_points) {
		cout << "(";
		for (auto j: i)
			cout << j << " ";

		cout << ")" << endl;
	}
}


void PAR::printShaping(const std::vector<int>& shaping)
{
	for (auto i : shaping)
		cout << i << " ";
	cout << endl;
}


void PAR::transferPoint(int p, int currentCluster, int newCluster, vector<Cluster>& clusters)
{
	clusters[currentCluster].removePoint(p);
	clusters[newCluster].addPoint(p);
}


void PAR::forceTransferPoint(int p, int currentCluster, int newCluster, vector<Cluster> & clusters)
{
	clusters[currentCluster].forceRemovePoint(p);
	clusters[newCluster].addPoint(p);
}


void PAR::updateShapping(int p, int newCluster, vector<int>& shaping)
{
	shaping[p] = newCluster;
}


void PAR::fromShappingToClusters(const std::vector<int>& shapping, std::vector<Cluster>& clusters)
{
	createClusters(clusters);
	int a = shapping[0];
	for (int i = 0; i < pointsSize; i++)
		clusters[shapping[i]].addPoint(i);

	for (auto & c : clusters)
		c.calculateClusterCentroid(g_points);
}

void PAR::createClusters(std::vector<Cluster> & clusters)
{
	clusters.clear();
	vector<float> centroide(dimension);

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < dimension; j++) {
			centroide[j] = Rand();
		}

		clusters.push_back(Cluster(centroide, i));
	}
}