#include <iostream>

#include "BL.h"
#include "COPKM.h"
#include "AGGUN.h"
#include "AGGSF.h"
#include "AGEUN.h"
#include "AGESF.h"
#include "benchmark.h"
#include "DataSets.h"
#include "ExecutionParameters.h"

using namespace std;


void algortimExecution(int argc, char** argv) {
	//Need 3 arguments (Points file, Restrictions file, Number of Clusters) to run, else exit
	if (argc < 4)
		throw "Error: command-line argument count mismatch";

	//Update the seed
	if (argc == 5)
		(new ExecutionParameters())->seed = atoi(argv[4]);

	//Fetching data from files
	string points_file = argv[1];
	string restrictions_file = argv[2];
	readData(points_file, restrictions_file);
	algorithmSelection(argv[3]);
}


void benchmarkExecution(int argc, char** argv) {
	switch (argc) {
	case 3:
		benchmarkSelector(stoi(argv[2]));
		break;

	case 4:
		(new ExecutionParameters())->seed = atoi(argv[3]);
		benchmarkSelector(stoi(argv[2]));
		break;

	default:
		cout << "No benchmark specified";
		throw "Error: command-line argument mismatch";
		break;
	}
}



int main(int argc, char** argv) {
	(new ExecutionParameters())->initialize();

	if(argc < 2)
		throw "Error: command-line argument mismatch";

	if (string(argv[1]) == "B")
		benchmarkExecution(argc, argv);

	else
		algortimExecution(argc, argv);
}