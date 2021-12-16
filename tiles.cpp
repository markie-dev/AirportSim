#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "tiles.h"
using namespace std;

void removeNewline(string &removeString) {
    if (removeString.size() > 1) {
        for (int i = 0; i < removeString.size(); i++) {
            if (removeString[i] == '\n') { removeString.erase((i), (i+1)); }
        }
    }
}

void tiles::loadTiles(string regionMap) {
    ifstream fin, finLineCnt;
    int x, y, pollution = 0, population = 0, lineCnt=0;
    string row, label, throwaway;
    string test;

    //Verify filename is valid
    while (true){
            fin.open(regionMap);
            finLineCnt.open(regionMap);
    if (fin) break;
        cout << "\nRegion Layout file not found. Please make sure the .csv file is in this directory. \n";
        exit(1);
    }

    //count number of lines in file
    while (getline(finLineCnt, throwaway) ){
        ++lineCnt;
    }

    //get line and push each character to its own tile
    for (int i=0;i<lineCnt;i++){
        x=0;
        y=i;

        //store each line in "row"
        getline(fin, row, '\r');
        //seperate "row" into spaces and letters
        stringstream s(row);
        
        //Adds a row to the vector for each pass of the loop
        tileList.push_back( vector<tile>() );

        //create base tile object and push to vector "tileList"
        while (getline(s, label, ',')) {
            removeNewline(label); //Removes all newlines in the string
            tile newTile(label, x, y, pollution, population);
            tileList[i].push_back(newTile); // Push back causing stack dump
            x++;    //move x coordniate along row
            }
    }

    //close streams used
    fin.close();
    finLineCnt.close();
}

void tiles::regionPrint() {
    // calculate length of dashes to match the length of the vector
    string dash64 = "---------------", dash110 = "---------------------", dash = dash64;
    if  (tileList.size() > 8){
        dash = dash110;
    }
    //print region
    cout << dash << endl;
    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
                 if (tileList[i][j].getPopulation() == 0){  //if tile has a population of 0
                    cout << tileList[i][j].getLabel() << " ";   //display Label
                 }else{     //else
                    cout << tileList[i][j].getPopulation() << " ";  //display population
                 }
        }
        cout << endl;
    }
    cout << dash << endl;
}

int tiles::updateWorkers(){
    int pop=0, finalPop=0;
    //For loop to iterate through vector
    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
           if((tileList[i][j].getLabel() == "D") && (tileList[i][j].getPopulation()) > 0 ){ //if tile is Domestic
               finalPop+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getLabel() == "C") && (tileList[i][j].getPopulation()) > 0 ){ //if tile is Cargo
               finalPop-=(tileList[i][j].getPopulation());
           }
           if((tileList[i][j].getLabel() == "I") && (tileList[i][j].getPopulation()) > 0 ){ //if tile is International
               finalPop-=tileList[i][j].getPopulation();
           }
        }
    }
    return finalPop;
}

int tiles::updateGoods(){
    int finalGoods=0;
    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
           if((tileList[i][j].getLabel() == "C") && (tileList[i][j].getPopulation()) > 0 ){ //if tile is Cargo
               finalGoods+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getLabel() == "I") && (tileList[i][j].getPopulation()) > 0 ){ //if tile is International
               finalGoods-=tileList[i][j].getPopulation();
           }
        }
    }
    return finalGoods;
}

int avaliableWorkers, avaliableGoods;
bool tiles::runSim(int timeL, int refreshR){
    // calculate length of dashes to match the length of the vector
    string dash64 = "---------------", dash110 = "---------------------", dash = dash64;
    if  (tileList.size() > 8){
        dash = dash110;
    }


int avalWorkers=0, avalGoods=0;
vector< vector<tile> > nextStepTileList(tileList);
    for(int n=1;n < timeL+1; n++){
        updateSim(nextStepTileList);    //update vector list
        avalWorkers = updateWorkers();
        avalGoods = updateGoods();
        avaliableWorkers = avalWorkers; avaliableGoods = avalGoods;
        cout << "\nTime Step: " << n << endl;
        if((avaliableWorkers < 0) || (avaliableGoods < 0)){
            cout << "Available Workers: " << 0 << " Available Goods: " << avaliableGoods << endl <<  dash << endl << dash;
            return false;
        }
        cout << "Available Workers: " << avaliableWorkers << " Available Goods: " << avaliableGoods << endl <<  dash << endl;
        for (int i = 0; i < tileList.size(); i++){
            for (int j = 0; j < tileList[i].size(); j++) {
                if ((n-1) % refreshR == 0){
                 if (tileList[i][j].getPopulation() == 0){  //if tile has a population of 0
                    cout << tileList[i][j].getLabel() << " ";   //display Label
                 }else{     //else
                    cout << tileList[i][j].getPopulation() << " ";  //display population
                 }
                }
            }if(!((n-1) % refreshR == 0)){}else{cout << endl;}  
        }nextStepTileList = tileList;   //Copy to new vector to update
        cout << dash << endl;

    }
    return true;
}

void tiles::updateSim(vector< vector<tile> > nextStepTileList){
    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
            //Domestic Rule 1
            if((tileList[i][j].isAdjPowerline() == true) && (tileList[i][j].getLabel() == "D") && (tileList[i][j].getPopulation() == 0)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 2
            else if((tileList[i][j].getPopulation() == 0) && (tileList[i][j].getLabel() == "D") && (tileList[i][j].checkAdjPopulation(1)) >= 1){
                nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 3
            else if((tileList[i][j].getPopulation() == 1) && (tileList[i][j].getLabel() == "D") && (tileList[i][j].checkAdjPopulation(1)) >= 2){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 4
            else if((tileList[i][j].getPopulation() == 2) && (tileList[i][j].getLabel() == "D") && (tileList[i][j].checkAdjPopulation(2)) >= 4){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 5
            else if((tileList[i][j].getPopulation() == 3) && (tileList[i][j].getLabel() == "D") && (tileList[i][j].checkAdjPopulation(3)) >= 6){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 6
            else if((tileList[i][j].getPopulation() == 4) && (tileList[i][j].getLabel() == "D") && (tileList[i][j].checkAdjPopulation(4)) >= 8){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }
            //Cargo Rule 1
            if((tileList[i][j].isAdjPowerline() == true) && (tileList[i][j].getLabel() == "C") && (tileList[i][j].getPopulation() == 0) && (avaliableWorkers >= 2)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
               nextStepTileList[i][j].setPollution(tileList[i][j].getPollution()+1);
            }//Rule 2
            else if((tileList[i][j].getPopulation() == 0) && (tileList[i][j].getLabel() == "C") && ((tileList[i][j].checkAdjPopulation(1)) >= 1) && (avaliableWorkers >= 2)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
               nextStepTileList[i][j].setPollution(tileList[i][j].getPollution()+1);
            }//Rule 3
            else if((tileList[i][j].getPopulation() == 1) && (tileList[i][j].getLabel() == "C") && ((tileList[i][j].checkAdjPopulation(1)) >= 2) && (avaliableWorkers >= 2)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
               nextStepTileList[i][j].setPollution(tileList[i][j].getPollution()+1);
            }//Rule 4
            else if((tileList[i][j].getPopulation() == 2) && (tileList[i][j].getLabel() == "C") && ((tileList[i][j].checkAdjPopulation(2)) >= 4) && (avaliableWorkers >= 2)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
               nextStepTileList[i][j].setPollution(tileList[i][j].getPollution()+1);
            }
            //International Rule 1
            if((tileList[i][j].isAdjPowerline() == true) && (tileList[i][j].getLabel() == "I") && (tileList[i][j].getPopulation() == 0) && (avaliableWorkers >= 1) && (avaliableGoods >= 1)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 2
            else if((tileList[i][j].getPopulation() == 0) && (tileList[i][j].getLabel() == "I") && ((tileList[i][j].checkAdjPopulation(1)) >= 1) && (avaliableWorkers >= 1) && (avaliableGoods >= 1)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }//Rule 3
            else if((tileList[i][j].getPopulation() == 1) && (tileList[i][j].getLabel() == "I") && ((tileList[i][j].checkAdjPopulation(1)) >= 2) && (avaliableWorkers >= 1) && (avaliableGoods >= 1)){
               nextStepTileList[i][j].setPopulation(tileList[i][j].getPopulation()+1);
            }
        }
    }
    tileList = nextStepTileList;
}

void tiles::printPollutionMap(){
    string dash64 = "---------------", dash110 = "---------------------", dash = dash64;
    if  (tileList.size() > 8){
        dash = dash110;
    }
    vector< vector<tile> > nextStepTileList(tileList);

    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
           if((tileList[i][j].checkAdjPollution(tileList[i][j].getPollution()) == 3)){  //if max adjacent pollution is 3
               nextStepTileList[i][j].setPollution(2);
           }
           if((tileList[i][j].checkAdjPollution(tileList[i][j].getPollution()) == 2)){  //if max adjacent pollution is 2
               nextStepTileList[i][j].setPollution(1);
           }
        }
    }

    tileList = nextStepTileList;    //swap vectors

        for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
           if((tileList[i][j].checkAdjPollution(tileList[i][j].getPollution()) == 2)){  //if max adjacent pollution is 2
               tileList[i][j].setPollution(1);
           }
        }
    }

    //print region
    cout << "\nPollution: ";
    cout << endl << dash << endl;
    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
                    cout << tileList[i][j].getPollution() << " ";   //display Pollution

        }
        cout << endl;
    }
    cout << dash << endl;

    int pollutionTotal=0;
        for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
           if((tileList[i][j].getPollution())>0){
               pollutionTotal+=tileList[i][j].getPollution();   //calculate total population
           }
        }
    }
    cout << "\nThe total pollution in the zone is: " << pollutionTotal << " units\n";
}
string COORDS[4] = {"X1: ", "Y1: ", "X2: ", "Y2: "}; //string array for functions
void tiles::requestedArea(){
    int maxY = tileList.size();
    int maxX = tileList[0].size();
    int input = 0, x1=0, x2=0, y1=0, y2=0;
    int inputCOORDS[4] = {};

    cout << "\nEnter the diagonal corners of the area you wish to have more information about (MinX = 0, MinY = 0, MaxX = " << maxX << ", MaxY = " << maxY << ")" << endl;

   //prompt user for coordinates
   x1=getValidInput(0, maxX, 0);
   y1=getValidInput(0, maxY, 1);
   x2=getValidInput(x1, maxX, 2);
   y2=getValidInput(y1, maxY, 3);
    int DTotal=0, CTotal=0, ITotal=0, pollution=0;

    //calculate correct population for coordinates
        for (int i = y1; i < y2+1; i++){
        for (int j = x1; j < x2+1; j++) {
           if((tileList[i][j].getPopulation())>0 && tileList[i][j].getLabel() == "D"){
               DTotal+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getPopulation())>0 && tileList[i][j].getLabel() == "C"){
               CTotal+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getPopulation())>0 && tileList[i][j].getLabel() == "I"){
               ITotal+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getPollution())>0){
               pollution+=tileList[i][j].getPollution();
           }
        }
    }
    cout << "\nThe total populations for the requested area are:" << endl;
    cout << "Domestic: " << DTotal << endl;
    cout << "Cargo: " << CTotal << endl;
    cout << "International: " << ITotal << endl;

    cout << "\nThe total amount of pollution for the requested area is " << pollution << " units" << endl;
}

//makes sure the useer input is valid
int tiles::getValidInput(int min, int max, int Coords){
    int val;
    do {
        cout << COORDS[Coords]; cin >> val;
    } while (val < min || val > max);
    return val;
}

//print total population based on zone type
void tiles::printPopTotal(){
    int domTotal=0, carTotal=0, intTotal=0; 
    for (int i = 0; i < tileList.size(); i++){
        for (int j = 0; j < tileList[i].size(); j++) {
           if((tileList[i][j].getLabel() == "D") && (tileList[i][j].getPopulation()) > 0 ){
               domTotal+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getLabel() == "C") && (tileList[i][j].getPopulation()) > 0 ){
               carTotal+=tileList[i][j].getPopulation();
           }
           if((tileList[i][j].getLabel() == "I") && (tileList[i][j].getPopulation()) > 0 ){
               intTotal+=tileList[i][j].getPopulation();
           }
        }
    }
    cout << "\nThe total populations for the zones are: \n";
    cout << "Domestic: " << domTotal << endl;
    cout << "Cargo: " << carTotal << endl;
    cout << "International: " << intTotal << endl;
}

//Don't think about it too hard
void tiles::assignPointers() {
    //Outer two loops for cycling through double vector
    for (int xLoc = 0; xLoc < tileList.size(); xLoc++){
        for (int yLoc = 0; yLoc < tileList[xLoc].size(); yLoc++) {

            int x = 0;
            int y = 0;
            tile* tempAdjList[3][3];

            //Inner two loops for assigning pointers
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    //assigning adjacency pointers???
                    x = xLoc + i;
                    y = yLoc + j;
                    if ((x < 0) || (y < 0) || (x > tileList.size()-1) || (y > tileList.at(0).size()-1)) {
                        tempAdjList[(i + 1)][(j + 1)] = nullptr;
                    }
                    else {
                        tempAdjList[(i + 1)][(j + 1)] = &tileList[x][y];
                    }
                }
            }
            
            tileList[xLoc][yLoc].setAdjacency(tempAdjList);
        }
    }
}