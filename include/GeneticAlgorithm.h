#pragma once

#include <vector>

#include "ExecutionParameters.h"
#include "PAR.h"


class GeneticAlgorithm : public PAR {

public:
	GeneticAlgorithm();

protected:
	int populationSize;
	std::vector<std::vector<int>> population;
	float crossingProbability;
	float muationProbability;

	void generatePopulation();
	void selectionOperator();
	virtual void crossingOperator();
	void mutationOperator();
};