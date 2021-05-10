#pragma once

#include <vector>

#include "COPKM.h"
#include "AGGUN.h"
#include "Cluster.h"


class AM : public AGGUN
{
protected:
	int cicleLength;
	int allowedFailures;
	std::vector<std::pair<std::vector<int>, float> * > populationToImprove;
	std::vector<int> index;

	AM();

	virtual void selectPopulationtoImprove() = 0;

	void softBL(std::pair<std::vector<int>, float> & cromosome);
	bool changePointToBestCluster(int p, std::pair<std::vector<int>, float> & cromosome, std::vector<Cluster> & clusters);
	int getBestCluster(int p, std::pair<std::vector<int>, float> & cromosome, std::vector<Cluster> & clusters);
	int getBestClusterAndFitness(int p, std::pair<std::vector<int>, float> & cromosome, std::vector<Cluster> & clusters, float & fitness);

	void modifiedBL(std::pair<std::vector<int>, float> & cromosome);
	bool changePointToBestCluster(int p, std::pair<std::vector<int>, float> & cromosome);
	int evalBL;

	void printPopulationToImprove();

public:
	std::vector<float> execute();
};