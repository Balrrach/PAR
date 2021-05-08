#include "benchmark.h"

using namespace std;


void algortimExecution(int argc, char ** argv)
{
	//Need 3 arguments (Points file, Restrictions file, Number of Clusters) to run, else exit
	if (argc < 4)
		throw "Error: command-line argument count mismatch";

	//Update the seed
	if (argc == 5)
		(new ExecutionParameters())->seed = atoi(argv[4]);

	//Fetching data from files
	string points_file = argv[1];
	string restrictions_file = argv[2];
	readData(points_file, restrictions_file);
	algorithmSelection(argv[3]);
}


void benchmarkExecution(int argc, char ** argv)
{
	switch (argc) {
	case 3:
		benchmarkSelector(stoi(argv[2]));
		break;

	case 4:
		(new ExecutionParameters())->seed = atoi(argv[3]);
		benchmarkSelector(stoi(argv[2]));
		break;

	default:
		cout << "No benchmark specified";
		throw "Error: command-line argument mismatch";
		break;
	}
}


void uniqueBenchmarkExecution(int argc, char ** argv)
{
	switch (argc) {
	case 3:
		benchmark(argv[2]);
		break;

	case 4:
		(new ExecutionParameters())->seed = atoi(argv[3]);
		benchmark(argv[2]);
		break;

	default:
		cout << "No benchmark specified";
		throw "Error: command-line argument mismatch";
		break;
	}
}


void benchmarkSelector(int number)
{
	switch (number) {
	case 1:
		p1Benchmark();
		break;

	case 2:
		p2Benchmark();
		break;

	default:
		cout << "Wrong benchmark specification";
		throw "Error: command-line argument mismatch";
		break;
	}
}



//Benchmark Practica 1
void p1Benchmark()
{
	benchmark("COPKM");
	benchmark("BL");
}


//Benchmark Practica 2
void p2Benchmark()
{
	benchmark("AGG-UN");
	benchmark("AGG-SF");
	benchmark("AGE-UN");
	benchmark("AGE-SF");
	benchmark("AM-P");
	benchmark("AM-C");
	benchmark("AM-M");
}



//Benchmark execution
void benchmark(string algorithm)
{
	int nexe = 5, estadisticos = 4;
	string points_file, restrictions_file, fileName;
	vector<float> result, media_10(4, 0), media_20(4, 0);
	string string_Media_10, string_Media_20;
	//string dataset = ",Zoo,,,,Glass,,,,Bupa,,,";
	string headers = ",Inf,GDeviation,Fitness,Time,Inf,GDeviation,Fitness,Time,Inf,GDeviation,Fitness,Time";
	vector<string> table_10(5, "Exe"), table_20(5, "Exe");
	string path = "..\\results\\";

	for (int i = 0; i < nexe; i++) {
		table_10[i] += " " + to_string(i + 1);
		table_20[i] += " " + to_string(i + 1);
	}


	//zoo_10
	points_file = "zoo";
	restrictions_file = "10";
	readData(points_file, restrictions_file);
	operate(algorithm, nexe, estadisticos, result, table_10, media_10, string_Media_10);

	//zoo_20
	restrictions_file = "20";
	readData(points_file, restrictions_file);
	operate(algorithm, nexe, estadisticos, result, table_20, media_20, string_Media_20);



	//glass_10
	points_file = "glass";
	restrictions_file = "10";
	readData(points_file, restrictions_file);
	operate(algorithm, nexe, estadisticos, result, table_10, media_10, string_Media_10);


	//glass_20
	restrictions_file = "20";
	readData(points_file, restrictions_file);
	operate(algorithm, nexe, estadisticos, result, table_20, media_20, string_Media_20);



	//bupa_10
	points_file = "bupa";
	restrictions_file = "10";
	readData(points_file, restrictions_file);
	operate(algorithm, nexe, estadisticos, result, table_10, media_10, string_Media_10);


	//bupa_20
	restrictions_file = "20";
	readData(points_file, restrictions_file);
	operate(algorithm, nexe, estadisticos, result, table_20, media_20, string_Media_20);



	//Chart for 10% restrictions
	fileName = path + algorithm + "_10.csv";
	writeOutput(fileName, headers, nexe, table_10, string_Media_10);

	//Chart for 20% restrictions
	fileName = path + algorithm+ "_20.csv";
	writeOutput(fileName, headers, nexe, table_20, string_Media_20);
}


void operate(string algoritmo, int nexe, int estadisticos,
	vector<float> & result, vector<string> & table,
	vector<float> & media, string & string_Media)
{
	(new ExecutionParameters())->initialize();
	(new ExecutionParameters())->seed -= 1;

	for (int i = 0; i < nexe; i++) {
		(new ExecutionParameters())->seed += 1;

		result = algorithmSelection(algoritmo);
		table[i] += outputToString(result);

		for (int j = 0; j < estadisticos; j++) {
			media[j] += (float)result[j] / (float)nexe;
		}
	}

	string_Media += outputToString(media);
	fill(media.begin(), media.end(), 0);
}



vector<float> algorithmSelection(string algoritm)
{
	if(algoritm == "COPKM")
		return (new COPKM)->execute();

	else if (algoritm == "BL")
		return (new BL)->execute();

	else if (algoritm == "AGG-UN")
		return (new AGGUN)->execute();

	else if (algoritm == "AGG-SF")
		return (new AGGSF)->execute();

	else if (algoritm == "AGE-UN")
		return (new AGEUN)->execute();

	else if (algoritm == "AGE-SF")
		return (new AGESF)->execute();

	else if (algoritm == "AM-C")
		return (new AMC)->execute();

	else if (algoritm == "AM-P")
		return (new AMP)->execute();

	else if (algoritm == "AM-M")
		return (new AMM)->execute();

	else{
		cout << (new ExecutionParameters)->algorithmError();
		throw "Algoritm Selection Error";
	}
}


