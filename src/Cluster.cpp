#include "Cluster.h"

using namespace std;


Cluster::Cluster(vector<float> centroid, int clusterId) {
	this->clusterId = clusterId;

	for (int i = 0; i < centroid.size(); i++)
		this->centroid.push_back(centroid[i]);
}


void Cluster::addPoint(int pointId) {
	set<int>::iterator it = clusterPoints.find(pointId);
	if (it == clusterPoints.end())
		clusterPoints.insert(pointId);

	else
		cout << "Beware: Inserctions" << endl;
}

void Cluster::removePoint(int pointId) {
	set<int>::iterator it = clusterPoints.find(pointId);
	if (it == clusterPoints.end())
		cout << "Beware: Removals" << endl;

	else if (getClusterSize() > 1)
		clusterPoints.erase(it);

	else
		cout << "Beware: Can't remove point " << pointId << "from cluster " << clusterId << "otherwise cluster would be empty" << endl;
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


void Cluster::calculateClusterCentroid(const vector<vector<float>>& g_points) {
	int dimension = g_points[0].size();

	for (int c = 0; c < dimension; c++) {
		float sum = 0.0;
		for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++)
			sum += g_points[*it][c];

		setCentroidByPos(c, sum / getClusterSize());
	}
}


float Cluster::calculateIntraClusterMeanDeviation(const vector<vector<float>>& g_points) const {
	float meanDeviation = 0;
	for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++)
		meanDeviation += calculateDistance(g_points[*it], getCentroid());

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
	for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++) {
		cout << *it << " ";
	}
	cout << endl << endl;
}