#include "Softlinked.h"
#include "OS.h"
#include <string>
#include <vector>
using namespace std;
#include <string>
#include <sstream>
#include<fstream>
//logic of this function is very important.Generally i write the content like that D OR F + name   at here,i also add again name
//but the file i linked.Also i add to OS system with the * character to contradistinguish
    void Softlinked::linkcommand(const string& name1, const string& name2) {
        vector<vector<string> > a = readfile();
        string temp2 = "F *" + name2;
        int flag = 0;
        ofstream file("deneme2.txt");

        for (row = a.begin(); row != a.end(); ++row) {
            string temp = (*row)[0];
            istringstream iss(temp);
            string firstWord, secondWord;
            iss >> firstWord >> secondWord;

            if ((firstWord + " ") == getcurrentdirectory()) {
                for (col = row->begin(); col != row->end(); ++col) {
                    if (*col == ("F " + name1)) {
                        flag = 1;
                        temp2 = temp2 + " " + name1;//adds the name1 because ı wanted that which file is linked 
                        row->push_back(temp2);
                        break;
                    }
                }
            }
        }

        if (flag == 0) {
            cout << "There is no such a file in this directory" << endl;
        }

        for (int i = 0; i < a.size(); i++) {//rewrite the whole vector again
            for (int j = 0; j < a[i].size(); j++) {
                file << a[i][j] << endl;
              }
        }
        file.close();
    }
