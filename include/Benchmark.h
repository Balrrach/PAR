#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "ExecutionParameters.h"
#include "DataSets.h"
#include "BL.h"
#include "COPKM.h"
#include "AGGUN.h"
#include "AGGSF.h"
#include "AGEUN.h"
#include "AGESF.h"


//Benchmark function
//void benchmark();
void benchmark(std::string algorithm);
void benchmarkSelector(int number);
std::vector<float> algorithmSelection(std::string selector);

void p1Benchmark();
void p2Benchmark();


//Encapsulates the execution of a given algorithm and dataset nexe times keeping the needed structure
//to export the results to a csv file
//void operate(int nexe, int estadisticos,
//	std::vector<float> & result_COPKM, std::vector<float> & result_BL,
//	std::vector<std::string> & table_COPKM, std::vector<std::string> & table_BL,
//	std::vector<float> & media_COPKM, std::vector<float> & media_BL,
//	std::string & string_Media_COPKM, std::string & string_Media_BL);

void operate(std::string algoritmo, int nexe, int estadisticos,
	std::vector<float> & result, std::vector<std::string> & table,
	std::vector<float> & media, std::string & string_Media);