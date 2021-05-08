#pragma once

#include <vector>

#include "COPKM.h"
#include "AGESF.h"
#include "Cluster.h"


class AM : public AGESF
{
protected:
	int cicleLength;
	int allowedFailures;
	std::vector<std::pair<std::vector<int>, float> * > populationToImprove;
	std::vector<int> index;

	AM();

	virtual void selectPopulationtoImprove() = 0;

	void modifiedBL(std::pair<std::vector<int>, float> & cromosome);
	bool changePointToBestCluster(int p, std::pair<std::vector<int>, float> & cromosome);
	
	void printPopulationToImprove();

public:
	std::vector<float> execute();
};