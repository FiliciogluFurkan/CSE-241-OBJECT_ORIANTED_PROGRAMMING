#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "OS.h"
#include "Directory.h"
#include "Softlinked.h"
#include "Regular.h"
using namespace std;
//including all necessary libraries

int main() {
    Directoryfile obje1;
    Softlinked obje2;
    Regular obje3;
    //i created objects
    string command;//to take command from user
    cout << "Myshell" << endl;
    
    ifstream file("deneme.txt");//writes all commands to deneme.txt file
    string sentence;
    while (getline(file, sentence)){//before starting of program,it reads previous commands
        cout << sentence << endl;
     }   
    file.close();
    ofstream file2("deneme.txt", ios::app);//writes commands to file
    while (true) {
        cout << "> ";
        file2 << "> ";
        cin >> command;
        file2 << command;
        if (obje3.getsize() < 10485760) {//controls size is bigger than 10mb or not,if not;
            if (command == "ls") {//if user select ls
                file2 << endl;
                obje1.lscommand();
            }
            else if (command == "mkdir") {//if user select mkdir
                string name;
                cin >> name;
                file2 << " " << name << endl;//takes parameter
                obje1.mkdircommand(name);
            }
            else if (command == "rm") {//if user select rm
                string name;
                cin >> name;
                file2 << " " << name << endl;
                obje1.rmcommand(name);

            }
            else if (command == "touch") {//if user select touch,creates mew file.Not necessary but ı just want to do that
                string name;
                cin >> name;
                file2 << " " << name << endl;
                obje1.touchcommand(name);
            }
            else if (command == "cp") {//if user select cp.Copies files
                string name, name1;
                cin >> name;
                cin >> name1;
                file2 << " " << name << " " << name1 << endl;
                obje1.cpcommand(name, name1);

            }
            else if (command == "link") {//if user select link.LInk files
                string name1, name2;
                cin >> name1;
                cin >> name2;
                obje2.linkcommand(name1, name2);
            }
            else if (command == "cd") { //if user select cd.Goes one directon forward
                string name;
                cin >> name;
                file2 << " " << name << endl;
                obje1.cdcommand(name);
            }
            else if (command == "cat") {//if user select cat.Reads file which user select
                string name;
                cin >> name;
                obje1.catcommand(name);
            }
            else if (command == "ls-R") { //shows all directories and files
                obje1.lsrcommand();
            }
            else if (command == "rmdir") {//deletes directories if it is empty
                string name;
                cin >> name;
                obje1.rmdircommand(name);
            }
            else if (command == "cd.") {//goes to beginning
                obje1.cd1command();
            }
            else if (command == "cd..") {
                obje1.cd2command();//goes previous directiory
            }
            else if (command == "clear") {
                obje1.cleancommand(); //clear previous commands.You must start program again
            }
            else {
                cout << "There is no such a command like this in this operating system." << endl;
                file2 << "There is no such a command like this in this operating system." << endl;//if user does not select correct command
            }
        }
        else {
            cout << "Disk is full.There is no enough place to store data" << endl;//if disk full,program finish
        }
    }
    
    file2.close();
    return 0;
}
