#include "AGE.h"

using namespace std;


AGE::AGE() : GeneticAlgorithm()
{
	numberOfCrosses = 1;
	mutationProbability = 0.1;
}


//Mutation based on probability
void AGE::applyMutations()
{
	uniform_real_distribution<double> random(0, 1);

	for (int i = 0; i < intermediatePopulation.size(); i++)
		if (random(rng) < mutationProbability)
			mutationOperator();
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


//Get the two worst cromosomes in the current population
void AGE::getTwoWorse(pair<int, float> & bestWorse, pair<int, float> & worseWorse)
{
	vector<float> fitnessVector(populationSize);
	calculatePopulationFitness(fitnessVector, population);

	bestWorse.second = worseWorse.second = FLT_MIN;

	for (int i = 0; i < fitnessVector.size(); i++) {
		float currentFitness = fitnessVector[i];
		if (worseWorse.second < currentFitness) {
			bestWorse = worseWorse;

			worseWorse.first = i;
			worseWorse.second = currentFitness;
		}

		else if (bestWorse.second < currentFitness) {
			bestWorse.first = i;
			bestWorse.second = currentFitness;
		}
	}
}