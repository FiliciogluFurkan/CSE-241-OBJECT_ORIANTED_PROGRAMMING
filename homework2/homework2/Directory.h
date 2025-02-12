#ifndef Directory_h
#define Directory_h
#include<vector>
#include "OS.h" //includes base class header
using namespace std;
class Directoryfile : public OS {
private:
    vector<vector<string> > s;//to read file
    vector<vector<string> >::iterator row;
    vector<string>::iterator col;//iterator which keeps directories
public:
    Directoryfile(const string& _name2 = "D. ", const string& _currentfilename2 = "", int _currentpath2 = 1);//constructor
    void lscommand() override;
    void currenttime(string filename);
    void touchcommand(const string& name) override;
    void mkdircommand(const string& name) override;
    void rmcommand(const string& name) override;
    void cpcommand(const string& name1, const string& name2) override;
    void rmdircommand(const string& name)override;
    void cdcommand(const string& name);
    void cd1command();
    void cd2command();
    void catcommand(const string& name1)override;
    void lsrcommand() override;
    void print_directory_contents(const vector<vector<string> >& data, int depth);
    void cleancommand();
    //comands i overrided

};
#endif
