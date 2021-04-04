#pragma once

#include <iostream>
#include <sstream>

using namespace std;

extern int dimension;


//Ptins elements of a vector vec
template<typename T>
void printVectorElements(vector<T>& vec){
	for (auto i = 0; i < vec.size(); ++i) {
		cout << vec.at(i) << "; ";
	}
	cout << endl << endl;
}


//Initializas a vector with integers from a to b
void initializeUniformInt(vector<int> & v, int a, int b) {
	if (a > b)
		cout << "a has to be greater than b when creating a uniform int vector" << endl;
	else {
		v.clear();
		for (int i = a; i < b; i++)
			v.push_back(i);
	}
}


//Calculates standard distance between a and b
float calculateDistance(const vector<float>& a, const vector<float>& b) {
	float sum = 0;
	for (int c = 0; c < dimension; c++) {
		sum += pow(a[c] - b[c], 2.0);
	}

	return sqrt(sum);
}


//Produces a string with a_value as base number and n decimal numbers precition
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}