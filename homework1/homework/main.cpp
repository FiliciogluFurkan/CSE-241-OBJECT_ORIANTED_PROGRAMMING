#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#include "board.h"
#include "pieces.h"
//includes the libraries
using namespace std;

int main() {
	srand(time(NULL)); //this is for suggest function.İf piece not eat other piece,it makes random move
    cout << "Welcome to the Chess game!\n" << endl;
    Chessboard chess; //created object
    chess.displayBoard();//shows the first board
    chess.game();//calls the game function
    chess.score(); //at the end of the game,shows the score of both players
   return 0;
}
