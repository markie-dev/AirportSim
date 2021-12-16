#include <vector>
#include "tile.h"
using namespace std;

class tiles{
    private:
        //create tile vector
        vector< vector<tile> > tileList;
        
        
    public:
        tiles()  { }
        ~tiles() { tileList.clear(); }

        void loadTiles(string);
        void regionPrint();

        bool runSim(int, int);
        void updateSim(vector< vector<tile> >);
        int updateWorkers();
        int updateGoods();
        void printPopTotal();
        void printPollutionMap();
        void requestedArea();

        //Will use the vector of tiles to assign the vector pointers to adjacent tiles
        void assignPointers();
        int getValidInput(int, int, int);
};