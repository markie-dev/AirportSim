#include <vector>
#include "tile.h"
using namespace std;

class tiles{
    private:
        int tilecnt;

        typedef vector<tile> tiles_;
        tiles_ tileList;
        
    public:
        tiles() {tilecnt=0;}

        int getCnt();

        void cntInc();
        void cntDec();

        void loadTiles(string);
        void editTile(int);
        
        void cleanup();
        void prtlist();
        void loadItems();
        void storeItems();

        void regionPrint();
        
};