#include "AM-M.h"

using namespace std;


void AMM::selectPopulationtoImprove()
{
	populationToImprove.clear();
	orderPopulation(population);

	int numberToImprove = 0.1 * populationSize;

	//The population in AGE is already ordered by fitness
	for (int i = 0; i < numberToImprove; i++) {
		populationToImprove.push_back(& population[i]);
	}
}