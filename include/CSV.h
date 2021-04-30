#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

#include "Cluster.h"
#include "PAR.h"
#include "utilities.h"


/*
Funcion encargada de convertir una cadena en la misma cadena
sustituyendo el caracter dado por c por un espacio. Parametros:
	s: Cadena base
	c: Caracter a sustituir por un espacio
	v: Cadena resultante
*/
void split(const std::string& s, char c, std::vector<std::string>& v);

//Reads points coordenates from a file
void readPoints(std::ifstream& pointsFile);

//Opens a file and handles exceptions
std::ifstream openFile(const std::string& filename);

//Reads point data from a file in CSV format
void fetchPoints(const std::string& pointsPath);

//Reads restrictions data from a file in CSV format
int fetchRestrictions(std::string restrictionsPath);

//Turns output data into an string
std::string outputToString(std::vector<float> results);

//Writes the results of a given algorithm and dataset to a given file
void writeOutput(const std::string& fileName, const std::string& headers, int nexe, const std::vector<std::string>& table, const std::string& string_Media);

//Writes the clusters coordenates
void toBoxplot(const std::vector<Cluster>& clusters);