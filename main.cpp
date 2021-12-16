#include "readin.h"
#include "tiles.h"
using namespace std;

int main(){
    int timeLimit, refreshRate;
    string mapFileName;

    //initialize tiles instance
    tiles tileMap;

    //read config and get variables from config
    readConfig(&timeLimit, &refreshRate, &mapFileName);
    
    //read in region file
    tileMap.loadTiles(mapFileName);
    //print initial region file
    tileMap.assignPointers();

    cout << "\nInitial Zone State\n";
    tileMap.regionPrint();

    if(tileMap.runSim(timeLimit, refreshRate) == false){
       cout << "\n\nFinal Region State: " << endl; 
       tileMap.regionPrint();
       tileMap.printPollutionMap();
       tileMap.printPopTotal();
       tileMap.requestedArea();
    }

    cout << "Simulation Complete!\n";

    return 0;
}