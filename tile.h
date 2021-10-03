#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class tile{
    private:
        string label;
        int x, y, pollution, population;
        tile *next;

    public:
        tile();
        tile(string, int, int, int, int);

        void setLabel(string);
        void setXCoord(int);
        void setYCoord(int);
        void setPollution(int);
        void setPopulation(int);

        void setnext(tile*);

        string getLabel();
        int getXCoord();
        int getYCoord();
        int getPollution();
        int getPopulation();

        virtual void print();

        tile* getnext();
};
