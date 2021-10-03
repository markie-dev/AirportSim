#include "readin.h"
using namespace std;

void readConfig(int *a, int *b, string *c) {
    ifstream fin;
    string filename, dontcare, regionMap;
    int timeLimit, refreshRate;

    cout << "Beginning simulation...\n";
    cout << "Config File Name: "; cin >> filename;

    fin.open(filename);

    getline(fin, dontcare, ':');
    fin >> regionMap;

    getline(fin, dontcare, ':');
    fin >> timeLimit;

    getline(fin, dontcare, ':');
    fin >> refreshRate;

    *a = timeLimit;
    *b = refreshRate;
    *c = regionMap;
    
    fin.close();
}