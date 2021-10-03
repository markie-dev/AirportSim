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
    string row1, row2, row3, row4, row5, row6, row7, row8, label;
    tile *temp;
    pollution = 0;
    population = 0;
    x=0;

    fin.open(regionMap);
}

void tiles::prtlist(){
 
}

void tiles::regionPrint(){

}

void tiles::cleanup(){

}
