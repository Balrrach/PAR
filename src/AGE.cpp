#include "AGE.h"

using namespace std;


AGE::AGE() : GeneticAlgorithm()
{
	numberOfCrosses = 1;
	mutationProbability = 0.1 / pointsSize;
}


//Mutation based on probability
void AGE::applyMutations()
{
	for (int i = 0; i < intermediatePopulation.size(); i++)
		for(int j = 0; j < pointsSize; j++)
		if (Rand() < mutationProbability)
			mutationOperator(i, j);
}



//Replacement operation: Substitute the two worst in case they are improved
void AGE::applyPopulationReplacement()
{
	pair<int, float> bestCandidate, worstCandidate;
	pair<int, float> bestWorse, worseWorse;

	orderCandidates(bestCandidate, worstCandidate);
	getTwoWorse(bestWorse, worseWorse);

	if (bestCandidate.second < bestWorse.second) {
		population[bestWorse.first] = intermediatePopulation[bestCandidate.first];

		if (worstCandidate.second < worseWorse.second)
		population[worseWorse.first] = intermediatePopulation[worstCandidate.first];
	}

	else if (bestCandidate.second < worseWorse.second)
		population[worseWorse.first] = intermediatePopulation[bestCandidate.first];
}


void AGE::orderCandidates(pair<int, float> & bestCandidate, pair<int, float> & worstCandidate)
{
	bestCandidate.first = 0;
	worstCandidate.first = 1;

	bestCandidate.second = calculateShapingFitness(intermediatePopulation[bestCandidate.first]);
	worstCandidate.second = calculateShapingFitness(intermediatePopulation[worstCandidate.first]);

	if (worstCandidate.second < bestCandidate.second) {
		pair<int, float> aux = bestCandidate;
		bestCandidate = worstCandidate;
		worstCandidate = aux;
	}
}


void AGE::getTwoWorse(pair<int, float> & bestWorse, pair<int, float> & worseWorse)
{
	vector<float> fitnessVector(intermediatePopulation.size());
	calculatePopulationFitness(fitnessVector);

	bestWorse.second = worseWorse.second = FLT_MAX;

	for (int i = 0; i < fitnessVector.size(); i++) {
		float currentFitness = fitnessVector[i];
		if (currentFitness < bestWorse.second) {
			bestWorse.first = i;
			bestWorse.second = currentFitness;
		}

		else if (currentFitness < worseWorse.second) {
			worseWorse.first = i;
			worseWorse.second = currentFitness;
		}
	}
}