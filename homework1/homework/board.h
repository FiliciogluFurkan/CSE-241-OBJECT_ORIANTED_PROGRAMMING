#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <vector>
//i incluede the libraries
using namespace std;
class Chessboard {
private:
    int mate1=0, mate2=0; // controls that pieces make checkmate or not.
    std::vector<std::vector<pieces> > board;
    double whiteScore = 0; //calculates white score
    double blackScore = 0; //calculates black score
    int flag1 = 0;  // controls game over or not;
    int turn = 0;  // controls whose turn is it. If turn is odd, it's black's turn; else, it's white's turn
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0, k1 = 0, k2 = 0; // to make rock

public:
    double getscore1()const;//return white player's score
    double getscore2()const;//return blac player's score
    Chessboard(); //i used contructor to initialize board
    void underattack(int k, int l); //decreases point of black pieces if it is underttack
    void underattack2(int k, int l);//decreases point of white pieces if it is underttack
    void score()const;//cout score
    void suggest(); //if user use suggest,this function called
    void isunderattack(); //controls that pieces are underattack or not
    bool isvalidmove(int a,int b,int c,int d)const; //this one for suggest function.If not valid move,return false 
    void writefile()const; //write the boards to the file
    void ischeckmate();//controls game over or not
    void displayBoard() const;
    void game(); //controls the game(whose turn it is,game is over or not,gets input
    void move(char a,int b,char c,int d); //makes the movement here
};

#endif
