#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/*
    Tile Class that holds each tiles information
*/
class tile{
    private:
        string label;
        int x, y, pollution, population;

        tile* adjList[3][3];
        //vector<tile*> adjList;
        /*  Map of Pointers (Not implemented yet):
            [5][6][7]
            [3] C [4]
            [0][1][2]
        */

    public:
        tile();
        //initialize each tile function
        tile(string, int, int, int, int);

        void setLabel(string);
        void setXCoord(int);
        void setYCoord(int);
        void setPollution(int);
        void setPopulation(int);
        void setAdjacency(tile* newAdjList[3][3]); //Set the adjacency tile list

        string getLabel();
        int getXCoord();
        int getYCoord();
        int getPollution();
        int getPopulation();

        //Testing for adjacency read in
        void printAdjacency();

        //check if adjacents have powerlines
        bool isAdjPowerline();
        //check adjacents
        int checkAdjPopulation(int);
        int checkAdjPollution(int);
};
