#include "ExecutionParameters.h"


int ExecutionParameters::seed;
int ExecutionParameters::iters;


void ExecutionParameters::initialize() {
	seed = 4;
	iters = 100000;
};