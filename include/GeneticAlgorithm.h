#pragma once

#include <cfloat>
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
	int evaluationNumber;
	int mutationsNumber;

	//Initialization
	GeneticAlgorithm();
	void generatePopulation();
	void initializeCromosome(std::vector<int>& cromosone);


	//Algorithm execution
	std::vector<float> executeGeneticAlgoritm(int numberOfParents, int crossingOperator);


	//Selection
	void applySelection(int numberOfParents);
	int selectionOperator();
	void getRandomCromosomes(int& first, int& second);
	int binaryTournament(int first, int second);
	void addParent(std::vector<int> parentsNumbers, int winner);


	//Crossing
	virtual void applyCrossing(int crossingOperator);
	void crossParents(void (GeneticAlgorithm:: * crossingOperator)(int, std::vector<int> &));
	void uniformCrossingOperator(int firstParent, std::vector<int> & index);
	void fixedSegmentCrossingOperator(int firstParent, std::vector<int> & index);
	void initializeFirstSegment(int r, int v, int firstParent, std::vector<int> & newDescendant);
	void initializeSecondSegment(int r, int v, int firstParent, int secondParent, std::vector<int> & newDescendant);
	void adjustParents(int & firstParent, int & secondParent);
	

	//Mutations
	virtual void applyMutations();
	void mutationOperator();


	//Replacements
	virtual void applyPopulationReplacement();
	

	//Others
	void calculatePopulationFitness(std::vector<float> & fitnessVector, const std::vector<std::vector<int>> & thePopulation);
	int findCurrentBestCromosome();
	int findCurrenIntermediateWorstCromosome();
	float calculateShapingFitness(const std::vector<int> & shaping);


	//Printers
	void printPopulation(const std::vector<std::vector<int>> & thePopulation);
	void printMeanPopulationFitness(const std::vector<std::vector<int>> & thePopulation);
};