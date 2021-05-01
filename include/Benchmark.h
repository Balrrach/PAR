#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "ExecutionParameters.h"
#include "DataSets.h"
#include "COPKM.h"
#include "BL.h"


//Encapsulates the execution of a given algorithm and dataset nexe times keeping the structure needed
//to export the results to a csv file
void operate(int nexe, int estadisticos,
	std::vector<float>& result_COPKM, std::vector<float>& result_BL,
	std::vector<std::string>& table_COPKM, std::vector<std::string>& table_BL,
	std::vector<float>& media_COPKM, std::vector<float>& media_BL,
	std::string& string_Media_COPKM, std::string& string_Media_BL);

//Benchmark function
int benchmark();