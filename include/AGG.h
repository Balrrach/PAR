#pragma once

#include "GeneticAlgorithm.h"


class AGG : public GeneticAlgorithm
{
protected:
	AGG();

	int numberOfMutations;

	virtual void calculateNumberOfCrosses(float crossingProbability);
	virtual void calculateNumberOfMutations();

	void applyMutations();

	void applyPopulationReplacement();
};