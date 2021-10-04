#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include "tiles.h"
using namespace std;

int tiles::getCnt() { return tilecnt;}

void tiles::cntInc() {tilecnt++;}
void tiles::cntDec() {tilecnt--;}

void tiles::loadTiles(string regionMap) {
    ifstream fin;
    int x, y, pollution, population;
    string row1, row2, row3, row4, row5, row6, row7, row8, label, word;
    pollution = 0;
    population = 0;
    x=0;
    y=0;

    fin.open(regionMap);

    getline(fin, row1);
    stringstream s(row1);
    while (getline(s, label, ',')) {
        cout << word << endl;
        tile newTile(label, x, y, pollution, population);
        tileList.push_back(newTile);
        x++;
    }
}

void tiles::prtlist(){
 
}

void tiles::regionPrint(){
    for (int i=0;i<tileList.size();i++){
        cout << "Label: " << tileList[i].getLabel() << " Coordinates: " << tileList[i].getXCoord() << ", " << tileList[i].getYCoord() << endl;
    }
}

void tiles::cleanup(){

}
