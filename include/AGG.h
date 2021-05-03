#pragma once

#include "GeneticAlgorithm.h"


class AGG : public GeneticAlgorithm
{
protected:
	AGG();

	int numberOfCrosses;
	int numberOfMutations;

	virtual void calculateNumberOfCrosses(float crossingProbability);
	virtual void calculateNumberOfMutations(float mutationProbability);

	void applyMutations();

	void applyPopulationReplacement();
};