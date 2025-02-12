#ifndef Regular_h
#define Regular_h
#include <vector>
#include "OS.h"
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;
//calcluates the size
class Regular :public OS {
public:
    int calculatesize();
    int getsize();
private:
    vector<vector<string> >s;
    vector<vector<string> >::iterator row;
    vector<string>::iterator col;
    int size = 0;
}; 

#endif
