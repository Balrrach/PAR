#pragma once

#include "csv.h"
#include "PAR.h"


class DataSets {
protected:
	void fetch(const std::string& pointsPath, const std::string& restrictionsPath);

	const std::string composePointsFile(std::string dataSet);
	const std::string composeRestrictionsFile(const std::string& dataSet, const std::string& restrictionsNumber);

public:
	//DataSets() {};
	DataSets(const std::string& _dataSet, const std::string& _restrictionsNumber);
};


class Zoo : public DataSets {
public:
	//Zoo() {};
	Zoo(std::string _restrictionsNumber) : DataSets("zoo", _restrictionsNumber) {
		(new PAR)->K = 7;
		(new PAR)->optimumDistance = 0.904799856193481;
	};
};

class Glass : public DataSets {
public:
	//Glass() {};
	Glass(std::string _restrictionsNumber) : DataSets("glass", _restrictionsNumber) {
		(new PAR)->K = 7;
		(new PAR)->optimumDistance = 0.364290281975566;
	};
};

class Bupa : public DataSets {
public:
	//Bupa() {};
	Bupa(const std::string& _restrictionsNumber) : DataSets("bupa", _restrictionsNumber) {
		(new PAR)->K = 16;
		(new PAR)->optimumDistance = 0.220423749236422;
	};
};


//Reads all data that algorithms need
void readData(const std::string& dataSet, const std::string& restrictionsNumber);