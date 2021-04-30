#pragma once

#include <map>
#include <utility>
#include <vector>

using namespace std;


class ExecutionParameters {
public:
	static int seed;
	static int iters;

	ExecutionParameters() {};
	void initialize();
};

