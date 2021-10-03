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

string tile::getLabel(){return label;}
int tile::getXCoord(){return x;}
int tile::getYCoord(){return y;}
int tile::getPollution(){return pollution;}
int tile::getPopulation(){return population;}

void tile::setnext(tile* np) {next = np;}
tile* tile::getnext() {return next;}

void tile::print() {
    cout << "Label: " << label << " Coordinates: " << x << ", " << y << endl;
}

