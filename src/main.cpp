#include <iostream>

#include "Benchmark.h"
#include "ExecutionParameters.h"

using namespace std;


int main(int argc, char** argv) {
	(new ExecutionParameters())->initialize();

	if(argc < 2)
		throw "Insuffitient Number of arguments";

	if (string(argv[1]) == "B")
		benchmarkExecution(argc, argv);

	else if (string(argv[1]) == "b")
		uniqueBenchmarkExecution(argc, argv);

	else
		algortimExecution(argc, argv);

	cout << endl;
}
