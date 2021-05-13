#include "BMB.h"

using namespace std;


BMB::BMB() : NCandidates(10)
{
	maxIters = 10000;
}


vector<float> BMB::execute()
{
	auto begin = std::chrono::high_resolution_clock::now();

	vector<int> currentShaping, bestShaping;
	vector<Cluster> currentClusters, bestClusters;
	float bestFitness = FLT_MAX , currentFitness;

	for (auto i = 0; i < NCandidates; i++) {
		initializeRandomSolution(currentClusters, currentShaping);
		currentFitness = BLCore(currentClusters, currentShaping);

		if (currentFitness < bestFitness) {
			bestShaping = currentShaping;
			bestClusters = currentClusters;

			bestFitness = currentFitness;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	printSolution(bestClusters, bestShaping);
	std::cout << "Tiempo de ejecucion: " << time << endl;

	return createOutput(bestClusters, bestShaping, time);
}