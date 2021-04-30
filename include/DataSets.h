#pragma once

#include "csv.h"
#include "utilities.h"
#include "Cluster.h"
#include "PAR.h"

using namespace std;

class DataSets {
protected:
	bool fetch(const string& pointsPath, const string& restrictionsPath) {
		fetchPoints(pointsPath);
		fetchRestrictions(restrictionsPath);
	}

	const string composePointsFile(string dataSet) { return "..\\datos\\" + dataSet + "_set.dat"; };
	const string composeRestrictionsFile(const string& dataSet, const string& restrictionsNumber) {
		return "..\\datos\\" + dataSet + "_set_const_" + restrictionsNumber + ".const";
	}

public:
	//DataSets() {};
	DataSets(const string& _dataSet, const string& _restrictionsNumber) {
		string pointsPath = composePointsFile(_dataSet);
		string restrictionsPath = composeRestrictionsFile(_dataSet, _restrictionsNumber);
		fetch(pointsPath, restrictionsPath);
	};
};


class Zoo : public DataSets {
public:
	//Zoo() {};
	Zoo(string _restrictionsNumber) : DataSets("zoo", _restrictionsNumber) {
		(new PAR)->K = 7;
		(new PAR)->optimumDistance = 0.904799856193481;
	};
};

class Glass : public DataSets {
public:
	//Glass() {};
	Glass(string _restrictionsNumber) : DataSets("glass", _restrictionsNumber) {
		(new PAR)->K = 7;
		(new PAR)->optimumDistance = 0.364290281975566;
	};
};

class Bupa : public DataSets {
public:
	//Bupa() {};
	Bupa(const string& _restrictionsNumber) : DataSets("bupa", _restrictionsNumber) {
		(new PAR)->K = 16;
		(new PAR)->optimumDistance = 0.220423749236422;
	};
};


//Reads all data that algorithms need to work
int readData(const string& dataSet, const string& restrictions_file) {
	(new PAR)->cleanGlobals();

	if (dataSet == "zoo")
		new Zoo(restrictions_file);

	else if (dataSet == "glass")
		new Glass(restrictions_file);

	else if (dataSet == "bupa")
		new Bupa(restrictions_file);

	else {
		cout << "Error: Wrong file" << endl << endl;
		return 1;
	}

	//Return if number of clusters > number of points
	if ((new PAR)->g_points.size() < (new PAR)->K) {
		cout << "Error: Number of clusters greater than number of points" << endl;
		return 1;
	}

	return 0;
}