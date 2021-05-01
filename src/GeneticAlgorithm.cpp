#include "GeneticAlgorithm.h"

using namespace std;


GeneticAlgorithm::GeneticAlgorithm() {
	populationSize = 50;
	muationProbability = 0.1/dimension;

	generatePopulation();
}


void GeneticAlgorithm::generatePopulation() {}


void GeneticAlgorithm::selectionOperator() {}


void GeneticAlgorithm::crossingOperator() {}


void GeneticAlgorithm::mutationOperator() {}