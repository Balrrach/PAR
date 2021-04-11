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


//Reads point data from a file in CSV format
int fetchPoints(string filename) {
	//Open file for fetching points
	cout << "Filename: " << filename << endl;
	ifstream infile(filename.c_str());

	if (!infile.is_open()) {
		return 1;
	}

	int pointId = 0;
	vector<string> aux;
	vector<float> coordenates;
	string line;

	while (getline(infile, line)) {
		aux.clear();
		coordenates.clear();

		split(line, ',', aux);
		for (unsigned int i = 0; i < aux.size(); i++) {
			coordenates.push_back(stof(aux[i]));
		}
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
	infile.close();

	dimension = g_points[0].size();

	return 0;
}


//Reads restrictions data from a file in CSV format
int fetchRestrictions(string filename) {
	//Open file for fetching restrictions
	cout << "Filename: " << filename << endl;
	ifstream infile(filename.c_str());

	if (!infile.is_open()) {
		return 1;
	}

	//Fetching restrictions from file
	string line;
	vector<string> aux;
	int i = 0;

	while (getline(infile, line)) {
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
	infile.close();

	cout << "Number of restrictions: " << restrictionsList.size() << endl;
	
	lambda = calculateLambda();

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

	return 0;
}


//Reads all data that algorithms need to work
int readData(const string& points_file, const string& restrictions_file) {
	cleanGlobals();

	if (points_file == "zoo") {
		K = 7;
		optimumDistance = 0.904799856193481;

		if (fetchPoints(".\\datos\\zoo_set.dat") == 0)
			cout << "Points fetched successfully!" << endl << endl;
		else {
			cout << "Error: Failed to open points file" << endl;
			return 1;
		}

		if (restrictions_file == to_string(10)) {
			if (fetchRestrictions(".\\datos\\zoo_set_const_10.const") == 0)
				cout << "Restrictions fetched successfully!" << endl << endl;
			else {
				cout << "Error: Failed to open restrictions file" << endl;
				return 1;
			}
		}

		else if (restrictions_file == to_string(20)) {
			if (fetchRestrictions(".\\datos\\zoo_set_const_20.const") == 0)
				cout << "Restrictions fetched successfully!" << endl << endl;
			else {
				cout << "Error: Failed to open restrictions file" << endl;
				return 1;
			}
		}

		else {
			cout << "Error: Wrong percentage of restrictions" << endl;
			return 1;
		}
	}


	else if (points_file == "glass") {
		K = 7;
		optimumDistance = 0.364290281975566;

		if (fetchPoints(".\\datos\\glass_set.dat") == 0)
			cout << "Points fetched successfully!" << endl << endl;
		else {
			cout << "Error: Failed to open points file" << endl;
			return 1;
		}

		if (restrictions_file == to_string(10)) {
			if (fetchRestrictions(".\\datos\\glass_set_const_10.const") == 0)
				cout << "Restrictions fetched successfully!" << endl << endl;
			else {
				cout << "Error: Failed to open restrictions file" << endl;
				return 1;
			}
		}

		else if (restrictions_file == to_string(20)) {
			if (fetchRestrictions(".\\datos\\glass_set_const_20.const") == 0)
				cout << "Restrictions fetched successfully!" << endl << endl;
			else {
				cout << "Error: Failed to open restrictions file" << endl;
				return 1;
			}
		}

		else {
			cout << "Error: Wrong percentage of restrictions" << endl;
			return 1;
		}
	}


	else if (points_file == "bupa") {
		K = 16;
		optimumDistance = 0.229248049533093;

		if (fetchPoints(".\\datos\\bupa_set.dat") == 0)
			cout << "Points fetched successfully!" << endl << endl;
		else {
			cout << "Error: Failed to open points file" << endl;
			return 1;
		}

		if (restrictions_file == to_string(10)) {
			if (fetchRestrictions(".\\datos\\bupa_set_const_10.const") == 0)
				cout << "Restrictions fetched successfully!" << endl << endl;
			else {
				cout << "Error: Failed to open restrictions file" << endl;
				return 1;
			}
		}

		else if (restrictions_file == to_string(20)) {
			if (fetchRestrictions(".\\datos\\bupa_set_const_20.const") == 0)
				cout << "Restrictions fetched successfully!" << endl << endl;
			else {
				cout << "Error: Failed to open restrictions file" << endl;
				return 1;
			}
		}

		else {
			cout << "Error: Wrong percentage of restrictions" << endl;
			return 1;
		}
	}


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


//
void toBoxplot(const vector<Cluster>& clusters) {
	ofstream myfile;
	string fileName;

	if (dimension == 16)
		fileName = "..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\zoo.csv";

	else if (dimension == 9)
		fileName = "..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\glass.csv";

	else
		fileName = "..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\bupa.csv";

	myfile.open(fileName);
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < dimension-1; j++)
			myfile << clusters[i].getCentroidByPos(j) << ", ";

		myfile << clusters[i].getCentroidByPos(dimension - 1) <<endl;
	}

	myfile.close();
}