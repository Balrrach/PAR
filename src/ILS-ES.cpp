#include "ILS-ES.h"


ILSES::ILSES()
{
	ESMaxIters = 10000;
}


std::vector<float> ILSES::execute() { return ILS::execute(); }


float ILSES::optimumSearcher(std::vector<Cluster> & clusters, std::vector<int> & shaping)
{
	return ESCore(clusters, shaping);
}
