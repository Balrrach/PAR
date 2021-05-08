#include "AM-P.h"

using namespace std;


AMP::AMP() { pls = 0.1; }

void AMP::selectPopulationtoImprove()
{
	populationToImprove.clear();

	int numberToImprove = pls * populationSize;
	uniform_int_distribution<int> randomCromosome(0, populationSize - 1);

	for (int i = 0; i < numberToImprove; i++) {
		int cromosomePosition = randomCromosome(rng);
		populationToImprove.push_back(& population[cromosomePosition]);
		//cout << "Identificador: " << cromosomePosition << endl;
	}
}