#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "CSV.h"
#include "COPKM.h"
#include "BL.h"
#include "Benchmark.h"

using namespace std;

vector<vector<float>> g_points;
map<int, vector <pair<int, int> > > restrictionsMap;
vector<vector<int>> restrictionsList;
int dimension;
int K;
float lambda;
float optimumDistance;


int main(int argc, char** argv) {

	if (string(argv[1]) == "B") {
		benchmark();
		return 0;
	}

	else {
		cout << argv[1];
		//Need 3 arguments (Points file, Restrictions file, Number of Clusters) to run, else exit
		if (argc != 4) {
			cout << "Error: command-line argument count mismatch";
			return 1;
		}

		//Fetching data from files
		string points_file = argv[1];
		string restrictions_file = argv[2];
		int K = 0;

		if (readData(points_file, restrictions_file) == 1)
			return 1;


		int seed = 4;
		int iters = 100000;

		switch (atoi(argv[3])){
		case 1:
			//Running COPKM Clustering
			COPKM(seed, iters);
			break;

		case 2:
			//Running BL Clustering
			BL(seed, iters);
			break;

		default:
			cout << "Wrong algorith selection:" << endl;
			cout << "1 ------ COPKM" << endl;
			cout << "2 ------ BL" << endl;
			break;
		}

		return 0;
	}
}
