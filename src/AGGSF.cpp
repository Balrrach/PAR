#include "AGGSF.h"


AGGSF::AGGSF() { crossingOperator = 1; }

std::vector<float> AGGSF::execute() { return executeGeneticAlgoritm(); }