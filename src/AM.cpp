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

	while (evaluationsCounter < maxIters) {
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
	cout << "Evaluaciones: " << evaluationsCounter << endl;
	cout << "Mutaciones: " << mutationsCounter << endl;
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

bool AM::changePointToBestCluster(int p, pair<vector<int>, float> & cromosome)
{

	vector<int> & shaping = cromosome.first;
	int originalCluster = shaping[p];
	bool wasChanged;

	pair<int, float> bestClusterAndFitness = getBestClusterAndFitness(p, shaping);
	shaping[p] = bestClusterAndFitness.first;
	cromosome.second = bestClusterAndFitness.second;

	if (originalCluster == bestClusterAndFitness.first)
		wasChanged = false;

	else
		wasChanged = true;

	return wasChanged;
}

pair<int, float> AM::getBestClusterAndFitness(int p, vector<int> & shaping)
{
	int originalCluster = shaping[p];

	vector<Cluster> clusters;
	fromShappingToClusters(shaping, clusters);

	float fitness = -1;
	pair<int, float> bestClusterAndFitness(-1, FLT_MAX);
	for (int i = 0; i < K; i++) {
		forceTransferPoint(p, shaping[p], i, clusters);
		shaping[p] = i;

		fitness = calculateFitness(shaping, clusters);
		if (fitness < bestClusterAndFitness.second) {
			bestClusterAndFitness.first = i;
			bestClusterAndFitness.second = fitness;
		}
	}

	shaping[p] = originalCluster;

	return bestClusterAndFitness;
}


void AM::printPopulationToImprove()
{
	cout << endl;
	for (const auto & cromosome : populationToImprove){
		printShaping(cromosome->first);
		cout << "Fitness: " << cromosome->second << endl;
	}

}