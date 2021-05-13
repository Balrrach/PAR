#pragma once

#include "BL.h"

class BMB : BL
{
public:
	BMB();
	std::vector<float> execute();

protected:
	unsigned int NCandidates;
};