#include "GeneticAlgorithm.h"

using namespace std;


GeneticAlgorithm::GeneticAlgorithm()
{	
	populationSize = 50;
	evaluationNumber = 0;

	generatePopulation();
}



//Generates the initial population
void GeneticAlgorithm::generatePopulation()
{
	bool repeat = true;

	for (int i = 0; i < populationSize; i++) {
		vector<int> cromosome(pointsSize);
		initializeCromosome(cromosome);
		population.push_back(cromosome);
	}
}

//Initializes a cromosone checking strong restrictions are acomplished
void GeneticAlgorithm::initializeCromosome(vector<int>& cromosome)
{
	while (checkShaping(cromosome) == false)
		for (auto & gen : cromosome)
			gen = Randint(0, K - 1);
}



//Genetic Algorithm execution
vector<float> GeneticAlgorithm::executeGeneticAlgoritm(int numberOfParents, int crossingOperator)
{
	auto begin = std::chrono::high_resolution_clock::now();

	//printPopulation();
	while (evaluationNumber < (new ExecutionParameters)->iters) {
		applySelection(numberOfParents);
		applyCrossing(crossingOperator);
		applyMutations();
		applyPopulationReplacement();
		//printf("Current best fitness %f completed \n", calculateShapingFitness(population[findCurrentBestCromosome()]));
	}

	auto end = std::chrono::high_resolution_clock::now();
	vector<int> solution = population[findCurrentBestCromosome()];
	printSolution(solution);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

	return createOutput(solution, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}



//Selection operation
void GeneticAlgorithm::applySelection(int numberOfParents)
{
	parentPopulation.clear();

	for (int i = 0; i < numberOfParents; i++) {
		int winner = selectionOperator();
		parentPopulation.push_back(population[winner]);
	}
}

//Selection Operator
int GeneticAlgorithm::selectionOperator()
{
	int first, second, winner;
	getRandomCromosomes(first, second);
	winner = binaryTournament(first, second);

	return winner;
}

//Provides two different cromosomes
void GeneticAlgorithm::getRandomCromosomes(int& first, int& second)
{
	first = Randint(0, populationSize - 1);
	second = Randint(0, populationSize - 1);
	while(first == second)
		second = Randint(0, populationSize - 1);
}

//Implements Binary Tournament
int GeneticAlgorithm::binaryTournament(int first, int second)
{
	float firstScore = calculateShapingFitness(population[first]);
	float secondScore = calculateShapingFitness(population[second]);

	if (firstScore < secondScore)
		return first;

	else
		return second;
}

//Makes sure a cromosome isn't repeated in the parents population
void GeneticAlgorithm::addParent(vector<int> parentsNumbers, int winner)
{
	if (find(parentsNumbers.begin(), parentsNumbers.end(), winner) == parentsNumbers.end())
		parentPopulation.push_back(population[winner]);
}



//Crossing operation
void GeneticAlgorithm::applyCrossing(int crossingOperator)
{	
	intermediatePopulation.clear();

	if (crossingOperator == 0)
		generateIntermediatePopulation(& GeneticAlgorithm::uniformCrossingOperator);

	else
		generateIntermediatePopulation(& GeneticAlgorithm::fixedSegmentCrossingOperator);
}


void GeneticAlgorithm::generateIntermediatePopulation(void (GeneticAlgorithm::*function)(int, vector<int> &))
{
	vector<int> index(pointsSize);
	initializeUniformInt(index, 0, pointsSize);

	for (int i = 0; i < numberOfCrosses; i += 1)
		//2i because the crossinf operator needs two cromosomes to make a cross
		(this->*function)(2*i, index);

	//Add parents until intermediate population is complete
	for (int i = intermediatePopulation.size(); i < parentPopulation.size(); i++)
		intermediatePopulation.push_back(parentPopulation[i]);
}


void GeneticAlgorithm::uniformCrossingOperator(int firstParent, vector<int> & index)
{
	int secondParent = firstParent + 1;
	vector<int> newDescendant(pointsSize);

	//Repeat twice to obtain two descendants from two cromosomes
	for (int t = 0; t < 2; t++) {
		shuffle(index.begin(), index.end(), std::default_random_engine(Rand()));

		for (int i = 0; i < pointsSize / 2; i++)
			newDescendant[i] = population[firstParent][index[i]];

		for (int i = pointsSize / 2; i < pointsSize; i++)
			newDescendant[i] = population[secondParent][index[i]];

		fixShaping(newDescendant);
		intermediatePopulation.push_back(newDescendant);
	}
}


void GeneticAlgorithm::fixedSegmentCrossingOperator(int firstParent, vector<int> & index)
{
	//Se puede jugar con la selección del padre a desarrollar/heredar
	vector<int> newDescendant(pointsSize);
	int secondParent = firstParent + 1;
	int r = Randint(0, pointsSize - 1), v = Randint(0, pointsSize);
	
	//Alwais develop the best parent
	adjustParents(firstParent, secondParent);

	for (int t = 0; t < 2; t++) {
		initializeFirstSegment(r, v, firstParent, newDescendant);
		initializeSecondSegment(r, v, firstParent, secondParent, newDescendant);

		fixShaping(newDescendant);
		intermediatePopulation.push_back(newDescendant);
	}
}

//Initializes the first part of the new cromosome
void GeneticAlgorithm::initializeFirstSegment(int r, int v, int firstParent, vector<int> & newDescendant)
{
	for (int i = r; i < v; i++)
		newDescendant[i % pointsSize] = population[firstParent][i % pointsSize];
}

//Initializes the second part of the new cromosome
void GeneticAlgorithm::initializeSecondSegment(int r, int v, int firstParent, int secondParent, vector<int> & newDescendant)
{
	vector<int> randomVector(pointsSize - v);
	fillWithRandom(randomVector, 2);

	int j = -1;
	for (int i = v; i < pointsSize; i++) {
		j++;
		if (randomVector[j] == 0)
			newDescendant[i % pointsSize] = population[firstParent][i % pointsSize];
		else
			newDescendant[i % pointsSize] = population[secondParent][i % pointsSize];
	}
}

//Ensures fisrtParent is the best parent
void GeneticAlgorithm::adjustParents(int & firstParent, int & secondParent)
{
	if (secondParent == binaryTournament(firstParent, secondParent)) {
		secondParent = firstParent;
		firstParent += 1;
	}
}



//Implemented in the inheritant class
void GeneticAlgorithm::applyMutations() {}

//Mutation operation
void GeneticAlgorithm::mutationOperator(int cromosome, int gen)
{
	intermediatePopulation[cromosome][gen] = Randint(0, K - 1);
	fixShaping(intermediatePopulation[cromosome]);
}



//Implemented in the inheritant class
void GeneticAlgorithm::applyPopulationReplacement(){}



void GeneticAlgorithm::calculatePopulationFitness(vector<float> & fitnessVector)
{
	for (int i = 0; i < intermediatePopulation.size(); i++)
		fitnessVector[i] = calculateShapingFitness(intermediatePopulation[i]);
}


int GeneticAlgorithm::findCurrentBestCromosome()
{
	int bestCromosome = -1;
	float lowestFitness = FLT_MAX, newFitness;

	for (int i = 0; i < populationSize; i++) {
		newFitness = calculateShapingFitness(population[i]);

		if (newFitness < lowestFitness) {
			bestCromosome = i;
			lowestFitness = newFitness;
		}
	}

	return bestCromosome;
}


int GeneticAlgorithm::findCurrenIntermediateWorstCromosome()
{
	int worstCromosome = -1;
	float highiestFitness = FLT_MIN, newFitness;

	for (int i = 0; i < intermediatePopulation.size(); i++) {
		newFitness = calculateShapingFitness(intermediatePopulation[i]);

		if (highiestFitness < newFitness) {
			worstCromosome = i;
			highiestFitness = newFitness;
		}
	}

	return worstCromosome;
}


//Adds one to the number of evaluations
float GeneticAlgorithm::calculateShapingFitness(const std::vector<int> & shaping)
{
	evaluationNumber++;
	return PAR::calculateShapingFitness(shaping);
}



//Prints every cromosome values
void GeneticAlgorithm::printPopulation()
{
	cout << endl << "POPULATION: " << endl;
	for (auto cromosone : population)
		printShaping(cromosone);
}
