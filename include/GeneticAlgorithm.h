#pragma once

#include <vector>

#include "ExecutionParameters.h"
#include "PAR.h"


class GeneticAlgorithm : public PAR
{
protected:
	int populationSize;
	std::vector<std::vector<int>> population;
	std::vector<std::vector<int>> parentPopulation;
	std::vector<std::vector<int>> intermediatePopulation;
	int numberOfCrosses;
	float mutationProbability;


	//Initialization
	GeneticAlgorithm();
	void generatePopulation();
	void initializeCromosome(std::vector<int>& cromosone);


	//Algorithm execution
	std::vector<int> executeGeneticAlgoritm(int numberOfParents, int crossingOperator);


	//Selections
	void applySelection(int numberOfParents);
	int selectionOperator();
	void getRandomCromosomes(int& first, int& second);
	int binaryTournament(int first, int second);
	void addParent(std::vector<int> parentsNumbers, int winner);


	//Crossing
	virtual void applyCrossing(int crossingOperator);
	void generateIntermediatePopulation(void (GeneticAlgorithm:: * function)(int, std::vector<int> &));
	void uniformCrossingOperator(int firstParent, std::vector<int> & index);
	void fixedSegmentCrossingOperator(int firstParent, std::vector<int> & index);
	void initializeFirstSegment(int r, int v, int firstParent, std::vector<int> & newDescendant);
	void initializeSecondSegment(int r, int v, int firstParent, int secondParent, std::vector<int> & newDescendant);
	void adjustParents(int & firstParent, int & secondParent);


	//Mutations
	virtual void applyMutations();
	void mutationOperator(int cromosome, int gen);


	//Replacements
	virtual void applyPopulationReplacement();
	

	//Others
	void calculatePopulationFitness(std::vector<float> & fitnessVector);
	int findCurrentBestCromosome();
	int findCurrenIntermediateWorstCromosome();

	//Printers
	void printPopulation();
};