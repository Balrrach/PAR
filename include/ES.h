#pragma once

#include "BL.h"

class ES : public BL
{
public:
	ES();
	std::vector<float> execute();

protected:
	int ESMaxIters;
	int maxNeighbours;
	int neighboursCounter;
	int maxSuccess;
	int successCounter;
	int M;
	std::uniform_real_distribution<float> U;

	float initialTemperature;
	float currentTemperature;
	float endingTemperature;
	float mu;
	float phi;
	float beta;

	int Counter;

	float ESCore(std::vector<Cluster> & clusters, std::vector<int> & shaping);

	void initializeTemperatures(float bestFitness);
	void resetCounters();
	float obtainLimit(float fitnessDifference);
	void updateTemperature();
	float calculateBeta();
	void tryImproveSolution();

private:
	std::vector<Cluster> bestClusters;
	std::vector<int> bestShaping;
	float bestFitness;
	std::vector<Cluster> currentClusters;
	std::vector<int> currentShaping;
	float currentFitness;
};