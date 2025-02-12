#ifndef OS_H
#define OS_H
#include <string>
#include <vector>

using namespace std;

class OS {
public:
    virtual void lscommand();
    virtual void mkdircommand(const string& name);
    virtual void rmcommand(const string& name);
    virtual void cpcommand(const string& name1, const string& name2);
    virtual void linkcommand(const string& name1, const string& name2);
    virtual void cdcommand(const string& name);
    virtual void catcommand(const string& name1);
    virtual void touchcommand(const string& name);
    virtual void lsrcommand();
    virtual void rmdircommand(const string& name);
    virtual void cd1command();
    virtual void cd2command();
    int getcurrentpath();
    string getcurrentfilename();
    string getcurrentdirectory();
    void setfile(const string& other);
    void setdirectory(const string& other);
    void setpath(int b);
    OS(const string& _name = "D. ", const string& _currentfilename = "", int _currentpath = 1);
    vector<vector<string> > readfile();
private:
    int currentpath;
    string currentfilename;
    string currentdirectory;
};

#endif // OS
