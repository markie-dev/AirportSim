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
    getline(fin, row1);

   // cout << row1;
    stringstream s(row1);

    while (getline(s, label, ',')) {
        y=0;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }

    x=0;

    getline(fin, row2);
    stringstream s2(row2);
    while (getline(s2, label, ',')) {
        y=1;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
    x=0;

    getline(fin, row3);
    stringstream s3(row3);
    while (getline(s3, label, ',')) {
        y=2;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
    x=0;

    getline(fin, row4);
    stringstream s4(row4);
    while (getline(s4, label, ',')) {
        y=3;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
    x=0;

    getline(fin, row5);
    stringstream s5(row5);
    while (getline(s5, label, ',')) {
        y=4;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
    x=0;

    getline(fin, row6);
    stringstream s6(row6);
    while (getline(s6, label, ',')) {
        y=5;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
    x=0;

    getline(fin, row7);
    stringstream s7(row7);
    while (getline(s7, label, ',')) {
        y=6;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
    x=0;

    getline(fin, row8);
    stringstream s8(row8);
    while (getline(s8, label, ',')) {
        y=7;
        temp = new tile(label, x, y, pollution, population);
        tileList.push_back(temp);
        ++x;
    }
}

void tiles::prtlist(){
 
    tile *temp;
    string label;
    int x, y;
    cout << "\nTILE LIST" << endl;
    cout << endl;
    
    for (auto it = tileList.begin(); it !=tileList.end(); ++it){
        temp = *it;
        label=temp->getLabel();
        x=temp->getXCoord();
        y=temp->getYCoord();
        cout << "Label: " << label << " " << "Coordinates: " << x << ", " << y << endl << endl;
    }
}

void tiles::regionPrint(){
    tile *temp;
    cout << "------------------" << endl; cout << "|";
    for (int i = 0; i < 7; i++) {
        cout << tileList[i]->getLabel() << " ";
    }
    cout << "  |" << endl;
    for (int i = 7; i < 15; i++) {
        cout << tileList[i]->getLabel() << " ";
    }
    cout << endl;
    /*
    for (int i = 0; i < tileList.size(); i++){
        if(tileList[i]->getYCoord() == 0){
            cout << tileList[i]->getLabel() << " ";
        }
    }
    */
    for (int i = 15; i < 25; i++) {
        cout << tileList[i]->getLabel() << " ";
    }
    cout << endl;
    for (int i = 25; i < 33; i++) {
        cout << tileList[i]->getLabel() << " ";
    }
    cout << endl;
}

void tiles::cleanup(){
    for (auto it = tileList.begin(); it !=tileList.end(); ++it){
        delete *it;
    }
    tileList.clear();
}
