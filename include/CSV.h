#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

extern vector<vector<float> > g_points;
extern map<int, vector <pair<int, int> > > restrictionsMap;
extern vector<vector<int> > restrictionsList;
extern int dimension;
extern int K;


/*
Funcion encargada de convertir una cadena en la misma cadena
sustituyendo el caracter dado por c por un espacio. Parametros:
    s: Cadena base
    c: Caracter a sustituir por un espacio
    v: Cadena resultante
*/
void split(const string& s, char c, vector<string>& v) {
    int i = 0;
    int j = s.find(c);

    while (j >= 0) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j < 0) {
            v.push_back(s.substr(i, s.length()));
        }
    }
}


int fetchPoints(string filename) {

    //Open file for fetching points
    cout << "Filename: " << filename << endl;
    ifstream infile(filename.c_str());

    if (!infile.is_open()) {
        return 1;
    }

    int pointId = 0;
    vector<string> aux;
    vector<float> coordenates;
    string line;

    while (getline(infile, line)) {
        aux.clear();
        coordenates.clear();

        split(line, ',', aux);
        for (unsigned int i = 0; i < aux.size(); i++) {
            coordenates.push_back(stof(aux[i]));
        }
        g_points.push_back(coordenates);

        /*
        cout << "Punto: ";
        for (unsigned int i = 0; i < aux.size(); i++) {
            cout << coordenates[i] << " ";
        }
        cout << endl;
        */
    }

    cout << "Number of points: " << g_points.size() << endl;
    infile.close();

    dimension = g_points[0].size();

    return 0;
}


int fetchRestrictions(string filename) {
    //Open file for fetching restrictions
    cout << "Filename: " << filename << endl;
    ifstream infile(filename.c_str());

    if (!infile.is_open()) {
        return 1;
    }

    //Fetching restrictions from file
    string line;
    vector<string> aux;
    int i = 0;

    while (getline(infile, line)) {
        aux.clear();
        split(line, ',', aux);

        for (int j = 0; j < aux.size(); j++) {
            if (i < j) {
                if (stoi(aux[j]) == -1)
                    restrictionsList.push_back(vector<int>{-1, i, j});
                if (stoi(aux[j]) == 1)
                    restrictionsList.push_back(vector<int>{1, i, j});
            }
            if (i != j) {
                if (stoi(aux[j]) == -1)
                    restrictionsMap[i].push_back(pair<int, int>{-1, j});
                if (stoi(aux[j]) == 1)
                    restrictionsMap[i].push_back(pair<int, int>{1, j});
            }
        }

        i++;
    }
    infile.close();

    cout << "Number of restrictions: " << restrictionsList.size() << endl;
    
    /*
    int k = 0, l = 0;
    for (int c = 0; c < restrictionsList.size(); c++) {
        if (restrictionsList[c][2] == -1) {
            cout << "Restriccion CL numero " << i << " : (" << restrictionsList[c][0] << " , " << restrictionsList[c][1] << ")" << endl;
            k++;
        }
        if (restrictionsList[c][2] == 1) {
            cout << "Restriccion ML numero " << i << " : (" << restrictionsList[c][0] << " , " << restrictionsList[c][1] << ")" << endl;
            l++;
        }
    }

    cout << endl;

    for (int i = 0; i < g_points.size(); i++)
        for (int j = 0; j < restrictionsMap[i].size(); j++)
            cout << "Restriccion " << j << " asociada al punto " << i << " de tipo " << restrictionsMap[i][j].first << " pareja: " << restrictionsMap[i][j].second << endl;
    */

    return 0;
}


int readData(const string& points_file, const string& restrictions_file) {
    if (points_file == "zoo") {
        K = 7;
        if (fetchPoints(".\\datos\\zoo_set.dat") == 0)
            cout << "Points fetched successfully!" << endl << endl;
        else {
            cout << "Error: Failed to open points file" << endl;
            return 1;
        }

        if (restrictions_file == to_string(10)) {
            if (fetchRestrictions(".\\datos\\zoo_set_const_10.const") == 0)
                cout << "Restrictions fetched successfully!" << endl << endl;
            else {
                cout << "Error: Failed to open restrictions file" << endl;
                return 1;
            }
        }

        else if (restrictions_file == to_string(20)) {
            if (fetchRestrictions(".\\datos\\zoo_set_const_20.const") == 0)
                cout << "Restrictions fetched successfully!" << endl << endl;
            else {
                cout << "Error: Failed to open restrictions file" << endl;
                return 1;
            }
        }

        else {
            cout << "Error: Wrong percentage of restrictions" << endl;
            return 1;
        }
    }


    else if (points_file == "glass") {
        K = 7;
        if (fetchPoints(".\\datos\\glass_set.dat") == 0)
            cout << "Points fetched successfully!" << endl << endl;
        else {
            cout << "Error: Failed to open points file" << endl;
            return 1;
        }

        if (restrictions_file == to_string(10)) {
            if (fetchRestrictions(".\\datos\\glass_set_const_10.const") == 0)
                cout << "Restrictions fetched successfully!" << endl << endl;
            else {
                cout << "Error: Failed to open restrictions file" << endl;
                return 1;
            }
        }

        else if (restrictions_file == to_string(20)) {
            if (fetchRestrictions(".\\datos\\glass_set_const_20.const") == 0)
                cout << "Restrictions fetched successfully!" << endl << endl;
            else {
                cout << "Error: Failed to open restrictions file" << endl;
                return 1;
            }
        }

        else {
            cout << "Error: Wrong percentage of restrictions" << endl;
            return 1;
        }
    }


    else if (points_file == "bupa") {
        K = 16;
        if (fetchPoints(".\\datos\\bupa_set.dat") == 0)
            cout << "Points fetched successfully!" << endl << endl;
        else {
            cout << "Error: Failed to open points file" << endl;
            return 1;
        }

        if (restrictions_file == to_string(10)) {
            if (fetchRestrictions(".\\datos\\bupa_set_const_10.const") == 0)
                cout << "Restrictions fetched successfully!" << endl << endl;
            else {
                cout << "Error: Failed to open restrictions file" << endl;
                return 1;
            }
        }

        else if (restrictions_file == to_string(20)) {
            if (fetchRestrictions(".\\datos\\bupa_set_const_20.const") == 0)
                cout << "Restrictions fetched successfully!" << endl << endl;
            else {
                cout << "Error: Failed to open restrictions file" << endl;
                return 1;
            }
        }

        else {
            cout << "Error: Wrong percentage of restrictions" << endl;
            return 1;
        }
    }


    else {
        cout << "Error: Wrong file" << endl << endl;
        return 1;
    }

    //Return if number of clusters > number of points
    if (g_points.size() < K) {
        cout << "Error: Number of clusters greater than number of points" << endl;
        return 1;
    }

    return 0;
}