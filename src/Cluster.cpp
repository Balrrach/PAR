#include "Cluster.h"

using namespace std;


Cluster::Cluster(vector<float> centroid, int clusterId)
{
	this->clusterId = clusterId;
	this->centroid = centroid;
	clusterPoints.reserve(100);
}


void Cluster::addPoint(int pointId)
{
	if (find(clusterPoints.begin(), clusterPoints.end(), pointId) == clusterPoints.end())
		clusterPoints.push_back(pointId);

	else
		cout << "Beware: Inserctions" << endl;
}

void Cluster::removePoint(int pointId)
{
	auto it = find(clusterPoints.begin(), clusterPoints.end(), pointId);

	if (it == clusterPoints.end())
		cout << "Beware: Removals" << endl;

	else if (getClusterSize() > 1)
		clusterPoints.erase(it);

	else
		cout << "Beware: Can't remove point " << pointId << "from cluster " << clusterId << "otherwise cluster would be empty" << endl;
}

void Cluster::forceRemovePoint(int pointId)
{
	auto it = find(clusterPoints.begin(), clusterPoints.end(), pointId);

	if (it == clusterPoints.end())
		cout << "Beware: Removals" << endl;

	else
		clusterPoints.erase(it);
}

int Cluster::getClusterId() const {
	return clusterId;
}


/*
int getPoint(int pos) const {	//CUIDADO
	set<int>::iterator it = pos;
	return clusterPoints[it];
}
*/


int Cluster::getClusterSize() const {
	return clusterPoints.size();
}


float Cluster::getCentroidByPos(int pos) const {
	return centroid[pos];
}


vector<float> Cluster::getCentroid() const {
	return centroid;
}


void Cluster::setCentroidByPos(int pos, float val) {
	this->centroid[pos] = val;
}


void Cluster::calculateClusterCentroid() {
	int dimension = g_points[0].size();

	for (int c = 0; c < dimension; c++) {
		float sum = 0.0;
		for (auto it = clusterPoints.begin(); it != clusterPoints.end(); it++)
			sum += g_points[*it][c];

		setCentroidByPos(c, sum / getClusterSize());
	}
}


float Cluster::calculateIntraClusterMeanDeviation() const {
	float meanDeviation = 0;
	for (auto it = clusterPoints.begin(); it != clusterPoints.end(); it++)
		meanDeviation += calculateDistance(g_points[*it], centroid);

	return meanDeviation / getClusterSize();
}


void Cluster::printClusterCentroid(const int dimension) const {
	cout << "Cluster " << getClusterId() + 1 << ": " << endl << "Centroid: ";
	for (int i = 0; i < dimension; i++)
		cout << getCentroidByPos(i) << " ";
	cout << endl;
}

void Cluster::printClusterPoints() const {
	cout << "Points: ";
	for (auto it = clusterPoints.begin(); it != clusterPoints.end(); it++) {
		cout << *it << " ";
	}
	cout << endl << endl;
}


void Cluster::commitPoints(std::vector<int> & keeper) const
{
	for (auto i : clusterPoints)
		keeper.push_back(i);
}
