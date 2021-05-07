#pragma once

#include "GeneticAlgorithm.h"


class AGE : public GeneticAlgorithm
{
protected:
	AGE();
	void generatePopulation();
	void ordered_push_back(std::vector<std::pair<std::vector<int>, float>> & thePopulation, const std::pair<std::vector<int>, float> & cromosome);

	void applyMutations();

	void applyPopulationReplacement();
	void orderCandidates(std::pair<int, float> & first,std::pair<int, float> & second);
	void getTwoWorse(std::pair<int, float> & firstWorse,std::pair<int, float> & secondWorse);
};