#pragma once

#include <iostream>
#include <string>

class ExecutionParameters {
public:
	static int seed;
	static int iters;

	ExecutionParameters() {};
	void initialize();
	std::string algorithmError();
};

