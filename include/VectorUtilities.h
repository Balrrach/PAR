#pragma once

#include <iostream>

using namespace std;


template<typename T>
void printVectorElements(vector<T>& vec){
	for (auto i = 0; i < vec.size(); ++i) {
		cout << vec.at(i) << "; ";
	}
	cout << endl << endl;
}

void initializeUniformInt(vector<int> & v, int a, int b) {
	if (a > b)
		cout << "a has to be greater than b when creating a uniform int vector" << endl;
	else {
		v.clear();
		for (int i = a; i < b; i++)
			v.push_back(i);
	}
}