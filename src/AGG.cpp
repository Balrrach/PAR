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
	int gen, cromosome;

	for (int i = 0; i < numberOfMutations; i++) {
		cromosome = Randint(0, intermediatePopulation.size()-1);
		gen = Randint(0, pointsSize-1);
		mutationOperator(cromosome, gen);
	}
}


//Replacement operation: Only the best is kept
void AGG::applyPopulationReplacement()
{
	int currentBestCromosome = findCurrentBestCromosome(), currentWorstCromosome;
	if (find(intermediatePopulation.begin(), intermediatePopulation.end(), population[currentBestCromosome]) == intermediatePopulation.end()) {
		currentWorstCromosome = findCurrenIntermediateWorstCromosome();
		intermediatePopulation[currentWorstCromosome] = population[currentBestCromosome];
	}

	population = intermediatePopulation;
}