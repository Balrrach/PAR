#include "BL.h"

using namespace std;


//Assigns a point to a cluster removing it from its current cluster and updating centroids
void BL::assignPointToCluster(int point, int newCluster, vector<int>& shaping, vector<Cluster>& clusters) {
	int currentCluster = shaping[point];
	shaping[point] = newCluster;
	clusters[currentCluster].removePoint(point);
	clusters[newCluster].addPoint(point);
	clusters[currentCluster].calculateClusterCentroid((new PAR)->g_points);
	clusters[newCluster].calculateClusterCentroid((new PAR)->g_points);
}


void BL::generateNeighbourhood(vector<pair<int, int>>& neighbourhood, const vector<int>& shaping) {
	for (int p = 0; p < g_points.size(); p++)
		for (int k = 0; k < K; k++)
			if (k != shaping[p])
				neighbourhood.push_back(pair<int, int>{p, k});
}


//Local search algorithm
int BL::localSearch(vector<Cluster>& clusters, vector<int>& shaping, int seed, int maxIter) {
	vector<pair<int, int>> neighbourhood;
	generateNeighbourhood(neighbourhood, shaping);

	vector<int> index;
	initializeUniformInt(index, 0, neighbourhood.size());

	int iters = 0;

	int point, newCluster, currentCluster;
	float currentFitness = calculateFitness(clusters, shaping);
	float newFitness, generalDeviation;
	float currentIfs = calculateShapingInfeasibility(shaping), newIfs;
	float currentPointIfs, newPointIfs;
	bool bestNeightbourFound = false, betterNeighbourFound = false;


	while (iters < maxIter && !bestNeightbourFound) {
		shuffle(index.begin(), index.end(), std::default_random_engine(seed + iters));
		betterNeighbourFound = false;

		for (int i = 0; i < index.size(); i++) {
			if (iters == maxIter)
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

				newFitness = generalDeviation + (newIfs * lambda);

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
		if (!betterNeighbourFound)
			bestNeightbourFound = true;
	}

	return iters;
}


void BL::initializeClusters(vector<Cluster>& clusters, vector<int>& shaping) {

	bool repeat = true;
	while (repeat) {
		//-----Asociate each point to a random Cluster-----
		for (int p = 0; p < g_points.size(); p++)
			shaping[p] = Randint(0, K - 1);

		//-----Checking that all clusters are associated with at least one point-----
		if (checkShaping(shaping)) {
			repeat = false;
		}
	}

	//-----Initializing clusters-----
	vector<float> centroid(dimension, 0);
	for (int i = 0; i < K; i++)
		clusters.push_back(Cluster(centroid, i));

	//-----Adding points to clusters-----
	for (int p = 0; p < g_points.size(); p++)
		clusters[shaping[p]].addPoint(p);

	//-----Recalculating the center of each cluster-----
	for (int i = 0; i < K; i++)
		clusters[i].calculateClusterCentroid((new PAR)->g_points);

	cout << "Clusters initialized = " << clusters.size() << endl << endl;
}


//Local Search Algorithm
vector<float> BL::execute() {
	ExecutionParameters ep;
	auto begin = std::chrono::high_resolution_clock::now();

	int iters;
	Set_random(ep.seed);
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size());
	initializeClusters(clusters, shaping);

	iters = localSearch(clusters, shaping, ep.seed, ep.iters);

	auto end = std::chrono::high_resolution_clock::now();
	printSolution(clusters, shaping);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	//cout << "Numero de iteraciones: " << iters << endl;

	//toBoxplot(clusters);

	return createOutput(clusters, shaping, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}