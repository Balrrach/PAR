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
	for (int c = 0; c < a.size(); c++)
		sum += (a[c] - b[c]) * (a[c] - b[c]);

	return sqrtf(sum);
}


void fillWithRandom(std::vector<int> & randomVector, int K)
{
	for (int & i : randomVector)
		i = Randint(0, K-1);
}