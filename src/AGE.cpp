#include "AGE.h"

using namespace std;


AGE::AGE() : GeneticAlgorithm()
{
	numberOfCrosses = 1;
	mutationProbability = 0.1;
	numberOfParents = 2;

	generatePopulation();
}


//Generates the initial population
void AGE::generatePopulation()
{
	for (int i = 0; i < populationSize; i++) {
		pair<vector<int>, float > cromosome(make_pair(vector<int>(pointsSize), 0));
		initializeCromosome(cromosome);
		ordered_push_back(population, cromosome);
	}
}

void AGE::ordered_push_back(vector<pair<vector<int>, float>> & thePopulation, const pair<vector<int>, float> & cromosome)
{
	auto pos = thePopulation.begin();
	for (; pos != thePopulation.end(); pos++)
		if (cromosome.second < (*pos).second)
			break;

	thePopulation.insert(pos, cromosome);
}


//Mutation based on probability
void AGE::applyMutations()
{
	uniform_real_distribution<double> random(0, 1);

	for (int i = 0; i < parentPopulation.size(); i++)
		if (random(rng) < mutationProbability)
			mutationOperator();
}


//Replacement operation: Substitute the two worst cromosomes in case they are improved by the parents
void AGE::applyPopulationReplacement()
{
	pair<int, float> bestCandidate, worstCandidate;
	pair<int, float> bestWorse, worseWorse;

	orderCandidates(bestCandidate, worstCandidate);
	getTwoWorse(worseWorse, bestWorse);

	if (bestCandidate.second < bestWorse.second) {
		population.erase(population.begin() + bestWorse.first);
		ordered_push_back(population, parentPopulation[bestCandidate.first]);

		if (worstCandidate.second < worseWorse.second) {
			population.erase(population.begin() + worseWorse.first);
			ordered_push_back(population, parentPopulation[worstCandidate.first]);
		}
	}

	else if (bestCandidate.second < worseWorse.second) {
		population.erase(population.begin() + worseWorse.first);
		ordered_push_back(population, parentPopulation[bestCandidate.first]);
	}
}


void AGE::orderCandidates(pair<int, float> & bestCandidate, pair<int, float> & worstCandidate)
{
	bestCandidate.first = 0;
	worstCandidate.first = 1;
	
	bestCandidate.second = (parentPopulation[bestCandidate.first]).second;
	worstCandidate.second = (parentPopulation[worstCandidate.first]).second;

	if (worstCandidate.second < bestCandidate.second) {
		auto aux = bestCandidate;
		bestCandidate = worstCandidate;
		worstCandidate = aux;
	}
}


//Get the two worst cromosomes in the current population
void AGE::getTwoWorse(pair<int, float> & worseWorse, pair<int, float> & bestWorse)
{
	worseWorse.first = population.size() - 1;
	bestWorse.first = worseWorse.first - 1;

	worseWorse.second = (population[worseWorse.first]).second;
	bestWorse.second = (population[bestWorse.first]).second;

	/*bestWorse.second = worseWorse.second = FLT_MIN;

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
	}*/
}