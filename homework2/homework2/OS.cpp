#include "OS.h"
#include <string>
#include <vector>
#include<fstream>
using namespace std;
     void OS::lscommand() {};
     void OS::mkdircommand(const string& name) {};
     void OS::rmcommand(const string& name) {};
     void OS::cpcommand(const string& name1, const string& name2) {};
     void OS::linkcommand(const string& name1, const string& name2) {};
     void OS::cdcommand(const string& name) {};
     void OS::catcommand(const string& name1) {};
     void OS::touchcommand(const string& name) {};
     void OS::lsrcommand() {};
     void OS::rmdircommand(const string& name) {};
     void OS::cd1command() {};
     void OS::cd2command() {};
     //these are pure virtual function and implemented in derived classes.i did not use (=0) but i did not implement at here.So it behaves like pure virtual
    int OS::getcurrentpath() {
        return currentpath;
    }
    string  OS::getcurrentfilename() {
         return currentfilename;
    }
    string  OS::getcurrentdirectory() {
        return currentdirectory;
    }
    void OS::setfile(const string& other) {
        currentfilename = other;
    }
    void OS::setdirectory(const string& other) {
        currentdirectory = other;
    }
    void  OS::setpath(int b) {
        currentpath = b;
    }
    //i have getter and setters
    OS::OS(const string& _name, const string& _currentfilename, int _currentpath) ://this is consturctor.i talked about Logic of the program in directory.cpp 
        currentdirectory(_name),currentfilename(_currentfilename),currentpath(_currentpath){
        ifstream file("deneme2.txt");
        ofstream file2("deneme2.txt", ios::app);
        string sentence;
        if (!getline(file, sentence)) {
            file2 << _name;
        }
        file.close();
        file2.close();
    }//this is important.deneme2.txt file should include D. for the program to run
    vector<vector<string>>  OS::readfile() {//reads deneme2.txt to remember previous files and directories
        ifstream file("deneme2.txt");
        string sentence;
        // İki boyutlu vektör tanımla
        vector<vector<string> > a;
        // Her satırı oku
        while (getline(file, sentence)) {
            // Eğer satır "D." ile başlıyorsa
            if (sentence[0] == 'D' && sentence[1] == '.') {
                a.push_back(vector<string>()); // Yeni bir alt vektör oluştur
                a.back().push_back(sentence); // Bu alt vektörün ilk elemanını ekle
            }
            else {
                // "D." ile başlamıyorsa ve daha önce bir alt vektör oluşturulmuşsa
                if (!a.empty()) {
                    a.back().push_back(sentence); // Şu anki alt vektöre satırı ekle
                }
            }
        }
        file.close();
        return a;    
    }
