#include "AGGUN.h"


AGGUN::AGGUN() { crossingOperator = 0; }

std::vector<float> AGGUN::execute() { return executeGeneticAlgoritm(); }