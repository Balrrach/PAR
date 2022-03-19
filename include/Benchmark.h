#pragma once

#include <iostream>
#include <vector>

#include "ExecutionParameters.h"
#include "DataSets.h"
#include "BL.h"
#include "COPKM.h"
#include "AGGUN.h"
#include "AGGSF.h"
#include "AGEUN.h"
#include "AGESF.h"
#include "AM-C.h"
#include "AM-P.h"
#include "AM-M.h"
#include "BMB.h"
#include "ES.h"
#include "ILS.h"
#include "ILS-ES.h"

//Parameter sorting
void algortimExecution(int argc, char ** argv);
void benchmarkExecution(int argc, char ** argv);
void uniqueBenchmarkExecution(int argc, char ** argv);

//Benchmark function
void benchmark(std::string algorithm);
void benchmarkSelector(int number);
std::vector<float> algorithmSelection(std::string selector);

//Compose benchmark
void p1Benchmark();
void p2Benchmark();
void p3Benchmark();

//Reads all data that algorithms need
void readData(const std::string& dataSet, const std::string& restrictionsNumber);

//Auxiliary function
void operate(std::string algoritmo, int nexe, int estadisticos,
	std::vector<float> & result, std::vector<std::string> & table,
	std::vector<float> & media, std::string & string_Media);

