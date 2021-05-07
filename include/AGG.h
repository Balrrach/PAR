#pragma once

#include "GeneticAlgorithm.h"


class AGG : public GeneticAlgorithm
{
protected:
	int numberOfMutations;

	AGG();
	void generatePopulation();

	void calculateNumberOfCrosses(float crossingProbability);
	void calculateNumberOfMutations();

	void applyMutations();

	void applyPopulationReplacement();
};