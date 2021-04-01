#pragma once

#include <set>

using namespace std;


float calculateDistance(const vector<float> & a, const vector<float> & b) {
	float sum = 0;
	for (int c = 0; c < dimension; c++) {
		sum += pow(a[c] - b[c], 2.0);
	}

	return sqrt(sum);
}


class Cluster {

private:
	int clusterId;
	vector<float> centroid;
	set<int> clusterPoints;
	static int nextId;

public:
	//Constructor
	Cluster(vector<float> centroid) {
		this->clusterId = nextId++;

		for (int i = 0; i < centroid.size(); i++) {
			this->centroid.push_back(centroid[i]);
		}
	}


	void addPoint(int pointId) {
		set<int>::iterator it = clusterPoints.find(pointId);
		if (it == clusterPoints.end())
			clusterPoints.insert(pointId);

		else
			cout << "Beware: Inserctions" << endl;
	}

	void removePoint(int pointId) {
		set<int>::iterator it = clusterPoints.find(pointId);
		if (it == clusterPoints.end())
			cout << "Beware: Removals" << endl;

		else if (getClusterSize() > 1)
			clusterPoints.erase(it);

		else
			cout << "Beware: Can't remove point " << pointId << "from cluster " << clusterId << "otherwise cluster would be empty" << endl;
	}


	//Getters
	int getClusterId() const {
		return clusterId;
	}

	/*
	int getPoint(int pos) const {	//CUIDADO
		set<int>::iterator it = pos;
		return clusterPoints[it];
	}
	*/

	int getClusterSize() const {
		return clusterPoints.size();
	}

	float getCentroidByPos(int pos) const {
		return centroid[pos];
	}

	vector<float> getCentroid() const {
		return centroid;
	}

	//Setters
	void setCentroidByPos(int pos, float val) {
		this->centroid[pos] = val;
	}


	//Others
	void calculateClusterCentroid() {
		for (int c = 0; c < dimension; c++) {
			float sum = 0.0;
			for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++)
				sum += g_points[*it][c];

			setCentroidByPos(c, sum / getClusterSize());
		}
	}

	//Calculates intra cluster mean deviation
	float calculateIntraClusterMeanDeviation() const {
		float meanDeviation = 0;
		for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++)
			meanDeviation += calculateDistance(g_points[*it], getCentroid());

		return meanDeviation / getClusterSize();
	}


	//Printers
	void printClusterCentroid() const {
		cout << "Cluster " << getClusterId() << ": " << endl << "Centroid: ";
		for (int i = 0; i < dimension; i++)
			cout << getCentroidByPos(i) << " ";
		cout << endl;
	}

	void printClusterPoints() const {
		cout << "Points: ";
		for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++) {
			cout << *it << " ";
		}
		cout << endl << endl;
	}
};

int Cluster::nextId = 0;