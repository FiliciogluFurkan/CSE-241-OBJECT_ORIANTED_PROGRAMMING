#ifndef Softlinked_h
#define Softlinked_h
#include<vector>
#include "OS.h"
#include<fstream>
#include<iostream>

class Softlinked :public OS {//makes link command at here
public:
    void linkcommand(const string& name1, const string& name2) override;
private:
    vector<vector<string> >::iterator row;
    vector<string>::iterator col;
};
#endif
