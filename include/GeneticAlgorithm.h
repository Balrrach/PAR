#pragma once

#include <cfloat>
#include <vector>

#include "ExecutionParameters.h"
#include "PAR.h"


class GeneticAlgorithm : virtual public PAR
{
protected:
	int populationSize;
	std::vector<std::pair<std::vector<int>, float>> population;
	
	int numberOfParents;
	std::vector<std::pair<std::vector<int>, float>> parentPopulation;

	int numberOfCrosses;
	int crossingOperator;
	
	float mutationProbability;

	int evaluationsCounter;
	int mutationsCounter;


	//Initialization
	GeneticAlgorithm();
	virtual void generatePopulation() = 0;
	void initializeCromosome(std::pair<std::vector<int>, float> & cromosome);


	//Algorithm execution
	std::vector<float> executeGeneticAlgoritm();


	//Selection
	void applySelection();
	int selectionOperator();
	void getRandomCromosomes(int& first, int& second);
	int binaryTournament(int first, int second);
	void addParent(std::vector<int> parentsNumbers, int winner);


	//Crossing
	void applyCrossing();
	void crossParents(void (GeneticAlgorithm:: * crossingOperator)(int, std::vector<int> &));
	void uniformCrossingOperator(int firstParent, std::vector<int> & index);
	void fixedSegmentCrossingOperator(int firstParent, std::vector<int> & index);
	void initializeFirstSegment(int r, int v, int firstParent, std::vector<int> & newDescendant);
	void initializeSecondSegment(int r, int v, int firstParent, int secondParent, std::vector<int> & newDescendant);
	void adjustParents(int & firstParent, int & secondParent);
	

	//Mutations
	virtual void applyMutations() = 0;
	void mutationOperator();


	//Replacements
	virtual void applyPopulationReplacement() = 0;
	

	//Evaluation
	void fixAndEvaluateParentPopulation();


	//Others
	virtual void geneticCore(int iters);
	int findCurrentBestCromosome();
	int findCurrenWorstParent();
	float calculateShapingFitness(const std::vector<int> & shaping);
	void orderPopulation(std::vector<std::pair<std::vector<int>, float>> & thePopulation);
	static bool sortingFunction(const std::pair<std::vector<int>, float > & i, const std::pair<std::vector<int>, float > & j);
	void checkPopulation();
	float calculateFitness(const std::vector<int> & shaping, const std::vector<Cluster> & clusters);

	//Printers
	void printPopulation(const std::vector<std::pair<std::vector<int>, float>> & thePopulation);
	void printMeanPopulationFitness(const std::vector<std::pair<std::vector<int>, float>> & thePopulation);
};