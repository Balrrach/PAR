#include "DataSets.h"

using namespace std;


void DataSets::fetch(const string& pointsPath, const string& restrictionsPath) {
	cout << endl << "--->Dataset:" << endl;
	fetchPoints(pointsPath);
	fetchRestrictions(restrictionsPath);
	cout << endl;
}


const string DataSets::composePointsFile(string dataSet) { return "..\\datos\\" + dataSet + "_set.dat"; };
const string DataSets::composeRestrictionsFile(const string& dataSet, const string& restrictionsNumber) {
	return "..\\datos\\" + dataSet + "_set_const_" + restrictionsNumber + ".const";
}


//DataSets() {};
DataSets::DataSets(const string& _dataSet, const string& _restrictionsNumber) {
	string pointsPath = composePointsFile(_dataSet);
	string restrictionsPath = composeRestrictionsFile(_dataSet, _restrictionsNumber);
	fetch(pointsPath, restrictionsPath);
}


//Reads all data that algorithms need to work
void readData(const string& dataSet, const string& restrictionsNumber) {
	(new ExecutionParameters)->cleanGlobals();

	if (dataSet == "zoo")
		new Zoo(restrictionsNumber);

	else if (dataSet == "glass")
		new Glass(restrictionsNumber);

	else if (dataSet == "bupa")
		new Bupa(restrictionsNumber);

	else
		throw "Error: Wrong file";


	//Exception if there are less points than clusters
	if ((new ExecutionParameters)->g_points.size() < (new ExecutionParameters)->K)
		throw "Error: Number of clusters greater than number of points";
}