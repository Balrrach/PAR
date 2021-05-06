#include "GeneticAlgorithm.h"

using namespace std;


GeneticAlgorithm::GeneticAlgorithm()
{	
	populationSize = 50;
	evaluationNumber = 0;
	mutationsNumber = 0;

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
	uniform_int_distribution<int> randomInt(0, K-1);
	while (checkShaping(cromosome) == false)
		for (auto & gen : cromosome)
			gen = randomInt(rng);
	//printShaping(cromosome);
}



//Genetic Algorithm execution
vector<float> GeneticAlgorithm::executeGeneticAlgoritm(int numberOfParents, int crossingOperator)
{
	auto begin = std::chrono::high_resolution_clock::now();
	int totalIterations = 0;

	//printPopulation();
	while (evaluationNumber < (new ExecutionParameters)->iters) {
		//cout << endl << "---------------------" << endl;
		//printPopulation(population);
		//printMeanPopulationFitness(population);
		applySelection(numberOfParents);
		//printMeanPopulationFitness(parentPopulation);
		applyCrossing(crossingOperator);
		applyMutations();
		//printMeanPopulationFitness(intermediatePopulation);
		//printPopulation(population);
		applyPopulationReplacement();
		//printPopulation(population);
		//printf("Current best fitness %f \n", calculateShapingFitness(population[findCurrentBestCromosome()]));
		//printMeanPopulationFitness(population);
		totalIterations++;
	}

	auto end = std::chrono::high_resolution_clock::now();
	vector<int> solution = population[findCurrentBestCromosome()];
	printSolution(solution);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	cout << "Iteraciones bucle principal: " << totalIterations << endl;
	cout << "Evaluaciones: " << evaluationNumber << endl;
	cout << "Mutaciones: " << mutationsNumber << endl;
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
	uniform_int_distribution<int> randomInt(0, populationSize - 1);
	first = randomInt(rng);
	second = randomInt(rng);
	while(first == second)
		second = randomInt(rng);
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
		crossParents(& GeneticAlgorithm::uniformCrossingOperator);

	else
		crossParents(& GeneticAlgorithm::fixedSegmentCrossingOperator);
}


void GeneticAlgorithm::crossParents(void (GeneticAlgorithm::*crossingOperator)(int, vector<int> &))
{
	vector<int> index(pointsSize);
	initializeUniformInt(index, 0, pointsSize);

	//Apply the expected number of crosses
	for (int i = 0; i < numberOfCrosses; i += 1)
		//2i because the crossing two cromosomes are needed to make a cross
		(this->*crossingOperator)(2*i, index);

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
		shuffle(index.begin(), index.end(), rng);

		for (int i = 0; i < pointsSize / 2; i++)
			newDescendant[index[i]] = parentPopulation[firstParent][index[i]];

		for (int i = pointsSize / 2; i < pointsSize; i++)
			newDescendant[index[i]] = parentPopulation[secondParent][index[i]];

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
		newDescendant[i % pointsSize] = parentPopulation[firstParent][i % pointsSize];
}

//Initializes the second part of the new cromosome
void GeneticAlgorithm::initializeSecondSegment(int r, int v, int firstParent, int secondParent, vector<int> & newDescendant)
{
	int remainigVector = pointsSize - (v - r);
	vector<int> randomVector(remainigVector);
	fillWithRandom(randomVector, 2);

	int j = v;
	for (int i = 0; i < remainigVector; i++) {
		if (randomVector[i] == 0)
			newDescendant[j % pointsSize] = parentPopulation[firstParent][j % pointsSize];
		else
			newDescendant[j % pointsSize] = parentPopulation[secondParent][j % pointsSize];

		j++;
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
void GeneticAlgorithm::mutationOperator()
{
	uniform_int_distribution<int> randomCromosome(0, intermediatePopulation.size() - 1);
	uniform_int_distribution<int> randomGen(0, pointsSize - 1);
	uniform_int_distribution<int> randomCluster(0, K - 1);
	int cromosome = randomCromosome(rng);
	int cluster = randomCluster(rng);

	bool repeat = true;
	while (repeat) {
		int gen = randomGen(rng);
		int currentCluster = intermediatePopulation[cromosome][gen];

		intermediatePopulation[cromosome][gen] = cluster;
		if (find(intermediatePopulation.begin(), intermediatePopulation.end(), currentCluster) != intermediatePopulation.end())
			repeat = false;
	}

	mutationsNumber++;
}



//Implemented in the inheritant class
void GeneticAlgorithm::applyPopulationReplacement(){}



void GeneticAlgorithm::calculatePopulationFitness(vector<float> & fitnessVector, const vector<vector<int>> & thePopulation)
{
	for (int i = 0; i < thePopulation.size(); i++)
		fitnessVector[i] = calculateShapingFitness(thePopulation[i]);
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
	//evaluationNumber++;
	return PAR::calculateShapingFitness(shaping);
}



//Prints every cromosome values
void GeneticAlgorithm::printPopulation(const std::vector<std::vector<int>> & thePopulation)
{
	cout << endl << "POPULATION: " << endl;
	for (const auto & cromosone : thePopulation)
		printShaping(cromosone);
}


void GeneticAlgorithm::printMeanPopulationFitness(const vector<vector<int>> & thePopulation)
{
	float meanFitness = 0;
	//printPopulation(thePopulation);
	vector<float> populationFitness(thePopulation.size());
	string type;
	if (thePopulation == population)
		type = "MAIN ";
	else if (thePopulation == parentPopulation)
		type = "PARENT ";
	else
		type = "INTERMEDIATE ";
	cout << endl << type << "POPULATION FITNESS: ";
	calculatePopulationFitness(populationFitness, thePopulation);

	for (const auto & i : populationFitness)
		meanFitness += i;

	cout << meanFitness / thePopulation.size() << endl;
}
