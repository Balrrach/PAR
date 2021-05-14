#pragma once

#include <algorithm>
#include <set>

#include "utilities.h"
#include "ExecutionParameters.h"

class Cluster : public ExecutionParameters
{
private:
	int clusterId;
	std::vector<float> centroid;
	std::vector<int> clusterPoints;

public:
	//Constructor
	Cluster(std::vector<float> centroid, int clusterId);

	//Point related
	void addPoint(int pointId);
	void removePoint(int pointId);
	void forceRemovePoint(int pointId);

	//Getters
	int getClusterSize() const;
	float getCentroidByPos(int pos) const;
	
	//Others
	void calculateClusterCentroid();

	//Calculates intra cluster mean deviation
	float calculateIntraClusterMeanDeviation() const;

	//Printers
	void printClusterCentroid(const int dimension) const;
	void printClusterPoints() const;

	//Checker
	void commitPoints(std::vector<int> & keeper) const;
};