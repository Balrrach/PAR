#pragma once

#include "GeneticAlgorithm.h"


class AGE : public GeneticAlgorithm
{
protected:
	AGE();

	void applyMutations();

	void applyPopulationReplacement();
	void orderCandidates(std::pair<int, float> & first, std::pair<int, float> & second);
	void getTwoWorse(std::pair<int, float> & firstWorse, std::pair<int, float> & secondWorse);
};