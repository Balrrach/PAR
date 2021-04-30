#include "utilities.h"

using namespace std;


void initializeUniformInt(vector<int>& v, int a, int b) {
	if (a > b)
		cout << "a has to be greater than b when creating a uniform int vector" << endl;
	else {
		v.clear();
		for (int i = a; i < b; i++)
			v.push_back(i);
	}
}


float calculateDistance(const vector<float>& a, const vector<float>& b) {
	float sum = 0;
	for (int c = 0; c < a.size(); c++) {
		sum += pow(a[c] - b[c], 2.0);
	}

	return sqrt(sum);
}