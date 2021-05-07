#include "AGG.h"

using namespace std;


AGG::AGG() : GeneticAlgorithm()
{
	float crossingProbability = 0.7;
	mutationProbability = 0.1 / pointsSize;
	calculateNumberOfCrosses(crossingProbability);
	calculateNumberOfMutations();
	generatePopulation();
}


//Generates the initial population
void AGG::generatePopulation()
{
	for (int i = 0; i < populationSize; i++) {
		pair<vector<int>, float > cromosome(make_pair(vector<int>(pointsSize), 0));
		initializeCromosome(cromosome);
		population.push_back(cromosome);
	}
}



//Calculates the expected number of crosses
void AGG::calculateNumberOfCrosses(float crossingProbability)
{
	numberOfCrosses = crossingProbability * populationSize / 2;
}

//Calculates the expected number of mutations
void AGG::calculateNumberOfMutations()
{
	numberOfMutations = mutationProbability * pointsSize * populationSize;
}



//Mutation based on number of mutations expectancy
void AGG::applyMutations()
{
	for (int i = 0; i < numberOfMutations; i++)
		mutationOperator();
}


//Replacement operation: Only the best is kept
void AGG::applyPopulationReplacement()
{
	int currentBestCromosome = findCurrentBestCromosome(), currentWorstParent;
	if (find(parentPopulation.begin(), parentPopulation.end(), population[currentBestCromosome]) == parentPopulation.end()) {
		currentWorstParent = findCurrenWorstParent();
		parentPopulation[currentWorstParent] = population[currentBestCromosome];
	}

	population = parentPopulation;
}