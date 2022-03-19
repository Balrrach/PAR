#include "DataSets.h"
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;


DataSets::DataSets(const string& _dataSet, const string& _restrictionsNumber) {
	string pointsPath = composePointsFile(_dataSet);
	string restrictionsPath = composeRestrictionsFile(_dataSet, _restrictionsNumber);
	fetch(pointsPath, restrictionsPath);
}

const string DataSets::composePointsFile(string dataSet) {
	fs::path pointsRoute;
	pointsRoute /= ".."; pointsRoute /= ".."; pointsRoute /= "datos";
	pointsRoute /= dataSet + "_set.dat";
	return pointsRoute;
};

const string DataSets::composeRestrictionsFile(const string& dataSet, const string& restrictionsNumber) {
	fs::path restrictionsRoute;
	restrictionsRoute /= ".."; restrictionsRoute /= ".."; restrictionsRoute /= "datos";
	restrictionsRoute /= dataSet + "_set_const_" + restrictionsNumber + ".const";
	return restrictionsRoute;
}

void DataSets::fetch(const string& pointsPath, const string& restrictionsPath) {
	cout << endl << "--->Dataset:" << endl;
	fetchPoints(pointsPath);
	fetchRestrictions(restrictionsPath);
	cout << endl;
}

