#include "AGEUN.h"


AGEUN::AGEUN() { crossingOperator = 0; }

std::vector<float> AGEUN::execute() { return executeGeneticAlgoritm(); }