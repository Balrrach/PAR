#include <iostream>

#include "ExecutionParameters.h"
#include "CSV.h"
#include "COPKM.h"
#include "BL.h"
#include "Benchmark.h"

using namespace std;


void algorimtSelection(int selector) {
	(new executionParameters())->initialize();

	switch (selector) {
	case 1:
		COPKM();
		break;

	case 2:
		BL();
		break;

	default:
		throw "Error: command-line argument mismatch";
		break;
	}
}


void algortimExecution(int argc, char** argv) {
	int number = atoi(argv[3]);

	//Need 3 arguments (Points file, Restrictions file, Number of Clusters) to run, else exit
	if (argc < 4)
		throw "Error: command-line argument count mismatch";

	//Update the seed
	if (argc == 5)
		(new executionParameters())->seed = atoi(argv[4]);

	//Fetching data from files
	string points_file = argv[1];
	string restrictions_file = argv[2];
	readData(points_file, restrictions_file);
	algorimtSelection(number);
}


void benchmarkExecution(int argc, char** argv) {
	if (argc == 2)
		benchmark();

	else if (argc == 3) {
		(new executionParameters())->seed = atoi(argv[2]);
		benchmark();
	}

	else
		throw "Error: command-line argument mismatch";
}



int main(int argc, char** argv) {
	(new executionParameters())->initialize();

	if(argc < 2)
		throw "Error: command-line argument mismatch";

	if (string(argv[1]) == "B")
		benchmarkExecution(argc, argv);

	else
		algortimExecution(argc, argv);
}