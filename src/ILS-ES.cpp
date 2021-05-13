#include "ILS-ES.h"


std::vector<float> ILSES::execute() { return ILS::execute(); }


float ILSES::optimumSearcher(std::vector<Cluster> & clusters, std::vector<int> & shaping)
{
	return ESCore(clusters, shaping);
}
