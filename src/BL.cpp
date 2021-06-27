#include "BL.h"

using namespace std;


BL::BL() : BLMaxIters(maxIters)
{}



void BL::initializeIfs(const vector<int> & shaping)
{
	BLCurrentIfs = calculateShapingInfeasibility(shaping);
}

void BL::updateIfs(int newIfs)
{
	BLCurrentIfs = newIfs;
}


//Prev: CALL initializeIfs(...)
float BL::exploreNeighbour(vector<Cluster> & clusters, vector<int> & shaping, int & point, int & newCluster, int & newIfs)
{
	evaluationsCounter++;

	int oldCluster;
	float newFitness;

	do {
		point = randomPoint(rng);
		newCluster = randomCluster(rng);
		oldCluster = shaping[point];
	} while (oldCluster == newCluster || clusters[oldCluster].getClusterSize() == 1);

	newIfs = calculateNewFitness(clusters, shaping, point, newCluster, oldCluster, newFitness);
	
	return newFitness;
}


int BL::calculateNewFitness(vector<Cluster> & clusters, vector<int> & shaping, int point, int newCluster, int oldCluster, float & newFitness)
{
	int currentIncrementIfs, newIncrementIfs;
	currentIncrementIfs = calculateIncrementInfeseability(point, oldCluster, shaping);
	newIncrementIfs = calculateIncrementInfeseability(point, newCluster, shaping);
	int newIfs = BLCurrentIfs + newIncrementIfs - currentIncrementIfs;

	assignPointToCluster(point, newCluster, shaping, clusters);
	float newGeneralDeviation;
	newGeneralDeviation = calculateGeneralDeviation(clusters);
	assignPointToCluster(point, oldCluster, shaping, clusters);
	
	newFitness = newGeneralDeviation + (lambda * newIfs);

	return newIfs;
}


//Assigns a point to a cluster removing it from its current cluster and updating centroids
void BL::assignPointToCluster(int point, int newCluster, vector<int>& shaping, vector<Cluster>& clusters)
{
	int currentCluster = shaping[point];
	shaping[point] = newCluster;
	clusters[currentCluster].removePoint(point);
	clusters[newCluster].addPoint(point);
	clusters[currentCluster].calculateClusterCentroid();
	clusters[newCluster].calculateClusterCentroid();
}


void BL::initializeNeighbourhood(const vector<int>& shaping)
{
	for (int p = 0; p < pointsSize; p++)
		for (int k = 0; k < K; k++)
			if (k != shaping[p])
				neighbourhood.push_back(pair<int, int>{p, k});

	randomNeighbour = uniform_int_distribution<int>(0, neighbourhood.size() - 1);
}


//Local search algorithm
int BL::localSearch(vector<Cluster>& clusters, vector<int>& shaping)
{
	initializeNeighbourhood(shaping);
	initializeUniformInt(index, 0, neighbourhood.size());

	int iters = 0;

	int point, newCluster, currentCluster;
	float currentFitness = calculateFitness(clusters, shaping);
	float newFitness, generalDeviation;
	float currentIfs = calculateShapingInfeasibility(shaping), newIfs;
	float currentPointIfs, newPointIfs;
	bool bestNeightbourFound = false, betterNeighbourFound = false;


	while (iters < BLMaxIters && !bestNeightbourFound) {
		shuffle(index.begin(), index.end(), rng);
		betterNeighbourFound = false;

		for (int i = 0; i < index.size(); i++) {
			if (iters == BLMaxIters)
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


//Local Search Algorithm
vector<float> BL::execute()
{
	ExecutionParameters ep;
	auto begin = std::chrono::high_resolution_clock::now();

	int iters;
	Set_random(ep.seed);
	vector<Cluster> clusters;
	vector<int> shaping;
	initializeRandomSolution(clusters, shaping);

	iters = localSearch(clusters, shaping);

	auto end = std::chrono::high_resolution_clock::now();
	printSolution(clusters, shaping);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	cout << "Numero de iteraciones realizadas: " << iters << endl;

	//toBoxplot(clusters);

	return createOutput(clusters, shaping, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}



float BL::BLCore(std::vector<Cluster> & clusters, std::vector<int> & shaping)
{
	localSearch(clusters, shaping);
	return calculateFitness(clusters, shaping);
}
