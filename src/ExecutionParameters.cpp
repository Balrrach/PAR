#include "ExecutionParameters.h"

using namespace std;

int ExecutionParameters::seed;
int ExecutionParameters::maxIters;
map<int, vector <pair<int, int> > > ExecutionParameters::restrictionsMap;
vector<vector<int>> ExecutionParameters::restrictionsList;
vector<vector<float>> ExecutionParameters::g_points;
int ExecutionParameters::pointsSize;
float ExecutionParameters::optimumDistance;
int ExecutionParameters::dimension;
int ExecutionParameters::K;
float ExecutionParameters::lambda;
std::mt19937 ExecutionParameters::rng;


//Default execution parameters
void ExecutionParameters::initialize()
{
	seed = 4;
	maxIters = 100000;
};


string ExecutionParameters::algorithmError()
{
	string errorMessage = "\nError: Wrong Algorithm. Options are: \n";
	string COPKM = "1 ----------------- COPKM\n";
	string BL = "2 ----------------- BL\n";
	string AGGUN = "3 ----------------- AGG-UN\n";
	string AGGSF = "4 ----------------- AGG-SF\n";
	string AGEUN = "5 ----------------- AGE-UN\n";
	string AGESF = "6 ----------------- AGE-UN\n";
	string AM1 = "7 ----------------- AM-(10,1.0)\n";
	string AM2 = "8 ----------------- AM-(10,0.1)\n";
	string AM3 = "9 ----------------- AM-(10,0.1mej)\n";
	return  errorMessage + COPKM + BL + AGGUN + AGGSF + AGEUN + AGESF + AM1 + AM2 + AM3;
}