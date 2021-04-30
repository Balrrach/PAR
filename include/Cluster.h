#pragma once

#include <set>

#include "utilities.h"


class Cluster {

private:
	int clusterId;
	std::vector<float> centroid;
	std::set<int> clusterPoints;

public:
	//Constructor
	Cluster(std::vector<float> centroid, int clusterId);

	//Point related
	void addPoint(int pointId);
	void removePoint(int pointId);

	//Getters
	int getClusterId() const;
	int getClusterSize() const;
	std::vector<float> getCentroid() const;
	float getCentroidByPos(int pos) const;

	//Setters
	void setCentroidByPos(int pos, float val);
	
	//Others
	void calculateClusterCentroid(const std::vector<std::vector<float>>& g_points);

	//Calculates intra cluster mean deviation
	float calculateIntraClusterMeanDeviation(const std::vector<std::vector<float>>& g_points) const;

	//Printers
	void printClusterCentroid(const int dimension) const;
	void printClusterPoints() const;
};