#include "GeneticAlgorithm.h"

using namespace std;


GeneticAlgorithm::GeneticAlgorithm()
{
	populationSize = 50;
	evaluationNumber = 0;
	mutationsNumber = 0;
}

//Initializes a cromosone checking strong restrictions are acomplished
void GeneticAlgorithm::initializeCromosome(pair<vector<int>, float > & cromosome)
{
	uniform_int_distribution<int> randomInt(0, K-1);

	while (checkShaping(cromosome.first) == false)
		for (auto & gen : cromosome.first)
			gen = randomInt(rng);

	cromosome.second = PAR::calculateShapingFitness(cromosome.first);
}



//Genetic Algorithm execution
vector<float> GeneticAlgorithm::executeGeneticAlgoritm()
{
	auto begin = std::chrono::high_resolution_clock::now();
	int totalIterations = 0;

	//printPopulation();
	while (evaluationNumber < (new ExecutionParameters)->iters) {
		//cout << endl << "---------------------" << endl;
		//printPopulation(population);
		//printPopulation(parentPopulation);
		applySelection();
		//printPopulation(parentPopulation);
		applyCrossing();
		applyMutations();
		//printPopulation(parentPopulation);
		fixAndEvaluateParentPopulation();
		//printPopulation(parentPopulation);
		applyPopulationReplacement();
		//printMeanPopulationFitness(population);
		//printf("Current best fitness %f \n", population[findCurrentBestCromosome()].second);
		//printMeanPopulationFitness(population);
		totalIterations++;
	}

	auto end = std::chrono::high_resolution_clock::now();
	vector<int> solution = population[findCurrentBestCromosome()].first;
	printSolution(solution);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
	cout << "Iteraciones bucle principal: " << totalIterations << endl;
	cout << "Evaluaciones: " << evaluationNumber << endl;
	cout << "Mutaciones: " << mutationsNumber << endl;
	return createOutput(solution, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}



//Selection operation
void GeneticAlgorithm::applySelection()
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
	uniform_int_distribution<int> randomCromosome(0, populationSize - 1);
	first = randomCromosome(rng);
	second = randomCromosome(rng);
	while(first == second)
		second = randomCromosome(rng);
}

//Implements Binary Tournament
int GeneticAlgorithm::binaryTournament(int firstFighter, int secondFighter)
{
	float firstFighterScore = population[firstFighter].second;
	float secondFighterScore = population[secondFighter].second;

	if (firstFighterScore < secondFighterScore)
		return firstFighter;

	else
		return secondFighter;
}

//Makes sure a cromosome isn't repeated in the parents population
void GeneticAlgorithm::addParent(vector<int> parentsNumbers, int winner)
{
	if (find(parentsNumbers.begin(), parentsNumbers.end(), winner) == parentsNumbers.end())
		parentPopulation.push_back(population[winner]);
}



//Crossing operation
void GeneticAlgorithm::applyCrossing()
{
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
}


void GeneticAlgorithm::uniformCrossingOperator(int firstParent, vector<int> & index)
{
	int secondParent = firstParent + 1;
	vector<pair<vector<int>, float>> newDescendants(2, make_pair(vector<int>(pointsSize, -1), -1));

	//Repeat twice to obtain two descendants from two cromosomes
	for (int t = 0; t < 2; t++) {
		shuffle(index.begin(), index.end(), rng);
		int a = index[0];
		int b = (parentPopulation[firstParent].first)[index[0]];
		for (int i = 0; i < pointsSize / 2; i++)
			newDescendants[t].first[index[i]] = (parentPopulation[firstParent].first)[index[i]];

		for (int i = pointsSize / 2; i < pointsSize; i++)
			newDescendants[t].first[index[i]] = (parentPopulation[secondParent].first)[index[i]];
	}

	parentPopulation[firstParent] = newDescendants[0];
	parentPopulation[secondParent] = newDescendants[1];
}


void GeneticAlgorithm::fixedSegmentCrossingOperator(int firstParent, vector<int> & index)
{
	//Se puede jugar con la selección del padre a desarrollar/heredar
	vector<pair<vector<int>, float>> newDescendants(2, make_pair(vector<int>(pointsSize, -1), -1));
	int secondParent = firstParent + 1;
	
	//Alwais develop the best parent
	adjustParents(firstParent, secondParent);

	for (int t = 0; t < 2; t++) {
		int r = Randint(0, pointsSize - 1), v = Randint(0, pointsSize - 1);

		initializeFirstSegment(r, v, firstParent, newDescendants[t].first);
		//printShaping(newDescendants[t].first);
		initializeSecondSegment(r, v, firstParent, secondParent, newDescendants[t].first);
		//printShaping(newDescendants[t].first);
	}

	parentPopulation[firstParent] = newDescendants[0];
	parentPopulation[secondParent] = newDescendants[1];
}

//Initializes the first part of the new cromosome
void GeneticAlgorithm::initializeFirstSegment(int r, int v, int firstParent, vector<int> & newDescendant)
{
	int end = (pointsSize + (v - r)) % pointsSize;
	int j = r;
	for (int i = 0; i <= end; i++) {
		newDescendant[j] = parentPopulation[firstParent].first[j];

		j = (j + 1) % pointsSize;
	}
}

//Initializes the second part of the new cromosome
void GeneticAlgorithm::initializeSecondSegment(int r, int v, int firstParent, int secondParent, vector<int> & newDescendant)
{
	int remainigVector = (pointsSize - (v - r) - 1) % pointsSize;
	vector<int> randomVector(remainigVector);
	fillWithRandom(randomVector, 2);

	int j = (v+1)%pointsSize;
	for (int i = 0; i < remainigVector; i++) {
		if (randomVector[i] == 0)
			newDescendant[j] = parentPopulation[firstParent].first[j];
		else
			newDescendant[j] = parentPopulation[secondParent].first[j];

		j = (j+1) % pointsSize;
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




//Mutation operation
void GeneticAlgorithm::mutationOperator()
{
	uniform_int_distribution<int> randomCromosome(0, parentPopulation.size() - 1);
	uniform_int_distribution<int> randomGen(0, pointsSize - 1);
	uniform_int_distribution<int> randomCluster(0, K - 1);
	int cromosome = randomCromosome(rng);
	int cluster = randomCluster(rng);
	int gen = randomGen(rng);

	//bool repeat = true;
	//while (repeat) {
	//	int gen = randomGen(rng);
	//	//int currentCluster = parentPopulation[cromosome].first[gen];

	//	parentPopulation[cromosome].first[gen] = cluster;
	//	//if (find(parentPopulation[cromosome].first.begin(), parentPopulation[cromosome].first.end(), currentCluster) != parentPopulation[cromosome].first.end()) {
	//	//	parentPopulation[cromosome].first[gen] = currentCluster;
	//	//	repeat = false;
	//	//}
	//}
	parentPopulation[cromosome].first[gen] = cluster;
	parentPopulation[cromosome].second = -1;
	mutationsNumber++;
}



//Fix descendants and evaluate their fitness
void GeneticAlgorithm::fixAndEvaluateParentPopulation()
{
	for (auto & cromosome : parentPopulation)
		if (cromosome.second == -1) {
			fixShaping(cromosome.first);
			cromosome.second = calculateShapingFitness(cromosome.first);
		}
}



int GeneticAlgorithm::findCurrentBestCromosome()
{
	int bestCromosome = -1;
	float lowestFitness = FLT_MAX, fitness;

	for (int i = 0; i < populationSize; i++) {
		fitness = population[i].second;

		if (fitness < lowestFitness) {
			bestCromosome = i;
			lowestFitness = fitness;
		}
	}

	return bestCromosome;
}


int GeneticAlgorithm::findCurrenWorstParent()
{
	int worstCromosome = -1;
	float highiestFitness = FLT_MIN, fitness;

	for (int i = 0; i < parentPopulation.size(); i++) {
		fitness = parentPopulation[i].second;

		if (highiestFitness < fitness) {
			worstCromosome = i;
			highiestFitness = fitness;
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

//Adds one to the number of evaluations
float GeneticAlgorithm::calculateFitness(const vector<int> & shaping, const vector<Cluster> & clusters)
{
	evaluationNumber++;
	return PAR::calculateFitness(clusters, shaping);
}


void GeneticAlgorithm::orderPopulation(vector<pair<vector<int>, float>> & thePopulation)
{
	sort(thePopulation.begin(), thePopulation.end(), GeneticAlgorithm::sortingFunction);
}

bool GeneticAlgorithm::sortingFunction(const pair<vector<int>, float > & i, const pair<vector<int>, float > & j)
{
	return (i.second < j.second);
}

//Core of a genetic algorithm
void GeneticAlgorithm::geneticCore(int iters)
{
	for (int i = 0; i < iters; i++) {
		applySelection();
		applyCrossing();
		applyMutations();
		fixAndEvaluateParentPopulation();
		applyPopulationReplacement();
	}
}



//Prints every cromosome values
void GeneticAlgorithm::printPopulation(const std::vector<std::pair<std::vector<int>, float>> & thePopulation)
{
	string type;
	if (thePopulation == population)
		type = "MAIN ";
	else if (thePopulation == parentPopulation)
		type = "PARENT ";

	cout << endl << type << "POPULATION: " << endl;
	for (int i = 0; i < thePopulation.size(); i++) {
		printShaping(thePopulation[i].first);
		cout << "Fitness: " << thePopulation[i].second << ", identificador: " << i << endl;
	}
}


void GeneticAlgorithm::printMeanPopulationFitness(const vector<pair<vector<int>, float>> & thePopulation)
{
	float meanFitness = 0;
	string type;
	if (thePopulation == population)
		type = "MAIN ";
	else if (thePopulation == parentPopulation)
		type = "PARENT ";

	cout << endl << type << "POPULATION FITNESS: ";

	for (const auto & i : thePopulation)
		meanFitness += i.second;

	cout << meanFitness / thePopulation.size() << endl;
}