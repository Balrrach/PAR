#include "ILS.h"

using namespace std;


ILS::ILS(): NCandidates(9)
{
	maxIters = 10000;
}


vector<float> ILS::execute()
{
	auto begin = std::chrono::high_resolution_clock::now();

	vector<int> currentShaping, bestShaping;
	vector<Cluster> currentClusters, bestClusters;
	float bestFitness = FLT_MAX, currentFitness;

	initializeRandomSolution(currentClusters, currentShaping);
	bestFitness = BLCore(currentClusters, currentShaping);
	bestClusters = currentClusters;
	bestShaping = currentShaping;

	for (int i = 0; i < NCandidates; i++) {
		fixedSegmentMutationOperator(currentClusters, currentShaping);
		currentFitness = optimumSearcher(currentClusters, currentShaping);

		if (currentFitness < bestFitness) {
			bestShaping = currentShaping;
			bestClusters = currentClusters;

			bestFitness = currentFitness;
		}

		//Parto del mejor o del actual???
		/*currentShaping = bestShaping;
		currentClusters = bestClusters;

		currentFitness = bestFitness;*/
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	printSolution(bestClusters, bestShaping);
	std::cout << "Tiempo de ejecucion: " << time << endl;

	return createOutput(bestClusters, bestShaping, time);
}



void ILS::fixedSegmentMutationOperator(std::vector<Cluster> & clusters, std::vector<int> & shaping)
{
	uniform_int_distribution<int> randomCluster(0, K - 1);
	uniform_int_distribution<int> randomPoint(0, pointsSize - 1);
	int r = randomPoint(rng), v = randomPoint(rng);
	int end = (v - r) % pointsSize;

	int j = r;
	for (int i = 0; i <= end; i++) {
		shaping[j] = randomCluster(rng);

		j = (j + 1) % pointsSize;
	}

	fixShaping(shaping);
	fromShappingToClusters(shaping, clusters);
}



float ILS::optimumSearcher(std::vector<Cluster> & clusters, std::vector<int> & shaping)
{
	return BLCore(clusters, shaping);
}


