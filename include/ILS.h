#pragma once

#include "BL.h"

class ILS : public BL
{
public:
	ILS();

	std::vector<float> execute();

protected:
	unsigned int NCandidates;

	void fixedSegmentMutationOperator(std::vector<Cluster> & clusters, std::vector<int> & shaping);
	virtual float optimumSearcher(std::vector<Cluster> & clusters, std::vector<int> & shaping);
};