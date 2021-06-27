#pragma once

#include "ES.h"
#include "ILS.h"

class ILSES : public ILS, public ES
{
public:
	ILSES();
	std::vector<float> execute();

protected:
	float optimumSearcher(std::vector<Cluster> & clusters, std::vector<int> & shaping);
};