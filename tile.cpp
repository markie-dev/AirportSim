#include "tile.h"
using namespace std;

tile::tile(string l, int xCoord, int yCoord, int pollu, int popul) {
    label = l;
    x = xCoord;
    y = yCoord;
    pollution = pollu;
    population = popul;
}

void tile::setLabel(string l){label=l;}
void tile::setXCoord(int xCoord){x=xCoord;}
void tile::setYCoord(int yCoord){y=yCoord;}
void tile::setPollution(int pollu){pollution=pollu;}
void tile::setPopulation(int popul){population=popul;}


void tile::setAdjacency(tile* newAdjList[3][3]) {  //Set the adjacency tile list
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adjList[i][j] = newAdjList[i][j];
        }
    }
}

string tile::getLabel(){return label;}
int tile::getXCoord(){return x;}
int tile::getYCoord(){return y;}
int tile::getPollution(){return pollution;}
int tile::getPopulation(){return population;}


void tile::printAdjacency() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (adjList[i][j] == nullptr) { //Check for nullptr (out of bounds)
                cout << "[@]";
            }
            else if ((i == 1) && (j == 1)) { //Check for center
                cout << "---";
                continue;
            }
            else {  //Else print the label
                cout << '[' << adjList[i][j]->getPopulation() << ']';
            }
        }
        cout << endl;
    }
}

//bool function to see if tile is adjacent to a powerline
bool tile::isAdjPowerline(){
    int powerLine=0, PoT=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (adjList[i][j] == nullptr) {break;} //Check for nullptr (out of bounds)
            else if ((i == 1) && (j == 1)) {continue;} //Middle Check
            else if (adjList[i][j]->getLabel() == "T"){  //Check if Label is Powerline
                powerLine++;
            }
            else if (adjList[i][j]->getLabel() == "#"){  //Check if Label is Powerline over Terminal
                PoT++;
            }
        }
    }

    if((powerLine > 0) || (PoT > 0)){
        return true;
    }
    return false;
}

//check highest adjacent population number
int tile::checkAdjPopulation(int requestedPopulationNumber){
    int numAdj=0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (adjList[i][j] == nullptr) {break;} //Check for nullptr (out of bounds)
                else if ((i == 1) && (j == 1)) {break;} //Middle Check
                else if ((adjList[i][j]->getPopulation())>=requestedPopulationNumber){numAdj++;}
            }
        }return numAdj;
}

//check highest adjacent pollution number
int tile::checkAdjPollution(int pollutionNum){
    int largestPull=0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (adjList[i][j] == nullptr) {break;} //Check for nullptr (out of bounds)
                else if ((i == 1) && (j == 1)) {break;} //Middle Check
                else if ((adjList[i][j]->getPollution() > pollutionNum) &&  (adjList[i][j]->getPollution() > largestPull)){largestPull=adjList[i][j]->getPollution();}
            }
        }return largestPull;
}