#include "ES.h"

using namespace std;


ES::ES()
{
	maxNeighbours = 0.1 * pointsSize;
	maxSuccess = 0.1 * maxNeighbours;
	M = maxIters / maxNeighbours;
	mu = phi = 0.3;
	U = uniform_real_distribution<float>(0, 1);
}


vector<float> ES::execute()
{
	auto begin = std::chrono::high_resolution_clock::now();

	//-----------
	vector<int> bestShaping(pointsSize);
	vector<Cluster> bestClusters;

	initializeRandomSolution(bestClusters, bestShaping);
	ESCore(bestClusters, bestShaping);
	//-----------

	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	printSolution(bestClusters, bestShaping);
	std::cout << "Tiempo de ejecucion: " << time << endl;

	return createOutput(bestClusters, bestShaping, time);
}


float ES::ESCore(vector<Cluster> & bestClusters, vector<int> & bestShaping)
{
	vector<int> currentShaping = bestShaping;
	vector<Cluster> currentClusters = bestClusters;

	initializeIfs(currentShaping);
	float bestFitness = calculateFitness(currentClusters, currentShaping);

	initializeTemperatures(bestFitness);

	do {
		resetCounters();

		do {
			tryImproveSolution(bestClusters, bestShaping, bestFitness, currentClusters, currentShaping);
		
		} while (neighboursCounter < maxNeighbours && successCounter < maxSuccess);

		//printShaping(currentShaping);
		updateTemperature();

	} while (evaluationsCounter < maxIters );
	//&& successCounter != 0
	cout << "Numero de evaluaciones: " << evaluationsCounter << endl;
	return bestFitness;
}



void ES::initializeTemperatures(float initialFitness)
{
	initialTemperature = mu * initialFitness / -log(phi);
	currentTemperature = initialTemperature;
	endingTemperature = 0.001;

	if (initialTemperature < endingTemperature)
		throw "Initial Temperature is lower than Ending Temperature";
}

void ES::resetCounters()
{
	neighboursCounter = 0;
	successCounter = 0;
}


float ES::obtainLimit(float fitnessDifference)
{
	return 1 / exp(fitnessDifference / currentTemperature);
}


void ES::updateTemperature()
{
	float beta = calculateBeta();
	//currentTemperature = currentTemperature / (1 + (beta * currentTemperature));
	currentTemperature = 0.999*currentTemperature;
}


float ES::calculateBeta()
{
	return (initialTemperature - endingTemperature) / (M * initialTemperature * endingTemperature);
}


//void ES::tryImproveSolution
//	(vector<Cluster> & bestClusters, vector<int> & bestShaping, float & bestFitness, 
//	vector<Cluster> & currentClusters, vector<int> & currentShaping)
//{
//	neighboursCounter++;
//
//	int point, newCluster, newIfs;
//	float currentFitness = saveNeighbourFitness(currentClusters, currentShaping, point, newCluster, newIfs);
//	//cout << "Intente: " << point << endl;
//	//cout << "NewFitness: " << currentFitness << endl;
//
//	float fitnessDifference = currentFitness - bestFitness;
//	float a = U(rng), b = obtainLimit(fitnessDifference);
//
//	if (a < b) {
//		cout << "NewFitness: " << currentFitness << endl;
//
//		//Update vectors
//		assignPointToCluster(point, newCluster, currentShaping, currentClusters);
//		updateIfs(newIfs);
//
//		if (fitnessDifference < 0) {
//			assignPointToCluster(point, newCluster, bestShaping, bestClusters);
//			//cout << endl << "Punto: " << point << endl;
//
//			bestFitness = currentFitness;
//			successCounter++;
//		}
//	}
//
//	/*cout << "Diferencia de fitness: " << fitnessDifference << endl;
//	cout << "Current fitness: " << currentFitness << endl;
//	cout << "Best fitness: " << bestFitness << endl;
//	cout << "a: " << a << " b: " << b << endl << endl;*/
//}


void ES::tryImproveSolution
(vector<Cluster> & bestClusters, vector<int> & bestShaping, float & bestFitness,
	vector<Cluster> & currentClusters, vector<int> & currentShaping)
{
	neighboursCounter++;

	int point, newCluster, newIfs;
	float currentFitness = saveNeighbourFitness(currentClusters, currentShaping, point, newCluster, newIfs);
	//cout << "Tried point : " << point << " in cluster: " << newCluster << endl;
	//cout << "NewFitness: " << currentFitness << endl;

	float fitnessDifference = currentFitness - bestFitness;
	float a = U(rng), b = obtainLimit(fitnessDifference);

	if (currentFitness < bestFitness) {
		assignPointToCluster(point, newCluster, currentShaping, currentClusters);

		//cout << "New Fitness: " << currentFitness << endl;
		//cout << "New Ifs: " << newIfs << endl;
		updateIfs(newIfs);
		assignPointToCluster(point, newCluster, bestShaping, bestClusters);
		//cout << endl << "Punto: " << point << endl;

		bestFitness = currentFitness;
		successCounter++;
	}
	

	/*cout << "Diferencia de fitness: " << fitnessDifference << endl;
	cout << "Current fitness: " << currentFitness << endl;
	cout << "Best fitness: " << bestFitness << endl;
	cout << "a: " << a << " b: " << b << endl << endl;*/
}