#include "AM.h"

using namespace std;


AM::AM()
{
	cicleLength = 10;
	allowedFailures = 0.1 * populationSize;
	initializeUniformInt(index, 0, pointsSize);
}

vector<float> AM::execute()
{
	auto begin = std::chrono::high_resolution_clock::now();
	int totalIterations = 0;

	while (evaluationsCounter < maxIters) {
		geneticCore(cicleLength);
		
		//cout << "Evaluaciones en core: " << evaluationsCounter << endl;

		selectPopulationtoImprove();

		//printPopulation(population);
		//printPopulationToImprove();
		//printMeanPopulationFitness(population);

		evalBL = 0;
		for (auto & cromosome : populationToImprove) {
			//printShaping(cromosome->first);
			softBL(*cromosome);
			//printShaping(cromosome->first);
		}

		//cout << "Evaluaciones en BL: " << evalBL << endl;
		//cout << "Evaluaciones totales: " << evaluationsCounter << endl << endl;

		orderPopulation(population);
		//printPopulationToImprove();
		//printPopulation(population);
		//printMeanPopulationFitness(population);

		totalIterations += 1;
	}

	auto end = std::chrono::high_resolution_clock::now();
	vector<int> solution = population[findCurrentBestCromosome()].first;
	PAR::printSolution(solution);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	cout << "Iteraciones bucle principal: " << totalIterations << endl;
	cout << "Evaluaciones: " << evaluationsCounter << endl;
	cout << "Mutaciones: " << mutationsCounter << endl;
	return PAR::createOutput(solution, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}


void AM::softBL(pair<vector<int>, float> & cromosome)
{
	vector<int> & shaping = cromosome.first;
	int failures = 0, pos = 0;
	bool mejora = true;

	pair<vector<int>, float> copy = cromosome;
	vector<Cluster> clusters;
	fromShappingToClusters(shaping, clusters);

	shuffle(index.begin(), index.end(), rng);
	while (failures < allowedFailures & pos < shaping.size()) {
		bool wasChanged = changePointToBestCluster(index[pos], cromosome, clusters);
		
		if (wasChanged == false)
			failures++;

		pos++;
	}

	//evalBL += pos*K;
	fixShaping(cromosome.first);
}

bool AM::changePointToBestCluster(int p, pair<vector<int>, float> & cromosome, vector<Cluster> & clusters)
{
	int originalCluster = cromosome.first[p];
	bool wasChanged;
	
	float bestFitness;
	int bestCluster = getBestClusterAndFitness(p, cromosome, clusters, bestFitness);
	cromosome.first[p] = bestCluster;
	cromosome.second = bestFitness;
	forceTransferPoint(p, originalCluster, bestCluster, clusters);

	if (originalCluster == bestCluster)
		wasChanged = false;

	else
		wasChanged = true;

	return wasChanged;
}

int AM::getBestCluster(int p, std::pair<std::vector<int>, float> & cromosome, vector<Cluster> & clusters)
{
	float fitness;
	return getBestClusterAndFitness(p, cromosome, clusters, fitness);
}


int AM::getBestClusterAndFitness(int p, pair<vector<int>, float> & cromosome, vector<Cluster> & clusters, float & bestFitness)
{
	vector<int> & shaping = cromosome.first;
	int originalCluster = shaping[p];
	float originalFitness = cromosome.second;

	int bestCluster;
	bestFitness = FLT_MAX;
	float fitness = -1;
	for (int i = 0; i < K; i++) {
		forceTransferPoint(p, shaping[p], i, clusters);
		shaping[p] = i;

		fitness = calculateFitness(shaping, clusters);
		if (fitness < bestFitness) {
			bestCluster = i;
			bestFitness = fitness;
		}
	}

	forceTransferPoint(p, K - 1, originalCluster, clusters);
	shaping[p] = originalCluster;

	return bestCluster;
}


void AM::printPopulationToImprove()
{
	cout << endl;
	for (const auto & cromosome : populationToImprove){
		printShaping(cromosome->first);
		cout << "Fitness: " << cromosome->second << endl;
	}

}


void AM::modifiedBL(pair<vector<int>, float> & cromosome)
{
	int failures = 0, pos = 0;
	vector<int> & shaping = cromosome.first;
	shuffle(index.begin(), index.end(), rng);

	while (failures < allowedFailures & pos < shaping.size()) {
		int change = changePointToBestCluster(index[pos], cromosome);
		if (change == false)
			failures++;

		pos++;
	}

	fixShaping(cromosome.first);
}

bool AM::changePointToBestCluster(int p, std::pair<std::vector<int>, float> & cromosome)
{
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