#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

#include "VectorUtilities.h"
#include "Cluster.h"
#include "PAR.h"

using namespace std;

extern vector<vector<float> > g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int> > restrictionsList;
extern int dimension;
extern int K;
extern float lambda;
extern float optimumDistance;


//Cleans global variables
void cleanGlobals() {
	g_points.clear();
	restrictionsMap.clear();
	restrictionsList.clear();
	dimension = 0;
	K = 0;
	lambda = 0;
	optimumDistance = 0;
}


//Calculates lambda value
float calculateLambda() {
	//Maximum distance calculation
	float max = 0.0, dist;

	for (int i = 0; i < g_points.size(); i++) {
		for (int j = 0; j < g_points.size(); j++) {
			if (j > i) {
				dist = calculateDistance(g_points[i], g_points[j]);;

				if (max < dist)
					max = dist;
			}
		}
	}

	return max / restrictionsList.size();
}


/*
Funcion encargada de convertir una cadena en la misma cadena
sustituyendo el caracter dado por c por un espacio. Parametros:
	s: Cadena base
	c: Caracter a sustituir por un espacio
	v: Cadena resultante
*/
void split(const string& s, char c, vector<string>& v) {
	int i = 0;
	int j = s.find(c);

	while (j >= 0) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j < 0) {
			v.push_back(s.substr(i, s.length()));
		}
	}
}


ifstream openFile(const string& filename) {
	cout << "Filename: " << filename << endl;

	ifstream infile(filename.c_str());
	if (!infile.is_open())
		throw "File not found!";

	return infile;
}


void readPoints(ifstream & pointsFile) {
	int pointId = 0;
	vector<string> aux;
	vector<float> coordenates;
	string line;

	while (getline(pointsFile, line)) {
		aux.clear();
		coordenates.clear();

		split(line, ',', aux);
		for (auto i : aux)
			coordenates.push_back(stof(i));

		g_points.push_back(coordenates);

		/*
		cout << "Punto: ";
		for (unsigned int i = 0; i < aux.size(); i++) {
			cout << coordenates[i] << " ";
		}
		cout << endl;
		*/
	}
	cout << "Number of points: " << g_points.size() << endl;

	dimension = g_points[0].size();
}


//Reads point data from a file in CSV format
void fetchPoints(const string & pointsPath) {
	ifstream pointsFile = openFile(pointsPath);
	readPoints(pointsFile);
	pointsFile.close();
}


void readRestrictions(ifstream& restrictionsFile) {
	string line;
	vector<string> aux;
	int i = 0;

	while (getline(restrictionsFile, line)) {
		aux.clear();
		split(line, ',', aux);

		for (int j = 0; j < aux.size(); j++) {
			
			if (i < j) {
				if (stoi(aux[j]) == -1)
					restrictionsList.push_back(vector<int>{-1, i, j});
				if (stoi(aux[j]) == 1)
					restrictionsList.push_back(vector<int>{1, i, j});
			}
			
			if (i != j) {
				if (stoi(aux[j]) == -1)
					restrictionsMap[i].push_back(pair<int, int>{-1, j});
				if (stoi(aux[j]) == 1)
					restrictionsMap[i].push_back(pair<int, int>{1, j});
			}
		}

		i++;
	}
	
	cout << "Number of restrictions: " << restrictionsList.size() << endl;

	lambda = calculateLambda();
}


//Reads restrictions data from a file in CSV format
int fetchRestrictions(string restrictionsPath) {
	ifstream restrictionsFile = openFile(restrictionsPath);
	readRestrictions(restrictionsFile);
	restrictionsFile.close();
	/*
	int k = 0, l = 0;
	for (int c = 0; c < restrictionsList.size(); c++) {
		if (restrictionsList[c][2] == -1) {
			cout << "Restriccion CL numero " << i << " : (" << restrictionsList[c][0] << " , " << restrictionsList[c][1] << ")" << endl;
			k++;
		}
		if (restrictionsList[c][2] == 1) {
			cout << "Restriccion ML numero " << i << " : (" << restrictionsList[c][0] << " , " << restrictionsList[c][1] << ")" << endl;
			l++;
		}
	}

	cout << endl;

	for (int i = 0; i < g_points.size(); i++)
		for (int j = 0; j < restrictionsMap[i].size(); j++)
			cout << "Restriccion " << j << " asociada al punto " << i << " de tipo " << restrictionsMap[i][j].first << " pareja: " << restrictionsMap[i][j].second << endl;
	*/
}


class DataSets {
protected:
	bool fetch(const string& pointsPath, const string& restrictionsPath) {
		fetchPoints(pointsPath);
		fetchRestrictions(restrictionsPath);
	}

	const string composePointsFile(string dataSet) {return "..\\datos\\" + dataSet + "_set.dat";};
	const string composeRestrictionsFile(const string & dataSet, const string & restrictionsNumber) {
		return "..\\datos\\" + dataSet + "_set_const_" + restrictionsNumber + ".const";
	}

public:
	//DataSets() {};
	DataSets(const string & _dataSet, const string & _restrictionsNumber){
		string pointsPath = composePointsFile(_dataSet);
		string restrictionsPath = composeRestrictionsFile(_dataSet, _restrictionsNumber);
		fetch(pointsPath, restrictionsPath);
	};
};


class Zoo : public DataSets{
public:
	//Zoo() {};
	Zoo(string _restrictionsNumber) : DataSets("zoo", _restrictionsNumber){
		K = 7;
		optimumDistance = 0.904799856193481;
	};
};

class Glass : public DataSets {
public:
	//Glass() {};
	Glass(string _restrictionsNumber) : DataSets("glass", _restrictionsNumber) {
		K = 7;
		optimumDistance = 0.364290281975566;
	};
};

class Bupa : public DataSets {
public:
	//Bupa() {};
	Bupa(const string & _restrictionsNumber) : DataSets("bupa", _restrictionsNumber) {
		K = 16;
		optimumDistance = 0.220423749236422;
	};
};


//Reads all data that algorithms need to work
int readData(const string& dataSet, const string & restrictions_file) {
	cleanGlobals();
	
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
	if (g_points.size() < K) {
		cout << "Error: Number of clusters greater than number of points" << endl;
		return 1;
	}

	return 0;
}


//Creates the output data
vector<float> createOutput(const vector<Cluster>& clusters, const vector<int>& shaping, float time) {
	vector<float> sol;
	sol.push_back((float)calculateShapingInfeasibility(shaping));
	sol.push_back(calculateErrorDistance(clusters));
	sol.push_back(calculateFitness(clusters, shaping));
	sol.push_back(time);
	return sol;
}


//Turns output data into an string
string outputToString(vector<float> results) {
	return "," + to_string((int)results[0]) + "," + to_string_with_precision(results[1], 5) + 
			"," + to_string_with_precision(results[2], 5) + "," + to_string((int)results[3]);
}


//Writes the results of a given algorithm and dataset to a given file
void writeOutput(const string& fileName, const string& headers, int nexe, const vector<string>& table, const string& string_Media) {
	ofstream myfile;
	myfile.open(fileName);
	//myfile << dataset << endl;
	myfile << headers << endl;
	for (int i = 0; i < nexe; i++)
		myfile << table[i] << endl;
	myfile << "Media" + string_Media << endl;
	myfile.close();
}


//Writes the clusters coordenates
void toBoxplot(const vector<Cluster>& clusters) {
	ofstream myfile;
	string fileName;

	if (dimension == 16)
		fileName = "..\\..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\zoo.csv";

	else if (dimension == 9)
		fileName = "..\\..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\glass.csv";

	else
		fileName = "..\\..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\bupa.csv";

	myfile.open(fileName);
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < dimension-1; j++)
			myfile << clusters[i].getCentroidByPos(j) << ", ";

		myfile << clusters[i].getCentroidByPos(dimension - 1) <<endl;
	}

	myfile.close();
}