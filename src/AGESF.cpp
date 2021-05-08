#include "AGESF.h"


AGESF::AGESF() { crossingOperator = 1; }

std::vector<float> AGESF::execute() { return executeGeneticAlgoritm(); }