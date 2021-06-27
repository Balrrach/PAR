#include "ES.h"

using namespace std;


ES::ES() : ESMaxIters(maxIters)
{
	maxNeighbours = 10 * pointsSize;
	maxSuccess = pointsSize;
	mu = phi = 0.3;
	U = uniform_real_distribution<float>(0, 1);
}


vector<float> ES::execute()
{
	auto begin = std::chrono::high_resolution_clock::now();

	//-----------
	vector<int> shaping(pointsSize);
	vector<Cluster> clusters;

	initializeRandomSolution(clusters, shaping);
	ESCore(clusters, shaping);
	//-----------

	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	printSolution(bestClusters, bestShaping);
	std::cout << "Tiempo de ejecucion: " << time << endl;

	return createOutput(bestClusters, bestShaping, time);
}


float ES::ESCore(vector<Cluster> & givenClusters, vector<int> & givenShaping)
{
	int itersCounter = 0;

	currentClusters = givenClusters;
	currentShaping = givenShaping;
	currentFitness = calculateFitness(currentClusters, currentShaping);
	initializeIfs(currentShaping);
	initializeTemperatures(currentFitness);

	bestFitness = FLT_MAX;
	Counter = 0;

	do
	{
		resetCounters();

		do 
		{
			tryImproveSolution();
			itersCounter++;
		} while (neighboursCounter < maxNeighbours && successCounter < maxSuccess);

		updateTemperature();

	} while (itersCounter < ESMaxIters && successCounter != 0);

	givenClusters = bestClusters;
	givenShaping = bestShaping;

	return bestFitness;
}



void ES::initializeTemperatures(float initialFitness)
{
	M = ESMaxIters / maxNeighbours;
	initialTemperature = mu * initialFitness / -log(phi);
	currentTemperature = initialTemperature;
	endingTemperature = 0.001;
	beta = calculateBeta();

	if (initialTemperature < endingTemperature)
		throw "Initial Temperature is lower than Ending Temperature";
}

float ES::calculateBeta()
{
	return (initialTemperature - endingTemperature) / (M * initialTemperature * endingTemperature);
}


void ES::resetCounters()
{
	neighboursCounter = 0;
	successCounter = 0;
}


float ES::obtainLimit(float fitnessDifference)
{
	return 1 / exp(fitnessDifference / (currentTemperature));
}


void ES::updateTemperature()
{
	currentTemperature = currentTemperature / (1 + (beta * currentTemperature));
	//currentTemperature = 0.999*currentTemperature;
}



void ES::tryImproveSolution()
{
	neighboursCounter++;
	Counter++;

	int point, newCluster, newIfs;
	float neighbourFitness = exploreNeighbour(currentClusters, currentShaping, point, newCluster, newIfs);

	float fitnessDifference = neighbourFitness - currentFitness;
	float a = U(rng), b = obtainLimit(fitnessDifference);

	if (a < b || fitnessDifference < 0) {
		//El vecino se convierte en la solucion actual
		assignPointToCluster(point, newCluster, currentShaping, currentClusters);
		currentFitness = neighbourFitness;
		updateIfs(newIfs);
		successCounter++;
		
		if (currentFitness < bestFitness) {
			bestShaping = currentShaping;
			bestClusters = currentClusters;

			bestFitness = currentFitness;	
		}
	}
}