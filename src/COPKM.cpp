#include "COPKM.h"

using namespace std;


void COPKM::calculateLowestInfeasibilityClusters(int p, vector<int>& liClusters, const vector<int>& shaping) {
	int lifs = INT_MAX, clusterIfs = 0;
	//vector<int> index;

	for (int k = 0; k < K; k++) {
		clusterIfs = calculateIncrementInfeseability(p, k, shaping);

		if (clusterIfs < lifs) {
			lifs = clusterIfs;
			liClusters.clear();
			liClusters.push_back(k);
		}

		else if (clusterIfs == lifs)
			liClusters.push_back(k);
	}
}


int COPKM::calculateClosestCluster(int p, const vector<int>& liClusters, const vector<Cluster>& clusters) {
	float sum = 0.0, dist = 0.0, ldist = DBL_MAX;
	int closestCluster = -1;
	for (int i = 0; i < liClusters.size(); i++) {
		sum = 0.0;

		for (int j = 0; j < dimension; j++) {
			sum += pow(clusters[liClusters[i]].getCentroidByPos(j) - g_points[p][j], 2.0);
		}

		dist = sqrt(sum);

		if (dist < ldist) {
			ldist = dist;
			closestCluster = liClusters[i];
		}
	}

	return closestCluster;
}


int COPKM::calculateBestCluster(int p, vector<Cluster>& clusters, vector<int>& shaping) {
	vector<int> liClusters;
	int bestCluster = -1;

	calculateLowestInfeasibilityClusters(p, liClusters, shaping);
	bestCluster = calculateClosestCluster(p, liClusters, clusters);

	return bestCluster;
}


void COPKM::assignUnclusteredPoint(int p, vector<Cluster>& clusters, vector<int>& shaping) {
	int newCluster = -1;

	newCluster = calculateBestCluster(p, clusters, shaping);
	clusters[newCluster].addPoint(p);
	updateShapping(p, newCluster, shaping);
}


bool COPKM::assignClusteredPoint(int p, vector<Cluster>& clusters, vector<int>& shaping) {
	bool altered = false;
	vector<int> liClusters;
	int currentCluster = shaping[p], newCluster = -1;

	newCluster = calculateBestCluster(p, clusters, shaping);
	if (currentCluster != newCluster) {
		transferPoint(p, currentCluster, newCluster, clusters);
		updateShapping(p, newCluster, shaping);
		altered = true;
	}

	return altered;
}


bool COPKM::realocatePointToBestCluster(int p, vector<Cluster>& clusters, vector<int>& shaping) {
	bool altered = false;
	int currentCluster = shaping[p];

	if (currentCluster == -1) {
		assignUnclusteredPoint(p, clusters, shaping);
		altered = true;
	}

	else if (clusters[shaping[p]].getClusterSize() > 1)
		altered = assignClusteredPoint(p, clusters, shaping);

	return altered;
}


void COPKM::initializeClusters(vector<Cluster>& clusters, vector<int>& shaping, int seed) {

	bool repeat = true;
	vector<float> centroide(dimension);
	vector<int> index;
	initializeUniformInt(index, 0, g_points.size());
	shuffle(index.begin(), index.end(), std::default_random_engine(seed));

	while (repeat) {
		repeat = false;

		//-----Calculate clusters center randomly-----
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < dimension; j++) {
				centroide[j] = Rand();
			}

			clusters.push_back(Cluster(centroide, i));
		}

		//-----Asociate each point to its best Cluster-----
		for (int p = 0; p < g_points.size(); p++)
			realocatePointToBestCluster(index[p], clusters, shaping);

		//-----Checking that all clusters are associated with at least one point-----
		for (int i = 0; i < K; i++)
			if (clusters[i].getClusterSize() < 1) {
				repeat = true;
				clusters.clear();
				for (int j = 0; j < shaping.size(); j++)
					shaping[j] = -1;
				shuffle(index.begin(), index.end(), std::default_random_engine(seed));
				break;
			}

		//-----Reset-----
		//printVectorElements(index);			
		//for (int i = 0; i < g_points.size(); i++)
			//clusters[i];
	}

	//-----Recalculating the center of each cluster-----
	for (int i = 0; i < K; i++)
		clusters[i].calculateClusterCentroid((new PAR)->g_points);

	cout << "Clusters initialized = " << clusters.size() << endl << endl;
}


vector<float> COPKM::executeCOPKM() {
	ExecutionParameters ep;
	auto begin = std::chrono::high_resolution_clock::now();

	Set_random(ep.seed);
	vector<Cluster> clusters;
	vector<int> shaping(g_points.size(), -1);
	bool key;

	initializeClusters(clusters, shaping, ep.seed);

	bool repeat = true;
	int iter = 1;
	while (repeat) {
		//cout << "Iter- " << iter << "/" << iters << endl;
		repeat = false;

		// -----Change each point to the cluster that better fits it-----
		//shuffle(index.begin(), index.end(), std::default_random_engine(seed));
		for (int i = 0; i < g_points.size(); i++) {
			if (clusters[shaping[i]].getClusterSize() > 1) {
				key = realocatePointToBestCluster(i, clusters, shaping);
				if (key == true)
					repeat = true;
			}
		}

		// -----Recalculate the center of each cluster-----
		for (int i = 0; i < K; i++)
			clusters[i].calculateClusterCentroid((new PAR)->g_points);

		iter++;
	}

	cout << "Clustering completed in iteration : " << iter << endl << endl;

	auto end = std::chrono::high_resolution_clock::now();
	printSolution(clusters, shaping);
	std::cout << "Tiempo de ejecucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

	return createOutput(clusters, shaping, std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}