#include "AGG.h"

using namespace std;


AGG::AGG() : GeneticAlgorithm()
{
	float crossingProbability = 0.7;
	mutationProbability = 0.1 / pointsSize;
	calculateNumberOfCrosses(crossingProbability);
	calculateNumberOfMutations();
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
	int currentBestCromosome = findCurrentBestCromosome(), currentIntermediateWorstCromosome;
	if (find(intermediatePopulation.begin(), intermediatePopulation.end(), population[currentBestCromosome]) == intermediatePopulation.end()) {
		currentIntermediateWorstCromosome = findCurrenIntermediateWorstCromosome();
		intermediatePopulation[currentIntermediateWorstCromosome] = population[currentBestCromosome];
	}

	population = intermediatePopulation;
}