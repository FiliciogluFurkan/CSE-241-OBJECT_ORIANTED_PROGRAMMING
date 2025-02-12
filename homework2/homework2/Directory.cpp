#include "Directory.h"
#include <string>
#include <vector>
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include "OS.h"
#include <iomanip>
#include<filesystem>
namespace fs = std::filesystem;
//it is so important place to understand the logic of the program.deneme2.txt file starst with (D. ).This mean that
//this is the starting point of program and if i make cp or touch,files added to this directory.I you make mkdir,
//adds here but ends of the file,makes a new directory D.. filename.If you go with cd command to here,you are in
//D.. directiory and you can make touch,cp also mkdir again but if you do,it adds to end of the program D... filename.
//this is how program works.Also before taking a command from user,i read the txt file with vector and iterator show the files
//so,vector keeps contents and program remembers previous process
    Directoryfile::Directoryfile(const string& _name2, const string& _currentfilename2, int _currentpath2 ) :
        OS(_name2, _currentfilename2, _currentpath2) {
    }//iti is initialized at header file.A the beginning conditions.currentdirector="D. ",file name "",currentpath 1 
     void Directoryfile::lscommand()  {//shows contents at the related directorypath
        s = readfile();
        string firstColWord, secondColWord, temp2;
        for (row = s.begin(); row != s.end(); ++row) {
            string temp = (*row)[0];
            // Use istringstream to tokenize the string
            istringstream iss(temp);
            string firstWord, secondWord;
            iss >> firstWord >> secondWord;

            if ((firstWord + " ") == getcurrentdirectory() && getcurrentfilename() == secondWord) {//first word shows D. or D.. or
            //d... (empty is necessary becaues i saved D.+" " so we add everytime " "to firstword)
            //d.. filename    at here secondWord keeps filename and if it is equal to currentfilename
                for (int i = 1; i <= getcurrentpath(); ++i) {
                    cout << 'D';
                    for (int j = 0; j < i; ++j) {
                        cout << '.';
                    }
                    cout << endl;
                }//before printing content of currentDirectory,it prints from beginning to current how much you are forward
                for (col = row->begin() + 1; col != row->end(); ++col) {
                    if ((*col)[2] == '*') {//this is for link statement.You will understand the logic at link command function
                        temp2 = *col;
                        istringstream iss(temp2);
                        iss >> firstColWord >> secondColWord;
                        cout << "F " << secondColWord << endl;
                    }//at this line,there is another word and i did not want to show user third word.
                    else {
                        cout << *col << endl;//prints contents
                    }
                }
                break;
            }
        }
    }
    void Directoryfile::currenttime(string filename) {
        ofstream file2("deneme3.txt", ios::app);

        // obtain current time.We must include ctime library 
        time_t currentTime = time(0);
        tm* localTime = localtime(&currentTime);

        // writes to the file when file is created
        file2 << filename << "  ";
        file2 << "Created time: " << localTime->tm_year + 1900 << '-'
            << setw(2) << setfill('0') << localTime->tm_mon + 1 << '-'
            << setw(2) << setfill('0') << localTime->tm_mday << "  ";

        file2 << setw(2) << std::setfill('0') << localTime->tm_hour << ':'
            << setw(2) << setfill('0') << localTime->tm_min << ':'
            << setw(2) << setfill('0') << localTime->tm_sec << endl;
//formats i want to show user like that
        // Dosyayı kapat
        file2.close();
    }
    void Directoryfile::touchcommand(const string& name)  {//i know you did not want this but i did.
        vector<vector<string> > a = readfile();
        ofstream file("deneme2.txt");
        for (row = a.begin(); row != a.end(); ++row) {
            string temp = (*row)[0];//i am doing the same thing.Seperating the words
            istringstream iss(temp);
            string firstWord, secondWord;
            iss >> firstWord >> secondWord;
            if ((firstWord + " ") == getcurrentdirectory() && getcurrentfilename() == secondWord) {
                string temp2 = "F " + name;//if it is in current directory and current filename pushback F +name to file
              //now,current directory shown in the file have this line 
                row->push_back(temp2);
                currenttime(name);
            }
        }

        for (row = a.begin(); row != a.end(); ++row) {//after pushback,it writes whole vector to txt file again
            for (col = row->begin(); col != row->end(); ++col) {
                file << *col << endl; // Separate entries with a space
            }
        }

        file.close();
    }
     void Directoryfile::mkdircommand(const string& name)  {//creates new directory
        vector<vector<string> > a = readfile();
        ofstream file("deneme2.txt");
        for (row = a.begin(); row != a.end(); ++row) {
            string temp = (*row)[0];
            istringstream iss(temp);
            string firstWord, secondWord;
            iss >> firstWord >> secondWord;

            if ((firstWord + " ") == getcurrentdirectory() && getcurrentfilename() == secondWord) {//if it is in cuurent directory
            //and currentfile,it pushbacks this line to a vector
                row->push_back(("D " + name));
            }
        }
        for (row = a.begin(); row != a.end(); ++row) {//writes vector again to the file
            for (col = row->begin(); col != row->end(); ++col) {
                file << *col << endl; // Separate entries with a space
            }
        }
        
        file << "D"; //at the end,it adds D.(getcurrentpath()+1) for example if path is D..  it ads  D...
        for (int i = 0; i <= getcurrentpath(); i++) {
            file << ".";
        }
        file << " " << name;//it adss the directory name D... directoryname
        file.close();
    }
    void Directoryfile::rmcommand(const string& name)  {//removes files from directory
        int flag1 = 0;//flag
        int flag2 = 0;//flag
        vector<vector<string> > a = readfile();
        string firstWord, secondWord;

        // Check if 'name' is a folder
        for (row = a.begin(); row != a.end(); ++row) {
            string temp = (*row)[0];
            istringstream iss(temp);
            iss >> firstWord >> secondWord;

            if (secondWord == name) {
                flag1 = 1;
                break;
            }
        }//controls it is file or directory.if it is directory 
        // Check if 'name' is a file in the current directory
        string temp2,word1,word2,word3;
        for (row = a.begin(); row != a.end(); ++row) {
            string temp = (*row)[0];
            istringstream iss(temp);
            iss >> firstWord >> secondWord;
            for (col = row->begin(); col != row->end(); ++col) {
            temp2=*col;
            istringstream iss2(temp2);
            iss2>>word1>>word2>>word3;
          if ((*col == ("F " + name)) || (*col == ("F " + name + " " + word3)) && (getcurrentdirectory() == (firstWord + " "))) {
                    flag2 = 1;
                    break;//if it is current directory
                }
                
            }
        }
        // Perform removal based on conditions
        if (flag1 == 1) {//if it is directory
            cout << "This is a folder and cannot be removed." << endl;
        }
        else if (flag2 == 0) {//if it is not in current directory
            cout << "File not found." << endl;
        }
        else {//if it is in current directory
            ofstream file("deneme2.txt");
            for (row = a.begin(); row != a.end(); ++row) {
                string temp = (*row)[0];
                istringstream iss(temp);
                iss >> firstWord >> secondWord;

                for (col = row->begin(); col != row->end(); ++col) {
                    if (getcurrentdirectory() == (firstWord + " ")) {
                        if (*col == ("F " + name) || *col=="F "+name+" "+word3) {//if line equals this it deletes from file
                            // Do nothing, skip the entry
                        }
                        else {
                            file << *col << endl;//else writes again
                        }
                    }
                    else {
                        file << *col << endl;
                    }
                }
            }
            file.close();//deletes the content of the file
            string sentence, temp3, word;
            vector<string> a;
            ifstream file2("deneme3.txt");
            while (getline(file2, sentence)) {//reads the content of the file
                a.push_back(sentence);
            }
            file2.close();
            ofstream file3("deneme3.txt");
            for (int i = 0; i < a.size(); i++) {
                temp3 = a[i];
                istringstream iss(temp3);
                iss >> word;
                if (word == name) {//if the name of first line eqauls file name,dont write to deneme3.txt file anyting
                }
                else {//else writes vector
                    file3 << a[i] << endl;
                }
            }
            file3.close();
        }

    }
    void Directoryfile::cpcommand(const string& name1, const string& name2){//this is cp commmand
        vector<vector<string> >a = readfile();
        string sentence;
        ofstream file("deneme2.txt");
        if ((name2 + " ") != getcurrentdirectory()) {
            cout << "Not Current Directory Selected" << endl;
            return;
        }//user select current directory.D.  D..  D... etc.   else gives error
     string pathname = getenv("HOME");
    // Create a path to the desktop directory
    fs::path desktopPath = fs::path(pathname) / "Desktop";
 // Check if the desktop directory exists
    if (fs::exists(desktopPath) && fs::is_directory(desktopPath)) {//it controls it is in Desktop or not.If else controls it is in 
    //system or not
        // Check if the file exists on the desktop
        fs::path filePath = desktopPath / name1;
        if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
      ifstream file(filePath);
    if (file.is_open()) {
       sentence= string ((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());//sentence keeps the content of file
        file.close();
    } 
    ofstream file3("deneme3.txt",ios::app);
    file3<<name1+" "+sentence;//writes the content of file with the name of file.
    file3.close();
string word1,word2;    
for(int i=0;i<a.size();i++){
string temp3=a[i][0];
istringstream iss(temp3);
iss>>word1>>word2;
for(int j=0;j<a[i].size();j++){
if((word1+" ")==getcurrentdirectory() && word2==getcurrentfilename()){
a[i].push_back("F "+name1);//also it add to my OS sytem with.Makes pushback to related directory
break;
}
}
}
} 
   for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < a[i].size(); j++) {
                file << a[i][j] << endl;
            }
        }    
    }//rewrite whole vector to file again
    else{//if it is not in Desktop,
        int flag = 0;
        for (int i = 0; i < a.size(); i++) {
            string temp = a[i][0];
            // Use istringstream to tokenize the string
            istringstream iss(temp);
            string firstWord, secondWord;
            iss >> firstWord >> secondWord;
            if (name1 == secondWord) {//controls user select directory or not.If it is
                flag = 1;//flag becomes 1
            }
        }
        int flag1 = 0;
        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < a[i].size(); j++) {
                if (a[i][j] == ("F " + name1))//controls it is file or not also controls it is in OS system or not
                    flag1 = 1;
            }
        }
        if (flag == 0 && flag1 == 1) {//if file and not in directory
            for (size_t i = 0; i < a.size(); i++) {
                string temp = a[i][0];
                // Use istringstream to tokenize the string
                istringstream iss(temp);
                string firstWord, secondWord;
                iss >> firstWord >> secondWord;
                if (firstWord + " " == getcurrentdirectory() && secondWord == getcurrentfilename()) {
                    a[i].push_back(("F " + name1));//pushback the file again to current directory
                }
            }
        }
        if (flag == 0 && flag1 == 0) {//if file doesnot exist
            cout << "file does not exist" << endl;
        }
        string temp3, word1, word2;
        vector<string>v;
        if (flag == 1) {//if it is file,it copies directory and content of the file
            for (int i = 0; i < a.size(); i++) {
                temp3 = a[i][0];
                istringstream iss(temp3);
                iss >> word1 >> word2;
                if (name1 == word2) {
                    for (int j = 1; j < a[i].size(); j++) {
                        v.push_back(a[i][j]);//there is another vector and adds the content of directory selected by user
                    }
                }
                if (word1 + " " == getcurrentdirectory())
                    a[i].push_back("D " + name1);//pushbacks to current directory
            }
        }
        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < a[i].size(); j++) {
                file << a[i][j] << endl;
            }
        }//writes the vector again and
        file << "D";
        for (int i = 0; i < getcurrentdirectory().size() - 1; i++) {
            file << ".";
        }//makes a new directory and adds the content which we keep with v vector
        file << " " << name1 << endl;
        for (int i = 0; i < v.size(); i++) {
            file << v[i] << endl;
        }

        file.close();
     }   
    }
    void Directoryfile::rmdircommand(const string& name) {//removes directory
        s = readfile();
        ofstream file("deneme2.txt");
        int flag = 0;
        int value = 0;
        string temp, firstWord, secondWord;
        for (int i = 0; i < s.size(); i++) {
            temp = s[i][0];
            istringstream iss(temp);
            iss >> firstWord >> secondWord;
            if (secondWord == name)
                flag = 1;
            value = i;//keeps the index number of file
        }//controls it is in OS system or not
        if (s[value].size() == 1) {//if there is nothing in directory it deletes else gives error mesage
            if (flag == 1) {//if this is a directory
            
                for (int i = 0; i < s.size(); i++) {
                    if (i != value) {
                        temp = s[i][0];
                        istringstream iss(temp);
                        iss >> firstWord >> secondWord;
                        for (int j = 0; j < s[i].size(); j++) {
                            if (firstWord + " " == getcurrentdirectory() && s[i][j] =="D "+name) {
                            }//removes related line from directory
                            else {
                                file << s[i][j] << endl;
                            }
                        }
                    }
                }
                return;
            }if (flag == 0) {
                cout << "There is no Directory in this operating system" << endl;
            }
        }
        else {
            cout << "Directory is not empty.Cannot be removed" << endl;
        }
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < s[i].size(); j++) {
                file << s[i][j] << endl;
            }
        }//rewrites whole vector again

        file.close();

    }
    void Directoryfile::cdcommand(const string& name) {//changes the path of program
        vector<vector<string> >a = readfile();
        string firstWord, secondWord;
        int flag = 0;
        int value = 0;
        string word1, word2;
        for (size_t i = 0; i < a.size(); i++) {
            string temp = a[i][0];
            // Use istringstream to tokenize the string
            istringstream iss(temp);
            iss >> firstWord >> secondWord;
            if (secondWord == name) {//if user enters the Directoryname which want to go
                flag = 1;//flag becomes 1.it means there is file but contorls.You will see a little bit later
                value = firstWord.length() - 1;//Because of D letter
                word1 = firstWord;
                word2 = secondWord;
            }
        }
        if (flag == 1) {//controls that Directory is valid but at where?
            if ((getcurrentpath() + 1) != value) {//if directory is away from by 1 
                cout << "Not valid directory.You cannot go more than one forward" << endl;
            }
            else {
                setdirectory(word1 + " ");
                int a = getcurrentpath();//else changes the path.filename.currentdirectory
                a = a + 1;
                setpath(a);
                setfile(word2);
            }
        }
        else {
            cout << "Not Valid Directory or File Selected" << endl;
        }
    }
    void Directoryfile::cd1command() {//goes the beginning of the Directory
        setdirectory("D. ");
        setfile("");
        setpath(1);
    }
    void Directoryfile::cd2command() {//goes previous directory
        s = readfile();
        int value;
        string temp, temp2, word1, word2, word3;
        for (int i = 0; i < s.size(); i++) {
            temp = s[i][0];
            istringstream iss(temp);
            iss >> word1 >> word2;
            for (int j = 1; j < s[i].size(); j++) {
                if (s[i][j] == getcurrentfilename()) {//controls whole vector and if finds the name of currentfilename
                //it means that you will go this directory
                    setdirectory(word1 + " ");
                    setfile(word2);
                    value = getcurrentpath() - 1;//decreases currentpath
                    setpath(value);
                }
            }
        }
    }

    void Directoryfile::catcommand(const string& name1) {//reads the content of file
        ifstream file("deneme3.txt");
        string sentence, firstWord, secondWord, temp, temp2, Word1, Word2, Word3;
        vector<vector<string> >a;
        a = readfile();//reads file
        int flag = 0;
        for (int i = 0; i < a.size(); i++) {
            temp = a[i][0];
            // Use istringstream to tokenize the string
            istringstream iss(temp);
            iss >> firstWord >> secondWord;
            for (int j = 0; j < a[i].size(); j++) {
                if (firstWord + " " == getcurrentdirectory() && (a[i][j] == ("F " + name1))) {//if finds the filename from 
                //current directory,there is a flag for this
                    flag = 1;
                    break;
                }
                temp2 = a[i][j];//this is for linked file.user can want to read linked file.Controls it is linked file or not
                istringstream iss(temp2);
                iss >> Word1 >> Word2 >> Word3;
                if (firstWord + " " == getcurrentdirectory() && (Word2 == (name1))) {
                    flag = 1;
                    break;
                }

            }
        }
        if (flag != 0) {//if this is file or linked file
            while (getline(file, sentence)) {
                temp = sentence;
                istringstream iss(temp);
                iss >> firstWord;
                if (firstWord == name1 || firstWord == Word3) {
                    cout << sentence << endl;//pritns the content of the file
                    break;
                }
            }
        }
        if (flag == 0)
            cout << "File could not found" << endl;
        file.close();
    }
    void Directoryfile::lsrcommand() {
        s = readfile(); // Read directory data
        print_directory_contents(s, 0); // Start recursive printing from depth 0
    }

    void Directoryfile::print_directory_contents(const vector<vector<string> >& data, int depth) {
        if (depth >= data.size()) {
            return; // Base case: end of current level
        }
        // Print indentation for current depth
        for (int i = 0; i < depth; ++i) {
            cout << "  ";
        }
        // Print the current filenames
        for (size_t index = 0; index < data[depth].size(); ++index) {
            cout << data[depth][index] << endl;
        }
        // Recursively print subdirectories
        for (size_t index = 0; index < data[depth].size(); ++index) {
            if (data[depth][index].substr(0, 2) == "D.") {
                print_directory_contents(data, depth + 1);
            }
        }
    }
    void Directoryfile::cleancommand() {//clean the terminal but program must start again
        ofstream file("deneme.txt");
        file.close();
    }
    
