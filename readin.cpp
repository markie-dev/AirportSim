#include "readin.h"
using namespace std;

//Read in Configuration File function
void readConfig(int *a, int *b, string *c) {
    ifstream fin;
    string filename, dontcare, regionMap;
    int timeLimit, refreshRate;

    cout << "Beginning simulation...\n" << "Config File Name: ";

    //verify filename is correct
    while (true){
        cin >> filename;
            fin.open(filename);
    if (fin) break;
        cout << "\nInvalid filename. Please enter a valid input file. \n" << "Config File Name: ";
    }

    //discard text before the colon
    getline(fin, dontcare, ':');
    //input regionMap filename from file
    fin >> regionMap;

    getline(fin, dontcare, ':');
    fin >> timeLimit;

    getline(fin, dontcare, ':');
    fin >> refreshRate;

    //assign pointers to variables to pass into main()
    *a = timeLimit;
    *b = refreshRate;
    *c = regionMap;
    
    fin.close();
}