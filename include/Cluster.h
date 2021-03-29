#pragma once

#include <set>

using namespace std;


class Cluster {

private:
	int clusterId;
	vector<double> centroid;
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

	bool removePoint(int pointId) {
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

	//Setters
	double getCentroidByPos(int pos) const {
		return centroid[pos];
	}

	void setCentroidByPos(int pos, double val) {
		this->centroid[pos] = val;
	}

	void recalculateCentroid() {
		for (int c = 0; c < g_points[0].size(); c++){
			double sum = 0.0;
			for (int p = 0; p < getClusterSize(); p++)
				sum += g_points[p][c];

			setCentroidByPos(c, sum / getClusterSize());
		}
	}

	//Printers
	void printClusterCentroid() const {
		cout << "Cluster " << getClusterId() << ": " << endl <<"Centroid: ";
		for (int i = 0; i < dimension; i++)
			cout << getCentroidByPos(i) << " ";
		cout << endl;
	}


	void printClusterPoints() const {
		cout << "Points: ";
		for (set<int>::iterator it = clusterPoints.begin(); it!= clusterPoints.end(); it++) {
			cout << *it << " ";
		}
		cout << endl << endl;
	}
};

int Cluster::nextId = 0;