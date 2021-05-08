#pragma once

#include "AM.h"


class AMP : public AM
{
protected:
	float pls;

	void selectPopulationtoImprove();

public:
	AMP();
};