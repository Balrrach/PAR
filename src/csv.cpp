#include "csv.h"

using namespace std;


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
					(new PAR)->restrictionsList.push_back(vector<int>{-1, i, j});
				if (stoi(aux[j]) == 1)
					(new PAR)->restrictionsList.push_back(vector<int>{1, i, j});
			}

			if (i != j) {
				if (stoi(aux[j]) == -1)
					(new PAR)->restrictionsMap[i].push_back(pair<int, int>{-1, j});
				if (stoi(aux[j]) == 1)
					(new PAR)->restrictionsMap[i].push_back(pair<int, int>{1, j});
			}
		}

		i++;
	}

	cout << "Number of restrictions: " << (new PAR)->restrictionsList.size() << endl;

	(new PAR)->calculateLambda();
}


void readPoints(ifstream& pointsFile) {
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

		(new PAR)->g_points.push_back(coordenates);
	}
	cout << "Number of points: " << (new PAR)->g_points.size() << endl;

	(new PAR)->dimension = (new PAR)->g_points[0].size();
}


ifstream openFile(const string& filename) {
	cout << "Filename: " << filename << endl;

	ifstream infile(filename.c_str());
	if (!infile.is_open())
		throw "File not found!";

	return infile;
}


void fetchPoints(const string& pointsPath) {
	ifstream pointsFile = openFile(pointsPath);
	readPoints(pointsFile);
	pointsFile.close();
}


void fetchRestrictions(string restrictionsPath) {
	ifstream restrictionsFile = openFile(restrictionsPath);
	readRestrictions(restrictionsFile);
	restrictionsFile.close();
}


string outputToString(vector<float> results) {
	return "," + to_string((int)results[0]) + "," + toStringWithPrecision(results[1], 5) +
		"," + toStringWithPrecision(results[2], 5) + "," + to_string((int)results[3]);
}


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


void toBoxplot(const vector<Cluster>& clusters) {
	ofstream myfile;
	string fileName;

	if ((new PAR)->dimension == 16)
		fileName = "..\\..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\zoo.csv";

	else if ((new PAR)->dimension == 9)
		fileName = "..\\..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\glass.csv";

	else
		fileName = "..\\..\\..\\Practica 1\\Memoria\\boxplots\\clusters\\bupa.csv";

	myfile.open(fileName);
	for (int i = 0; i < (new PAR)->K; i++) {
		for (int j = 0; j < (new PAR)->dimension - 1; j++)
			myfile << clusters[i].getCentroidByPos(j) << ", ";

		myfile << clusters[i].getCentroidByPos((new PAR)->dimension - 1) << endl;
	}

	myfile.close();
}