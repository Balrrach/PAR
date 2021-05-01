#include "benchmark.h"

using namespace std;


void operate(int nexe, int estadisticos,
	vector<float>& result_COPKM, vector<float>& result_BL,
	vector<string>& table_COPKM, vector<string>& table_BL,
	vector<float>& media_COPKM, vector<float>& media_BL,
	string& string_Media_COPKM, string& string_Media_BL)
{
	(new ExecutionParameters())->initialize();
	(new ExecutionParameters())->seed -= 1;

	for (int i = 0; i < nexe; i++) {
		(new ExecutionParameters())->seed += 1;

		result_COPKM = (new COPKM)->executeCOPKM();
		result_BL = (new BL)->executeBL();

		table_COPKM[i] += outputToString(result_COPKM);
		table_BL[i] += outputToString(result_BL);

		for (int j = 0; j < estadisticos; j++) {
			media_COPKM[j] += result_COPKM[j] / nexe;
			media_BL[j] += result_BL[j] / nexe;
		}
	}

	string_Media_COPKM += outputToString(media_COPKM);
	string_Media_BL += outputToString(media_BL);
	fill(media_COPKM.begin(), media_COPKM.end(), 0);
	fill(media_BL.begin(), media_BL.end(), 0);
}


int benchmark() {
	int nexe = 5, estadisticos = 4;
	string points_file, restrictions_file;
	string fileName;
	vector<float> result_COPKM, result_BL, media_COPKM_10(4, 0), media_BL_10(4, 0), media_COPKM_20(4, 0), media_BL_20(4, 0);
	string string_Media_COPKM_10, string_Media_BL_10, string_Media_COPKM_20, string_Media_BL_20;
	//string dataset = ",Zoo,,,,Glass,,,,Bupa,,,";
	string headers = ",Inf,Error,Fitness,Time,Inf,Error,Fitness,Time,Inf,Error,Fitness,Time";
	vector<string> table_COPKM_10(5, "Exe"), table_BL_10(5, "Exe"), table_COPKM_20(5, "Exe"), table_BL_20(5, "Exe");
	string path = "..\\results\\";

	for (int i = 0; i < nexe; i++) {
		table_COPKM_10[i] += " " + to_string(i + 1);
		table_COPKM_20[i] += " " + to_string(i + 1);
		table_BL_10[i] += " " + to_string(i + 1);
		table_BL_20[i] += " " + to_string(i + 1);
	}


	//zoo_10
	points_file = "zoo";
	restrictions_file = "10";
	readData(points_file, restrictions_file);
	operate(nexe, estadisticos, result_COPKM, result_BL, table_COPKM_10, table_BL_10,
		media_COPKM_10, media_BL_10, string_Media_COPKM_10, string_Media_BL_10);


	//zoo_20
	restrictions_file = "20";
	readData(points_file, restrictions_file);
	operate(nexe, estadisticos, result_COPKM, result_BL, table_COPKM_20, table_BL_20,
		media_COPKM_20, media_BL_20, string_Media_COPKM_20, string_Media_BL_20);



	//glass_10
	points_file = "glass";
	restrictions_file = "10";
	readData(points_file, restrictions_file);
	operate(nexe, estadisticos, result_COPKM, result_BL, table_COPKM_10, table_BL_10,
		media_COPKM_10, media_BL_10, string_Media_COPKM_10, string_Media_BL_10);


	//glass_20
	restrictions_file = "20";
	readData(points_file, restrictions_file);
	operate(nexe, estadisticos, result_COPKM, result_BL, table_COPKM_20, table_BL_20,
		media_COPKM_20, media_BL_20, string_Media_COPKM_20, string_Media_BL_20);



	//bupa_10
	points_file = "bupa";
	restrictions_file = "10";
	readData(points_file, restrictions_file);
	operate(nexe, estadisticos, result_COPKM, result_BL, table_COPKM_10, table_BL_10,
		media_COPKM_10, media_BL_10, string_Media_COPKM_10, string_Media_BL_10);


	//bupa_20
	restrictions_file = "20";
	readData(points_file, restrictions_file);
	operate(nexe, estadisticos, result_COPKM, result_BL, table_COPKM_20, table_BL_20,
		media_COPKM_20, media_BL_20, string_Media_COPKM_20, string_Media_BL_20);




	//Chart for COPKM_10
	fileName = path + "COPKM_10.csv";
	writeOutput(fileName, headers, nexe, table_COPKM_10, string_Media_COPKM_10);

	//Chart for COPKM_20
	fileName = path + "COPKM_20.csv";
	writeOutput(fileName, headers, nexe, table_COPKM_20, string_Media_COPKM_20);

	//Chart for BL_10
	fileName = path + "BL_10.csv";
	writeOutput(fileName, headers, nexe, table_BL_10, string_Media_BL_10);

	//Chart for BL_20
	fileName = path + "BL_20.csv";
	writeOutput(fileName, headers, nexe, table_BL_20, string_Media_BL_20);



	//Global results
	ofstream myfile;

	//Chart for global 10%
	fileName = path + "Global_10.csv";
	myfile.open(fileName);
	//myfile << dataset << endl;
	myfile << headers << endl;
	myfile << "COPKM" + string_Media_COPKM_10 << endl;
	myfile << "BL" + string_Media_BL_10 << endl;
	myfile.close();

	//Chart for global 20%
	fileName = path + "Global_20.csv";
	myfile.open(fileName);
	//myfile << dataset << endl;
	myfile << headers << endl;
	myfile << "COPKM" + string_Media_COPKM_20 << endl;
	myfile << "BL" + string_Media_BL_20 << endl;
	myfile.close();


	return 0;
}