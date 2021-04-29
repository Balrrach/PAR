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

	int seed = 4;
	int iters = 100000;

	if(argc < 2){
		cout << "Error: command-line argument count mismatch" << endl;
		return 1;
	}

	//Benchmark execution
	if (string(argv[1]) == "B") {
		if (argc == 2)
			benchmark(seed);
		
		else if(argc == 3)
			benchmark(atoi(argv[2]));
		
		else{
			cout << "Error: command-line argument count mismatch" << endl;
			return 1;
		}

		return 0;
	}

	//Regular execution
	else {
		cout << argv[1];
		//Need 3 arguments (Points file, Restrictions file, Number of Clusters) to run, else exit
		if (argc < 4) {
			cout << "Error: command-line argument count mismatch" << endl;
			return 1;
		}

		//Update the seed
		if (argc == 5)
			seed = atoi(argv[4]);

		//Fetching data from files
		string points_file = argv[1];
		string restrictions_file = argv[2];
		int K = 0;

		//Incorrect file/s
		if (readData(points_file, restrictions_file) == 1)
			return 1;


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
			cout << "Error: command-line argument count mismatch" << endl;
			break;
		}

		return 0;
	}
}
