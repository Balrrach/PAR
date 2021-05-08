#include "AM.h"

using namespace std;


AM::AM() {
	cicleLength = 10;
	allowedFailures = 0.1 * populationSize;
	initializeUniformInt(index, 0, pointsSize);
}

vector<float> AM::execute()
{
	auto begin = std::chrono::high_resolution_clock::now();

	while (evaluationNumber < (new ExecutionParameters)->iters) {
		geneticCore(cicleLength);

		selectPopulationtoImprove();

		//printPopulation(population);
		//printPopulationToImprove();
		//printMeanPopulationFitness(population);

		for (auto & cromosome : populationToImprove) {
			//printShaping(cromosome->first);
			modifiedBL(*cromosome);
			//printShaping(cromosome->first);
		}

		orderPopulation(population);
		//printPopulationToImprove();
		//printPopulation(population);
		//printMeanPopulationFitness(population);

	}

	auto end = std::chrono::high_resolution_clock::now();
	vector<int> solution = population[findCurrentBestCromosome()].first;
	PAR::printSolution(solution);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	cout << "Evaluaciones: " << evaluationNumber << endl;
	cout << "Mutaciones: " << mutationsNumber << endl;
	return PAR::createOutput(solution, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}


void AM::modifiedBL(pair<vector<int>, float> & cromosome)
{
	int failures = 0, pos = 0;
	vector<int> & shaping = cromosome.first;
	shuffle(index.begin(), index.end(), rng);

	while (failures < allowedFailures & pos < shaping.size()) {
		int change = changePointToBestCluster(index[pos], cromosome);
		if (change == true)
			failures++;

		pos++;
	}

	fixShaping(cromosome.first);
}

bool AM::changePointToBestCluster(int p, std::pair<std::vector<int>, float> & cromosome){
	vector<Cluster> clusters;
	vector<int> & shaping = cromosome.first;
	bool wasChanged;

	fromShappingToClusters(shaping, clusters);
	int originalCluster = shaping[p], bestCluster = -1;
	float fitness = -1, bestFitness = FLT_MAX;

	for (int i = 0; i < K; i++) {
		forceTransferPoint(p, shaping[p], i, clusters);
		shaping[p] = i;
		
		fitness = calculateFitness(shaping, clusters);
		if (fitness < bestFitness) {
			bestCluster = i;
			bestFitness = fitness;
		}
	}

	shaping[p] = bestCluster;
	cromosome.second = bestFitness;

	if (originalCluster == bestCluster)
		wasChanged = false;

	else
		wasChanged = true;

	return wasChanged;
}


void AM::printPopulationToImprove()
{
	for (const auto & cromosome : populationToImprove){
		printShaping(cromosome->first);
		cout << "Fitness: " << cromosome->second << endl;
	}

}