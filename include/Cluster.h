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


	//Others
	void calculateCentroid() {
		for (int c = 0; c < dimension; c++) {
			double sum = 0.0;
			for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++)
				sum += g_points[*it][c];

			setCentroidByPos(c, sum / getClusterSize());
		}
	}

	//Calculates intra cluster mean deviation
	double calculateIntraClusterMeanDeviation(const Cluster& c) const {
		double meanDeviation = 0, sum = 0;
		for (set<int>::iterator it = clusterPoints.begin(); it != clusterPoints.end(); it++) {
			sum = 0;
			for (int c = 0; c < dimension; c++) {
				sum += pow(g_points[*it][c] - getCentroidByPos(c), 2.0);
			}

			meanDeviation += sqrt(sum);
		}

		return meanDeviation / c.getClusterSize();
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