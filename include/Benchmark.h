#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "CSV.h"
#include "COPKM.h"
#include "BL.h"

using namespace std;

extern vector<vector<float>> g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int>> restrictionsList;
extern int dimension;
extern int K;
extern float lambda;


int benchmark() {
	int iters = 100;
	int seed = 4, nexe = 5, estadisticos = 4;
	string points_file, restrictions_file;
	string fileName;
	vector<float> result_COPKM, result_BL, media_COPKM_10(4, 0), media_BL_10(4, 0), media_COPKM_20(4, 0), media_BL_20(4, 0);
	string string_Media_COPKM_10, string_Media_BL_10, string_Media_COPKM_20, string_Media_BL_20;;
	//string COPKM_10 = ";;;; Resultados obtenidos por el algoritmo COPKM en el PAR con 10 % de restricciones;;;;;;;;";
	//string COPKM_20 = ";;;; Resultados obtenidos por el algoritmo COPKM en el PAR con 20 % de restricciones;;;;;;;;";
	//string BL_10 = ";;;; Resultados obtenidos por el algoritmo BL en el PAR con 10 % de restricciones;;;;;;;;";
	//string BL_20 = ";;;; Resultados obtenidos por el algoritmo BL en el PAR con 10 % de restricciones;;;;;;;;";
	string dataset = ";Zoo;;;;Glass;;;;Bupa;;;";
	string headers = ";Infeasable;Error_Dist;Aggregate;Time;Infeasable;Error_Dist;Aggregate;Time;Infeasable;Error_Dist;Aggregate;Time";
	vector<string> table_COPKM_10(5, "Ejecucion"), table_BL_10(5, "Ejecucion"), table_COPKM_20(5, "Ejecucion"), table_BL_20(5, "Ejecucion");
	
	for (int i = 0; i < nexe; i++) {
		table_COPKM_10[i] += " " + to_string(i+1);
		table_COPKM_20[i] += " " + to_string(i+1);
		table_BL_10[i] += " " + to_string(i+1);
		table_BL_20[i] += " " + to_string(i+1);
	}


	//zoo_10
	points_file = "zoo";
	restrictions_file = "10";
	if (readData(points_file, restrictions_file) == 1)
		return 1;
	for (int i = 0; i < nexe; i++) {
		result_COPKM = COPKM(i + seed, iters);
		result_BL = BL(i + seed, iters);
		table_COPKM_10[i] += outpputToString(result_COPKM);
		table_BL_10[i] += outpputToString(result_BL);
		for (int j = 0; j < estadisticos; j++) {
			media_COPKM_10[j] += result_COPKM[j]/nexe;
			media_BL_10[j] += result_BL[j]/nexe;
		}
	}
	string_Media_COPKM_10 += outpputToString(media_COPKM_10);
	string_Media_BL_10 += outpputToString(media_BL_10);
	fill(media_COPKM_10.begin(), media_COPKM_10.end(), 0);
	fill(media_BL_10.begin(), media_BL_10.end(), 0);


	//zoo_20
	restrictions_file = "20";
	if (readData(points_file, restrictions_file) == 1)
		return 1;
	for (int i = 0; i < nexe; i++) {
		result_COPKM = COPKM(i + seed, iters);
		result_BL = BL(i + seed, iters);
		table_COPKM_20[i] += outpputToString(result_COPKM);
		table_BL_20[i] += outpputToString(result_BL);
		for (int j = 0; j < estadisticos; j++) {
			media_COPKM_20[j] += result_COPKM[j] / nexe;
			media_BL_20[j] += result_BL[j] / nexe;
		}
	}
	string_Media_COPKM_20 += outpputToString(media_COPKM_20);
	string_Media_BL_20 += outpputToString(media_BL_20);
	fill(media_COPKM_20.begin(), media_COPKM_20.end(), 0);
	fill(media_BL_20.begin(), media_BL_20.end(), 0);



	//glass_10
	points_file = "glass";
	restrictions_file = "10";
	if (readData(points_file, restrictions_file) == 1)
		return 1;
	for (int i = 0; i < nexe; i++) {
		result_COPKM = COPKM(i + seed, iters);
		result_BL = BL(i + seed, iters);
		table_COPKM_10[i] += outpputToString(result_COPKM);
		table_BL_10[i] += outpputToString(result_BL);
		for (int j = 0; j < estadisticos; j++) {
			media_COPKM_10[j] += result_COPKM[j] / nexe;
			media_BL_10[j] += result_BL[j] / nexe;
		}
	}
	string_Media_COPKM_10 += outpputToString(media_COPKM_10);
	string_Media_BL_10 += outpputToString(media_BL_10);
	fill(media_COPKM_10.begin(), media_COPKM_10.end(), 0);
	fill(media_BL_10.begin(), media_BL_10.end(), 0);


	//glass_20
	restrictions_file = "20";
	if (readData(points_file, restrictions_file) == 1)
		return 1;
	for (int i = 0; i < nexe; i++) {
		result_COPKM = COPKM(i + seed, iters);
		result_BL = BL(i + seed, iters);
		table_COPKM_20[i] += outpputToString(result_COPKM);
		table_BL_20[i] += outpputToString(result_BL);
		for (int j = 0; j < estadisticos; j++) {
			media_COPKM_20[j] += result_COPKM[j] / nexe;
			media_BL_20[j] += result_BL[j] / nexe;
		}
	}
	string_Media_COPKM_20 += outpputToString(media_COPKM_20);
	string_Media_BL_20 += outpputToString(media_BL_20);
	fill(media_COPKM_20.begin(), media_COPKM_20.end(), 0);
	fill(media_BL_20.begin(), media_BL_20.end(), 0);



	//bupa_10
	points_file = "bupa";
	restrictions_file = "10";
	if (readData(points_file, restrictions_file) == 1)
		return 1;
	for (int i = 0; i < nexe; i++) {
		result_COPKM = COPKM(i + seed, iters);
		result_BL = BL(i + seed, iters);
		table_COPKM_10[i] += outpputToString(result_COPKM);
		table_BL_10[i] += outpputToString(result_BL);
		for (int j = 0; j < estadisticos; j++) {
			media_COPKM_10[j] += result_COPKM[j] / nexe;
			media_BL_10[j] += result_BL[j] / nexe;
		}
	}
	string_Media_COPKM_10 += outpputToString(media_COPKM_10);
	string_Media_BL_10 += outpputToString(media_BL_10);
	fill(media_COPKM_10.begin(), media_COPKM_10.end(), 0);
	fill(media_BL_10.begin(), media_BL_10.end(), 0);


	//bupa_20
	restrictions_file = "20";
	if (readData(points_file, restrictions_file) == 1)
		return 1;
	for (int i = 0; i < nexe; i++) {
		result_COPKM = COPKM(i + seed, iters);
		result_BL = BL(i + seed, iters);
		table_COPKM_20[i] += outpputToString(result_COPKM);
		table_BL_20[i] += outpputToString(result_BL);
		for (int j = 0; j < estadisticos; j++) {
			media_COPKM_20[j] += result_COPKM[j] / nexe;
			media_BL_20[j] += result_BL[j] / nexe;
		}
	}
	string_Media_COPKM_20 += outpputToString(media_COPKM_20);
	string_Media_BL_20 += outpputToString(media_BL_20);
	fill(media_COPKM_20.begin(), media_COPKM_20.end(), 0);
	fill(media_BL_20.begin(), media_BL_20.end(), 0);



	//Printing charts
	ofstream myfile;

	//Chart for COPKM_10
	fileName = ".\\results\\COPKM_10.csv";
	myfile.open(fileName);
	myfile << dataset << endl;
	myfile << headers << endl;
	for (int i = 0; i < nexe; i++)
		myfile << table_COPKM_10[i] << endl;
	myfile << "Media" + string_Media_COPKM_10 << endl;
	myfile.close();

	//Chart for COPKM_20
	fileName = ".\\results\\COPKM_20.csv";
	myfile.open(fileName);
	myfile << dataset << endl;
	myfile << headers << endl;
	for (int i = 0; i < nexe; i++)
		myfile << table_COPKM_20[i] << endl;
	myfile << "Media" + string_Media_COPKM_20 << endl;
	myfile.close();

	//Chart for BL_10
	fileName = ".\\results\\BL_10.csv";
	myfile.open(fileName);
	myfile << dataset << endl;
	myfile << headers << endl;
	for (int i = 0; i < nexe; i++)
		myfile << table_BL_10[i] << endl;
	myfile << "Media" + string_Media_BL_10 << endl;
	myfile.close();

	//Chart for BL_20
	fileName = ".\\results\\BL_20.csv";
	myfile.open(fileName);
	myfile << dataset << endl;
	myfile << headers << endl;
	for (int i = 0; i < nexe; i++)
		myfile << table_BL_20[i] << endl;
	myfile << "Media" + string_Media_BL_20 << endl;
	myfile.close();


	//Chart for global 10%
	fileName = ".\\results\\Golbal_10.csv";
	myfile.open(fileName);
	myfile << dataset << endl;
	myfile << headers << endl;
	myfile << "COPKM" + string_Media_COPKM_10 << endl;
	myfile << "BL" + string_Media_BL_10 << endl;
	myfile.close();


	//Chart for global 20%
	fileName = ".\\results\\Golbal_20.csv";
	myfile.open(fileName);
	myfile << dataset << endl;
	myfile << headers << endl;
	myfile << "COPKM" + string_Media_COPKM_20 << endl;
	myfile << "BL" + string_Media_BL_20 << endl;
	myfile.close();


	return 0;
}