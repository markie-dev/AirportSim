#include <iostream>
#include "readin.h"
#include "tiles.h"
using namespace std;

int main(){
    int a, b;
    string c;

    tiles tileMap;

    readConfig(&a, &b, &c);

    cout << "\nRegion Map: " << c << endl;
    cout << "Time Limit: " << a << endl;
    cout << "Refresh Rate: " << b << endl;
    
    tileMap.loadTiles(c);
    //tileMap.prtlist();
    cout << "\nInitial Zone State\n";
    tileMap.regionPrint();
    tileMap.cleanup();

    return 0;
}