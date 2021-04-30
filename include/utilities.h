#pragma once

#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>


//Ptins elements of a vector vec
template<typename T>
void printVectorElements(std::vector<T>& vec) {
	for (auto i = 0; i < vec.size(); ++i) {
		std::cout << vec.at(i) << "; ";
	}
	std::cout << std::endl << std::endl;
}

//Initializas a vector with integers from a to b
void initializeUniformInt(std::vector<int>& v, int a, int b);

//Calculates standard distance between a and b
float calculateDistance(const std::vector<float>& a, const std::vector<float>& b);

template <typename T>
std::string toStringWithPrecision(const T a_value, const int n) {
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}