#include "AM-C.h"

using namespace std;


void AMC::selectPopulationtoImprove()
{
	populationToImprove.clear();

	for (auto & cromosome : population)
		populationToImprove.push_back(& cromosome);
}