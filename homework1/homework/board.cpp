#include "board.h"
#include <vector>
#include <iostream>
#include<cmath>
#include <ctime>//these are just used to make random movement.there is nothing features of c language
#include <fstream>
using namespace std; //including necessary libraries
 double Chessboard::getscore1()const{//returns white player's score
 return whiteScore;
 }
 double Chessboard::getscore2()const{//returns black player's score
 return blackScore;
 }
Chessboard::Chessboard() : whiteScore(0), blackScore(0) {
        // Initialize the chessboard with pieces
        board.resize(8,std::vector<pieces>(8));

        // Populate the board with initial pieces
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == 0) {
                    // Set black pieces
                    if (j == 0 || j == 7){					
                        board[i][j].setPieceType('r');
                     }
                    else if (j == 1 || j == 6){
					    board[i][j].setPieceType('n');
                    }else if (j == 2 || j == 5){
					
                        board[i][j].setPieceType('b');
                }
					else if (j == 3){
					    board[i][j].setPieceType('q');
		 			}else if (j == 4){
					 
                        board[i][j].setPieceType('k');
       }
			    } else if (i == 1) {
                    // Set black pawns
                    board[i][j].setPieceType('p');
                } else if (i == 6) {
                    // Set white pawns
                    board[i][j].setPieceType('P');
                } else if (i == 7) {
                    // Set white pieces
                    if (j == 0 || j == 7){	
                        board[i][j].setPieceType('R');
                }	else if (j == 1 || j == 6){
                        board[i][j].setPieceType('N');
                    }else if (j == 2 || j == 5){
                        board[i][j].setPieceType('B');
                    }else if (j == 3){
                        board[i][j].setPieceType('Q');
                    }else if (j == 4)
                        board[i][j].setPieceType('K');
			    } else {
                    // Empty squares
                    board[i][j].setPieceType('.');
                            }
            }
        }
   }//until here,I initialized the board
void Chessboard::displayBoard()const{ //this function shows the current board
int i,j;
for(int i=0;i<8;i++){
if(i!=8){
cout<<8-i<<" | ";	
}	for(j=0;j<8;j++){
	cout<<board[i][j].getPieceType()<<"  ";	
	}
	cout<<endl;
}	
cout<<"    ";
for(i=0;i<22;i++){
	cout<<"-";
}
cout<<endl<<"    ";
for(i=0;i<8;i++){
	cout<<char('a'+i)<<"  ";
}
cout<<endl<<endl;
}  
void Chessboard::game(){ //this function is the most importan.Game is played inside this function.
    	int y1,y2;//keeps the position of pieces
    	char x1,x2;
    	string answer;//to get input from user
do{		   
if (turn %2 == 0) {//controls whose turn is it.whites's turns are even,blacks are odd
ischeckmate();//controls white pieces's king in dangerous or not.
mate1=0; //control flag for checkmate	
cout << "[White's Turn]" << endl;
cout << "Please enter your move: ";
cin >> answer;
if (answer == "suggest") {
    suggest(); //if user want suggest,this function called
} else {
    do { //in here,until taking correct input,it takes input
            if( !(answer[0] >= 'a' && answer[0] <= 'h') || !(answer[1] >= '1' && answer[1] <= '8') ||!(answer[2] >= 'a' && answer[2] <= 'h') || !(answer[3] >= '1' && answer[3] <= '8')){
			
            cout << "Invalid move! Please enter your move again:";
            cin >> answer;        
        }
    } while (  !(answer[0] >= 'a' && answer[0] <= 'h') || !(answer[1] >= '1' && answer[1] <= '8') ||!(answer[2] >= 'a' && answer[2] <= 'h') || !(answer[3] >= '1' && answer[3] <= '8'));
            x1 = answer[0]; //keeps the user's input
            y1 = answer[1]- '0'; // Convert character to integer
            x2 = answer[2];
            y2 = answer[3]- '0'; // Convert character to integer
move(x1,y1,x2,y2);//calls move function is game is not over and valid input there is
turn=turn-1;	
ischeckmate();//controls that the king are in check position or not.
if(mate1==1){//if it is,game finish
	flag1=1;
	cout<<"Game finished.Black player won.Congratualions "<<endl;
}
turn=turn+1;
}
//do your movement here for white pieces
}
 else if (turn % 2 == 1) { //if turn is odd,black player's turn
ischeckmate();
 mate2=0;	
    cout << "[Black's Turn]" << endl;
    cout << "Please enter your move: ";
    cin >> answer; //gets input from user

if (answer == "suggest") {
    suggest();//if user want suggest,this function called
} else {
    do {//in here,until taking correct input,it takes input
            if( !(answer[0] >= 'a' && answer[0] <= 'h') || !(answer[1] >= '1' && answer[1] <= '8') ||!(answer[2] >= 'a' && answer[2] <= 'h') || !(answer[3] >= '1' && answer[3] <= '8')){
			
            cout << "Invalid move! Please enter your move again: ";
            cin >> answer;        
        }
    } while (  !(answer[0] >= 'a' && answer[0] <= 'h') || !(answer[1] >= '1' && answer[1] <= '8') ||!(answer[2] >= 'a' && answer[2] <= 'h') || !(answer[3] >= '1' && answer[3] <= '8'));
            x1 = answer[0];//keeps the user's input
            y1 = answer[1] - '0'; // Convert character to integer
            x2 = answer[2];
            y2 = answer[3] - '0'; // Convert character to integer
//do your movement here
move(x1,y1,x2,y2);
turn=turn-1;
ischeckmate();//controls king is in still check position
if(mate2==1){ //if it is,game is over
	flag1=1;
	cout<<"Game finished.White player won.Congratualions "<<endl;
}
turn=turn+1;
}    
}
isunderattack();//calls underattack function and
writefile();//writes the boards to the file
displayBoard();//shows the board

}while(flag1!=1); //if flag1==1,game finishes
}
void Chessboard::move(char a,int b,char c,int d){ //makes the movement here 
 int i;
 int row1=8-b;
 int col1=a-'a';
 int row2=8-d;
 int col2=c-'a';//i keep the input as integer.user select a,it means col is 0 for vector.if entered 5,it means 8-5.because numbers are from down to up
char character=a;	
if(turn%2==0){ //if turn is of white player
if(board[row1][col1].getPieceType()!='R' && board[row1][col1].getPieceType()!='N'&& 
board[row1][col1].getPieceType()!='B' && 
board[row1][col1].getPieceType()!='Q' && 
board[row1][col1].getPieceType()!='K' && 
board[row1][col1].getPieceType()!='P'){
cout<<"invalid piece movement.Place select correct your piece"<<endl;//if player select not itself pieces,warns user
 return;
}
else if(row1==7 && col1== 4 && row2==7 && col2==2){//this one is for long rock movement.
if(r1==0 && k1== 0){ //control flag because if player played rook and king before,rock is not valid
board[7][0].setPieceType('.');
board[7][2].setPieceType('K');
board[7][3].setPieceType('R');
board[7][4].setPieceType('.');	//sets the board again with new values	
turn++;	//know,other player's turn
}
else{
	cout<<"Invalid move"<<endl;
	return;
}
}
else if(row1==7 && col1== 4 && row2==7 && col2==6){ //this one is for short rock
if(r2==0 && k1== 0){
board[7][7].setPieceType('.');
board[7][6].setPieceType('K');
board[7][5].setPieceType('R');
board[7][4].setPieceType('.');	//sets the board again with new values		
turn++;	//know,other player's turn
}	
else{
	cout<<"Invalid move"<<endl;
	return;
}
}
  	
else{//at here,we must control correctly the pieces and we must add eating pieces each other

char letter=board[row1][col1].getPieceType();
if(letter=='R'){ //if white player choose R
if (row1 != row2 && col1 != col2) { //this is rule of rook.first and secon position's row or col must be equal
    cout << "Invalid rook movement. Rooks can only move vertically or horizontally." << endl;
     return;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	cout<<"Invalid rook movement.You cannot move to your own piece."<<endl;
	 return;
}//if user goes to itself pieces,warns user.Not necessary but just i wanted to warn

else{//controls mechanism is here
if(row1>row2){ //if player wants to go from down to up
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){//if there is a piece 
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
}	
}
else if(row1<row2){//if player wants to go from up to down
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){//if there is a piece 
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
	}
else if(col1>col2){//if player wants to go from right to left
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){//if there is a piece 
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}		
}	
else if(col1<col2){ //if player wants to go from left to right
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){//if there is a piece 
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
}
}//if movement is valid
if(board[row2][col2].getPieceType()!='.'){//and the place where you go has an other player's pieces you eat this 
	if(board[row2][col2].getPieceType()=='r'){//here calculates the points
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}

}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;//makes the new place new piece and makes befor position .
if(row1==7 && col1==0){
	r1=1;//if first rook was played before becomes 1 and you cannot make rock
}
if(row1==7 && col1== 7){
	r2=1;
}//if second rook was played before becomes 1 and you cannot make rock
}
//*******************************************
else if(letter=='B'){ //if user select B
  if (abs(row1 - row2) != abs(col1 - col2)) { //the rule of Bishop piece.They must be equal to each other
        cout << "Invalid bishop movement. Bishops can only move diagonally." << endl;
        return;
    } else if (board[row2][col2].getPieceType() == 'R' ||
               board[row2][col2].getPieceType() == 'B' ||
               board[row2][col2].getPieceType() == 'N' ||
               board[row2][col2].getPieceType() == 'Q' ||
               board[row2][col2].getPieceType() == 'K' ||
               board[row2][col2].getPieceType() == 'P') {
        cout << "Invalid bishop movement. You cannot move to your own piece." << endl;
        return;//if user goes to itself piece
    }
else{
if (row1 < row2) { //if user goes from up to down
    if(col1>col2){ //if goes from right to left
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;//if there is block,warns user
			}
		}
    	}
    	else if(col1<col2){ //if player goes from left to right
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;//if there is block,warns user
			}
		}
		}
} else if (row1 > row2) { //if player goes from down to up
    if(col1>col2){ //if user goes right to left
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;//if there is block,warns user
		}
    	
	}	
	}
	else if(col1<col2){ //if player goes from left to right
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return; //if there is block,warns user
		}    	
	}
		
		
		
		
	}
}
}//if eats other pieces,gets some points
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='r'){
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}
}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
	turn++;//changes the position of pieces and turn is other player's
}
//*******************************************
else if(letter=='N'){ //if user select Knight
	
if (abs((row2-row1)*(row2-row1)+(col2-col1)*(col2-col1))!=5) {
    cout << "Invalid knight movement. Knights can only move in L position." << endl;
    return; //knights can go in L position.İt means distance of coordinate must be 5
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	cout<<"Invalid knight movement.You cannot move to your own piece."<<endl;
	return;
}
else{ //player gets some points if eat other piece
	if(board[row2][col2].getPieceType()!='.'){
		
		
		if(board[row2][col2].getPieceType()=='r'){
			whiteScore+=5;
		}
		else if(board[row2][col2].getPieceType()=='n'){
			whiteScore+=3;
		}
		else if(board[row2][col2].getPieceType()=='b'){
			whiteScore+=3;
		}
		else if(board[row2][col2].getPieceType()=='q'){
			whiteScore+=9;
			
		}
		else if(board[row2][col2].getPieceType()=='p'){
			whiteScore+=1;
		}	
	}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++; //changes the coordinates
}
}
//*******************************************
else if(letter=='Q'){
if ((row1 != row2 && col1 != col2) && (abs(row1 - row2) != abs(col1 - col2)) ) { //Queen is the mix of bishop and rook.Rules are valid for this
    cout << "Invalid Queen movement. Queen can only move vertically or horizontally or diagonally" << endl;
    return;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	cout<<"Invalid Queen movement.You cannot move to your own piece."<<endl;
	return;
}
else{
if(row1==row2 || col1==col2){//it means queen will go horizontal or vertical(rook's feature)
	
	if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
}
	
}

else if(row1<row2){
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
}

if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='r'){
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}

}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
}
else if(abs(row1 - row2) == abs(col1 - col2)){//bishop's feature
	
if (row1 < row2) {
    if(col1>col2){
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
			}
		}
    	}
    	else if(col1<col2){
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
			}
		}
		}
} else if (row1 > row2) {
    if(col1>col2){
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
		}
    	
	}	
	}
	else if(col1<col2){
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
		}    	
	}	
	}
}
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='r'){
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}
}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
}	
}
}
else if(letter=='K'){//if user select King
  if (abs(row1 - row2) > 1 || abs(col1 - col2) > 1) {
        cout << "Invalid King movement. King can only move vertically, horizontally, or diagonally by 1" << endl;
        return;//warns user if user goes by 2 or more
    }

else if (board[row2][col2].getPieceType() == 'R' ||
               board[row2][col2].getPieceType() == 'N' ||
               board[row2][col2].getPieceType() == 'B' ||
               board[row2][col2].getPieceType() == 'Q' ||
               board[row2][col2].getPieceType() == 'K' ||
               board[row2][col2].getPieceType() == 'P') {
        cout << "Invalid King movement. You cannot move to your own piece." << endl;
    }//if user goes to itself position
	else{
	int a,b,i,j;
		for(i=0;i<8;i++){
			for( j=0;j<8;j++){
				if(board[i][j].getPieceType()=='k'){
					a=i;
					b=j;
					break;
				}
				}//finds other player's king position
		}
//king cannot eat another king.I want to prevent this.
if(abs(a-row2==1)){
	if(b==col2 || abs(b-col2)==1){
	cout<<"You cannot move your King to other player's King"<<endl;
	return;
	}	
}
else if(a==row2){
	if(abs(b-col2)==1){
		cout<<"You cannot move your King to other player's King"<<endl;
	return;	
	}
}		
else{
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='r'){
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}
}//if king eats other pieces,gets some points

board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;	
if(row1==7 && col1==0){//this one is for rock.If king played before,rock will not be done
	k1=1;
}
	
}			
}
}
else if(letter=='P'){//if usere select Pawn

if (board[row2][col2].getPieceType() == 'R' ||
               board[row2][col2].getPieceType() == 'N' ||
               board[row2][col2].getPieceType() == 'B' ||
               board[row2][col2].getPieceType() == 'Q' ||
               board[row2][col2].getPieceType() == 'K' ||
               board[row2][col2].getPieceType() == 'P') {
        cout << "Invalid Pawn movement. You cannot move to your own piece." << endl;
    }//if user goes to itself pieces,warns user
else{
if(row1==6){//pawn move can by one or two on horizontal //if position of pawn is int the seventh line(as a coordinate,six)
if(row1<row2){//this player is white and row1 must be smaller than row2 because pawn cannot go back
	cout<<"You cannot move back.This Piece Type is Pawn "<<endl;
	return;
}
else{
if(row1-row2==1){//if row1==6,pawn can go by one or two.İf goes by one,it can eat other player
	if(col1==col2){
		if(board[row2][col2].getPieceType()!='.'){
			cout<<"Invalid move"<<endl;
			return;
		}//if goes by one and there is piece,movement is not valid
		else{
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;	//changes the coordinate
		}
	}
	else if(abs(col2-col1)==1){//if user goes diagnoally by one,it means it will eat a piece
		if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='r'){
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}
	board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;//player gets some points and other player's turn 
}
else{
	cout<<"Invalid move"<<endl;
	return;
}
	}
else{
	cout<<"Invalid move"<<endl;
	return;
}	
}
else if(row1-row2==2){ //if user goes by 2 from its first position
   if(col1==col2){   	//col1 and col2 mut be equal because it can't eat any piece
   	if(board[row2][col2].getPieceType()!='.'){
   		cout<<"Invalid move"<<endl;
   		return;
	   }else if(board[row1-1][col1].getPieceType()!='.'){
	   	cout<<"Invalid move"<<endl;
	   }
   	else{
   			board[row1][col1].setPieceType('.');
            board[row2][col2].setPieceType(letter);
            turn++;//change the coordinates and other player'S turn
	   }
   	}
   	else{
   		cout<<"Invalid move"<<endl;
   		return;
	   }
}	
else{
	cout<<"Invalid move"<<endl;
	return;
}	
}		
}
else if(row1!=6){//if position is not 6(means played before)
	
	if(row1<row2){ //it cant go back
	cout<<"You cannot move back.This Piece Type is Pawn "<<endl;
	return;
}
else{
	if((row1-row2)!=1){//if tries to go by 2,3 or etc.,not allowed
		cout<<"Invalid move"<<endl;
		return;
	}
	else{
		if(col1==col2){ //if wants to go vertically 
			if(board[row2][col2].getPieceType()!='.'){
				cout<<"Invalid move "<<endl;//if there is piece,it cannot go
				return;
			}
else{
		board[row1][col1].setPieceType('.');
            board[row2][col2].setPieceType(letter);
            turn++;//changes the position and other player's turn
}
		}
else if(abs(col2-col1)==1){ //if goes diagonally
	if(board[row2][col2].getPieceType()!='.'){//and the type is white player's type
	if(board[row2][col2].getPieceType()=='r'){
whiteScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='n'){
whiteScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='b'){
whiteScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='q'){
whiteScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='p'){
whiteScore+=1;
	}//gets some point player

	board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++; //change the position of board and other player's turn
}
else{
	cout<<"Invalid move"<<endl;
	return;//if there is your piece at there,you will be warned
}	
}		
}
}		
}
}	
}
} 
}
else if(turn%2==1){//everything is valid for if block from previous if block.There is just differences in rock and pawn movements.
//if letters are capital,now it will be small if small,it will be capital.Also I just changed the positions in rock and pawn places.
//also whiteScores became blackScore
if(board[row1][col1].getPieceType()!='r' && board[row1][col1].getPieceType()!='n'&& 
board[row1][col1].getPieceType()!='b' && 
board[row1][col1].getPieceType()!='q' && 
board[row1][col1].getPieceType()!='k' && 
board[row1][col1].getPieceType()!='p'){
cout<<"invalid piece movement.Place select correct your piece"<<endl;
 return;
}  
else if(row1==0 && col1== 4 && row2==0 && col2==2){ 
if(r3==0 && k1== 0){
board[0][0].setPieceType('.');
board[0][2].setPieceType('k');
board[0][3].setPieceType('r');
board[0][4].setPieceType('.');		
turn++;	
}
else{
	cout<<"Invalid move"<<endl;
	return;
}
}
else if(row1==0 && col1== 4 && row2==0 && col2==6){
if(r4==0 && k2== 0){
board[0][7].setPieceType('.');
board[0][6].setPieceType('k');
board[0][5].setPieceType('r');
board[0][4].setPieceType('.');		
turn++;	
}	
else{
	cout<<"Invalid move"<<endl;
	return;
}
}
else{//at here,we must control correctly the pieces and we must add eating pieces each other
char letter=board[row1][col1].getPieceType();
if(letter=='r'){
if (row1 != row2 && col1 != col2) {
    cout << "Invalid rook movement. Rooks can only move vertically or horizontally." << endl;
     return;
}
else if(board[row2][col2].getPieceType()=='r' ||
board[row2][col2].getPieceType()=='n' ||
board[row2][col2].getPieceType()=='b' ||
board[row2][col2].getPieceType()=='q' ||
board[row2][col2].getPieceType()=='k' ||
board[row2][col2].getPieceType()=='p' ){
	cout<<"Invalid rook movement.You cannot move to your own piece."<<endl;
	 return;
}

else{
if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
}
}
else if(row1<row2){
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
		cout << "Invalid rook movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
}
}
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}
}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
if(row1==0 && col1==0){
	r3=1;
}
if(row1==0 && col1==7){
	r4=1;
}
}
//*******************************************
else if(letter=='b'){
  if (abs(row1 - row2) != abs(col1 - col2)) {
        cout << "Invalid bishop movement. Bishops can only move diagonally." << endl;
       return;
    } else if (board[row2][col2].getPieceType() == 'r' ||
               board[row2][col2].getPieceType() == 'n' ||
               board[row2][col2].getPieceType() == 'b' ||
               board[row2][col2].getPieceType() == 'q' ||
               board[row2][col2].getPieceType() == 'k' ||
               board[row2][col2].getPieceType() == 'p') {
        cout << "Invalid bishop movement. You cannot move to your own piece." << endl;
        return;
    }
else{
if (row1 < row2) {
    if(col1>col2){
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
			}
		}
    	}
    	else if(col1<col2){
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
			}
		}
		}
} else if (row1 > row2) {
    if(col1>col2){
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
		}
    	
	}	
	}
	else if(col1<col2){
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid bishop movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
		}    	
	}
		
		
		
		
	}
}
}	
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}
		else if(board[row2][col2].getPieceType()=='K'){
		cout<<"Game finished.Black player won.Congratualions!!!"<<endl;
		flag1=1;
	}
}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
}
else if(letter=='n'){
	
if (abs((row2-row1)*(row2-row1)+(col2-col1)*(col2-col1))!=5) {
    cout << "Invalid knight movement. Knights can only move in L position." << endl;
}
else if(board[row2][col2].getPieceType()=='r' ||
board[row2][col2].getPieceType()=='n' ||
board[row2][col2].getPieceType()=='b' ||
board[row2][col2].getPieceType()=='q' ||
board[row2][col2].getPieceType()=='k' ||
board[row2][col2].getPieceType()=='p' ){
	cout<<"Invalid knight movement.You cannot move to your own piece."<<endl;
}
else{
	if(board[row2][col2].getPieceType()!='.'){
		
		
		if(board[row2][col2].getPieceType()=='R'){
			whiteScore+=5;
		}
		else if(board[row2][col2].getPieceType()=='N'){
			whiteScore+=3;
		}
		else if(board[row2][col2].getPieceType()=='B'){
			whiteScore+=3;
		}
		else if(board[row2][col2].getPieceType()=='Q'){
			whiteScore+=9;
			
		}
		else if(board[row2][col2].getPieceType()=='P'){
			whiteScore+=1;
		}	
	}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
	turn++;
}
}
else if(letter=='q'){
if ((row1 != row2 && col1 != col2) && (abs(row1 - row2) != abs(col1 - col2)) ) {
    cout << "Invalid Queen movement. Queen can only move vertically or horizontally or diagonally" << endl;
    return;
}
else if(board[row2][col2].getPieceType()=='r' ||
board[row2][col2].getPieceType()=='n' ||
board[row2][col2].getPieceType()=='b' ||
board[row2][col2].getPieceType()=='q' ||
board[row2][col2].getPieceType()=='k' ||
board[row2][col2].getPieceType()=='p' ){
	cout<<"Invalid Queen movement.You cannot move to your own piece."<<endl;
	return;
}
else{
if(row1==row2 || col1==col2){//it means queen will go horizontal or vertical
	
	if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
}	
}
else if(row1<row2){
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
		cout << "Invalid Queen movement. There is a piece blocking the way.Select valid movement" << endl;
        return;
	}
	}
}
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}
		else if(board[row2][col2].getPieceType()=='K'){
		cout<<"Game finished.Black player won.Congratualions!!!"<<endl;
		flag1=1;
	}
}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
}
else if(abs(row1 - row2) == abs(col1 - col2)){
	
if (row1 < row2) {
    if(col1>col2){
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
			}
		}
    	}
    	else if(col1<col2){
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
			}
		}
		}
} else if (row1 > row2) {
    if(col1>col2){
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
		}
    	
	}	
	}
	else if(col1<col2){
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
    		cout << "Invalid Queen movement. There is a piece blocking the way. Select a valid movement" << endl;
            return;
		}    	
	}		
	}
}	
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}
		else if(board[row2][col2].getPieceType()=='K'){
		cout<<"Game finished.Black player won.Congratualions!!!"<<endl;
		flag1=1;
	}
}

board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
}	
}
}
else if(letter=='k'){
  if (abs(row1 - row2) > 1 || abs(col1 - col2) > 1) {
        cout << "Invalid King movement. King can only move vertically, horizontally, or diagonally by 1" << endl;
        return;
    }
else if (board[row2][col2].getPieceType() == 'r' ||
               board[row2][col2].getPieceType() == 'n' ||
               board[row2][col2].getPieceType() == 'b' ||
               board[row2][col2].getPieceType() == 'q' ||
               board[row2][col2].getPieceType() == 'k' ||
               board[row2][col2].getPieceType() == 'p') {
        cout << "Invalid King movement. You cannot move to your own piece." << endl;
    }
	else{
		int a,b,i,j;
		for(i=0;i<8;i++){
			for( j=0;j<8;j++){
				if(board[i][j].getPieceType()=='K'){
					a=i;
					b=j;
					break;
				}
			}
		}
//king cannot eat another king.I want to prevent this.
if(abs(a-row2==1)){
	if(b==col2 || abs(b-col2)==1){
	cout<<"You cannot move your King to other player's King"<<endl;
	return;
	}	
}
else if(a==row2){
	if(abs(b-col2)==1){
		cout<<"You cannot move your King to other player's King"<<endl;
	return;	
	}
}		
else{
if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}
}
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
	turn++;
if(row1==0 && col1==4){
	k2=1;
}	
}			
}
}
else if(letter=='p'){
if (board[row2][col2].getPieceType() == 'r' ||
               board[row2][col2].getPieceType() == 'n' ||
               board[row2][col2].getPieceType() == 'b' ||
               board[row2][col2].getPieceType() == 'q' ||
               board[row2][col2].getPieceType() == 'k' ||
               board[row2][col2].getPieceType() == 'p') {
        cout << "Invalid Pawn movement. You cannot move to your own piece." << endl;
    }
else{
if(row1==1){//pawn move can by one or two on horizontal
if(row2<row1){
	cout<<"You cannot move back.This Piece Type is Pawn "<<endl;
	return;
}
else{
if(row2-row1==1){
	if(col1==col2){
		if(board[row2][col2].getPieceType()!='.'){
			cout<<"Invalid move"<<endl;
			return;
		}
		else{			
board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
		}
	}
	else if(abs(col2-col1)==1){
		if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;	
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}
	board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
}
else{
	cout<<"Invalid move"<<endl;
	return;
}
	}
else{
	cout<<"Invalid move"<<endl;
	return;
}	
}
else if(row2-row1==2){
   if(col1==col2){
   	if(board[row2][col2].getPieceType()!='.'){
   		cout<<"Invalid move"<<endl;
   		return;
	   }
	   else if(board[row1+1][col1].getPieceType()!='.'){
	   	cout<<"Invalid move"<<endl;
	   }
   	else{
   			board[row1][col1].setPieceType('.');
            board[row2][col2].setPieceType(letter);
            turn++;
	   }
   	}
   	else{
   		cout<<"Invalid move"<<endl;
   		return;
	   }
}	
else{
	cout<<"Invalid move"<<endl;
	return;
}	
}		
}
else if(row1!=1){
	
	if(row2<row1){
	cout<<"You cannot move back.This Piece Type is Pawn "<<endl;
	return;
}
else{
	if((row2-row1)!=1){
		cout<<"Invalid move"<<endl;
		return;
	}
	else{
		if(col1==col2){
			if(board[row2][col2].getPieceType()!='.'){
				cout<<"Invalid move"<<endl;
				return;
			}
else{
		board[row1][col1].setPieceType('.');
            board[row2][col2].setPieceType(letter);
            turn++;
}
		}
else if(abs(col2-col1)==1){
	if(board[row2][col2].getPieceType()!='.'){
	if(board[row2][col2].getPieceType()=='R'){
blackScore+=5;
	}
	else if(board[row2][col2].getPieceType()=='N'){
blackScore+=3;
	}	
	else if(board[row2][col2].getPieceType()=='B'){
blackScore+=3;
		
	}
	else if(board[row2][col2].getPieceType()=='Q'){
blackScore+=9;
		
	}
	else if(board[row2][col2].getPieceType()=='P'){
blackScore+=1;
	}

	board[row1][col1].setPieceType('.');
board[row2][col2].setPieceType(letter);
turn++;
}
else{
	cout<<"Invalid move"<<endl;
	return;
}
	
}		
}	
}	
}
}	
}
} 			 			
}	
}
void Chessboard::score()const{ //it prints the scores.
	cout<<"White score: "<<getscore1()<<endl;
	cout<<"Black score: "<<getscore2()<<endl;
	}

bool Chessboard::isvalidmove(int a,int b,int c,int d)const{//this function is for suggest function.Logic is the same for move function
//just instead of adding points,returns true and if in move function return;,at here return false.Everything is same
 int i;
 int row1=a;
 int col1=b;
 int row2=c;
 int col2=d;//keeps the coordinate of input by entered conputer
if(turn%2==0){
if(board[row1][col1].getPieceType()!='R' && board[row1][col1].getPieceType()!='N'&& 
board[row1][col1].getPieceType()!='B' && 
board[row1][col1].getPieceType()!='Q' && 
board[row1][col1].getPieceType()!='K' && 
board[row1][col1].getPieceType()!='P'){
 return false;
}	
//***********
if(board[row1][col1].getPieceType()=='R'){
if (row1 != row2 && col1 != col2) {
     return false;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	 return false;
}

else{
if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
        return false;
	}
}
	
}

else if(row1<row2){
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){
        return false;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
			return false;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}
}
}
return true;
	}
	//**********************
	
	else if(board[row1][col1].getPieceType()=='N'){
if (abs((row2-row1)*(row2-row1)+(col2-col1)*(col2-col1))!=5) {
    return false;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	return false;
}
	else{
		return true;
	}	
	}
//******************************	
	else if(board[row1][col1].getPieceType()=='B'){
 if (abs(row1 - row2) != abs(col1 - col2)) {
        return false;
    } else if (board[row2][col2].getPieceType() == 'R' ||
               board[row2][col2].getPieceType() == 'B' ||
               board[row2][col2].getPieceType() == 'N' ||
               board[row2][col2].getPieceType() == 'Q' ||
               board[row2][col2].getPieceType() == 'K' ||
               board[row2][col2].getPieceType() == 'P') {
        return false;
    }
else{
if (row1 < row2) {
    int a = col1;
    for (i = row1 + 1; i < row2; i++) {
        if (board[i][a++].getPieceType() != '.') {
            return false;
        }
    }
} else if (row1 > row2) {
    int a = col1;
    for (i = row1 - 1; i > row2; i--) {
        if (board[i][a++].getPieceType() != '.') {
            return false;
        }
    }
}
else{
	return true;
}
}	
}
	else if(board[row1][col1].getPieceType()=='Q'){
if ((row1 != row2 && col1 != col2) && (abs(row1 - row2) != abs(col1 - col2)) ) {
    return false;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	return false;
}
else{
if(row1==row2 || col1==col2){//it means queen will go horizontal or vertical
	
	if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
        return false;
	}
}	
}
else if(row1<row2){
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){
        return false;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}
}
else{
	return true;
}
}
else if(abs(row1 - row2) == abs(col1 - col2)){
	
if (row1 < row2) {
    if(col1>col2){
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
            return false;
			}
		}
    	}
    	else if(col1<col2){
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
            return false;
			}
		}
		}
} else if (row1 > row2) {
    if(col1>col2){
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
            return false;
		}
    	
	}	
	}
	else if(col1<col2){
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
            return false;
		}    	
	}
}
}
	else{
		return true;
	}
}	
}	
	}
	//***********************
	else if(board[row1][col1].getPieceType()=='K'){
  if (abs(row1 - row2) > 1 || abs(col1 - col2) > 1) {
        return false;
    }
else if (board[row2][col2].getPieceType() == 'R' ||
               board[row2][col2].getPieceType() == 'N' ||
               board[row2][col2].getPieceType() == 'B' ||
               board[row2][col2].getPieceType() == 'Q' ||
               board[row2][col2].getPieceType() == 'K' ||
               board[row2][col2].getPieceType() == 'P') {
return false;
    }
	else{
		int a,b,i,j;
		for(i=0;i<8;i++){
			for( j=0;j<8;j++){
				if(board[i][j].getPieceType()!='k'){
					a=i;
					b=j;
					break;
				}
			}
		}
//king cannot eat another king.I want to prevent this.
if(abs(i-row2)==1 || abs(j-col2)==1 || sqrt(i*i+col2*col2)==2 || sqrt(j*j+row1*row1)==2 ){
	return false;
}		
else{
return true;			
}	
}
}
		else if(board[row1][col1].getPieceType()=='P'){
		
if (board[row2][col2].getPieceType() == 'R' ||
               board[row2][col2].getPieceType() == 'N' ||
               board[row2][col2].getPieceType() == 'B' ||
               board[row2][col2].getPieceType() == 'Q' ||
               board[row2][col2].getPieceType() == 'K' ||
               board[row2][col2].getPieceType() == 'P') {
               	return false;
    }
else{
if(row1==6){//pawn move can by one or two on horizontal
if(row1<=row2){
	return false;
}
else{
if(row1-row2==1){
	if(col1==col2){
		if(board[row2][col2].getPieceType()!='.'){
			return false;
		}
		else{			
return true;
		}
	}
	else if(abs(col2-col1)==1){
		if(board[row2][col2].getPieceType()!='.'){
return true;
}
else{
	return false;
}
	}
else{
	return false;
}	
}
else if(row1-row2==2){
   if(col1==col2){   	
   	if(board[row2][col2].getPieceType()!='.'){
   		return false;
	   }else if(board[row1-1][col1].getPieceType()!='.'){
return false;
	   }
   	else{
   		return true;
	   }
   	}
   	else{
   		return false;
	   }
}	
else{
	return false;
}	
}		
}
else if(row1!=6){	
	if(row1<row2){
	return false;
}
else{
	if((row1-row2)!=1){
		return false;
	}
	else{
		if(col1==col2){
			if(board[row2][col2].getPieceType()!='.'){
				return false;
			}
else{
	return true;
}
		}
else if(abs(col2-col1)==1){
	if(board[row2][col2].getPieceType()!='.'){
return true;
}
else{
	return false;
}	
}		
}
}		
}
}	
}
}
else if(turn%2==1){
if(board[row1][col1].getPieceType()!='r' && board[row1][col1].getPieceType()!='n'&& 
board[row1][col1].getPieceType()!='b' && 
board[row1][col1].getPieceType()!='q' && 
board[row1][col1].getPieceType()!='k' && 
board[row1][col1].getPieceType()!='p'){
 return false;
}	
//***********
if(board[row1][col1].getPieceType()=='r'){
if (row1 != row2 && col1 != col2) {
     return false;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	 return false;
}
else{
if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
        return false;
	}
}	
}
else if(row1<row2){
	for(i=row1+1;i<row2;i++){
	if(board[i][col1].getPieceType()!='.'){
        return false;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}
}
}
return true;
	}
	else if(board[row1][col1].getPieceType()=='n'){
if (abs((row2-row1)*(row2-row1)+(col2-col1)*(col2-col1))!=5) {
    return false;
}
else if(board[row2][col2].getPieceType()=='R' ||
board[row2][col2].getPieceType()=='N' ||
board[row2][col2].getPieceType()=='B' ||
board[row2][col2].getPieceType()=='Q' ||
board[row2][col2].getPieceType()=='K' ||
board[row2][col2].getPieceType()=='P' ){
	return false;
}
	else{
		return true;
	}	
	}	
	else if(board[row1][col1].getPieceType()=='b'){
 if (abs(row1 - row2) != abs(col1 - col2)) {
        return false;
    } else if (board[row2][col2].getPieceType() == 'r' ||
               board[row2][col2].getPieceType() == 'b' ||
               board[row2][col2].getPieceType() == 'n' ||
               board[row2][col2].getPieceType() == 'q' ||
               board[row2][col2].getPieceType() == 'k' ||
               board[row2][col2].getPieceType() == 'p') {
        return false;
    }
else{
if (row1 < row2) {
    if(col1>col2){
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
            return false;
			}
		}
    	}
    	else if(col1<col2){
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
            return false;
			}
		}
		}
} else if (row1 > row2) {
    if(col1>col2){
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
            return false;
		}
    	
	}	
	}
	else if(col1<col2){
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
            return false;
		}    	
	}	
	}
}
}	
}
	else if(board[row1][col1].getPieceType()=='q'){
if ((row1 != row2 && col1 != col2) && (abs(row1 - row2) != abs(col1 - col2)) ) {
    return false;
}
else if(board[row2][col2].getPieceType()=='r' ||
board[row2][col2].getPieceType()=='n' ||
board[row2][col2].getPieceType()=='b' ||
board[row2][col2].getPieceType()=='q' ||
board[row2][col2].getPieceType()=='k' ||
board[row2][col2].getPieceType()=='p' ){
	return false;
}
else{
if(row1==row2 || col1==col2){//it means queen will go horizontal or vertical
	
	if(row1>row2){
for(i=row1-1;i>row2;i--){
	if(board[i][col1].getPieceType()!='.'){
        return false;
	}
}	
}
else if(row1<row2){
	for(i=row1+1;i<row2;i++){
			if(board[i][col1].getPieceType()!='.'){
        return false;
	}
	}
	}
else if(col1>col2){
for(i=col1-1;i>col2;i--){
		if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}		
}	
else if(col1<col2){
	for(i=col1+1;i<col2;i++){
			if(board[row1][i].getPieceType()!='.'){
        return false;
	}
	}
}
else{
	return true;
}
}
else if(abs(row1 - row2) == abs(col1 - col2)){
	
if (row1 < row2) {
    if(col1>col2){
    	int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][--a].getPieceType()!='.'){
            return false;
			}
		}
    	}
    	else if(col1<col2){
    		int a=col1;
    	for(int i=row1+1;i<row2;i++){
    		if(board[i][++a].getPieceType()!='.'){
            return false;
			}
		}
		}
} else if (row1 > row2) {
    if(col1>col2){
    int	a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][--a].getPieceType()!='.'){
            return false;
		}
    	
	}	
	}
	else if(col1<col2){
	int a=col1;
    for(int i=row1-1;i>row2;i--){
    	if(board[i][++a].getPieceType()!='.'){
            return false;
		}    	
	}		
	}
}
	else{
		return true;
	}
}	
}	
	}
	//***********************
	else if(board[row1][col1].getPieceType()=='k'){
  if (abs(row1 - row2) > 1 || abs(col1 - col2) > 1) {
        return false;
    }
else if (board[row2][col2].getPieceType() == 'r' ||
               board[row2][col2].getPieceType() == 'n' ||
               board[row2][col2].getPieceType() == 'b' ||
               board[row2][col2].getPieceType() == 'q' ||
               board[row2][col2].getPieceType() == 'k' ||
               board[row2][col2].getPieceType() == 'p') {
return false;
    }
	else{
		int a,b,i,j;
		for(i=0;i<8;i++){
			for( j=0;j<8;j++){
				if(board[i][j].getPieceType()!='k'){
					a=i;
					b=j;
					break;
				}
			}
		}
//king cannot eat another king.I want to prevent this.
if(abs(i-row2)==1 || abs(j-col2)==1 || sqrt(i*i+col2*col2)==2 || sqrt(j*j+row1*row1)==2 ){
	return false;
}		
else{
return true;			
}
		
}
	}
		else if(board[row1][col1].getPieceType()=='p'){
		
if (board[row2][col2].getPieceType() == 'r' ||
               board[row2][col2].getPieceType() == 'n' ||
               board[row2][col2].getPieceType() == 'b' ||
               board[row2][col2].getPieceType() == 'q' ||
               board[row2][col2].getPieceType() == 'k' ||
               board[row2][col2].getPieceType() == 'p') {
return false;
    }
else{
if(row1==1){//pawn move can by one or two on horizontal
if(row2<row1){
	return false;
}
else{
if(row2-row1==1){
	if(col1==col2){
		if(board[row2][col2].getPieceType()!='.'){
			return false;
		}
		else{			
return true;
		}
	}
	else if(abs(col2-col1)==1){
		if(board[row2][col2].getPieceType()!='.'){
return true;
}
else{
	return false;
}
	}
else{
	return false;
}	
}
else if(row2-row1==2){
   if(col1==col2){
   	if(board[row2][col2].getPieceType()!='.'){
   		return false;
	   }
	   else if(board[row1+1][col1].getPieceType()!='.'){
	   	return false;
	   }
   	else{
   	return true;
	   }
   	}
   	else{
   		return false;
	   }
}	
else{
	return false;
}	
}		
}
else if(row1!=1){
	
	if(row2<row1){
	return false;
}
else{
	if((row2-row1)!=1){
		return false;
	}
	else{
		if(col1==col2){
			if(board[row2][col2].getPieceType()!='.'){
				return false;
			}
else{
return true;
}
		}
else if(abs(col2-col1)==1){
	if(board[row2][col2].getPieceType()!='.'){
return true;
}
else{
	return false;
}	
}		
}	
}	
}
}	
}		
}
}
void Chessboard::suggest() {//ther is logic of suggest function here
    int number1, number2, number3, number4;//to keep inputs as integer
    bool found_capturing_move = false;
    // Check for capturing moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (turn % 2 == 0 && board[i][j].getPieceType() != '.') {
                // For each white piece, check for all possible capturing moves
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        if (isvalidmove(i, j, k, l) && board[k][l].getPieceType() != '.' &&
                            !(board[k][l].getPieceType() == 'R' || board[k][l].getPieceType() == 'N' ||
                              board[k][l].getPieceType() == 'B' || board[k][l].getPieceType() == 'Q' ||
                              board[k][l].getPieceType() == 'K' || board[k][l].getPieceType() == 'P')) {//if black pieces can be eaten,it eats
                            found_capturing_move = true;//if founded,returns true
                            cout << "You can play " << char('a' + j) << 8 - i << char('a' + l) << 8 - k << endl;
                            number1 = i;//assigns i,j,k,l values to number1,2,3,4
                            number2 = j;
                            number3 = k;
                            number4 = l;
                            break;
                        }
                    }
                    if (found_capturing_move) {
                        break;
                    }
                }
            } else if (turn % 2 == 1 && board[i][j].getPieceType() != '.') {
                // For each black piece, check for all possible capturing moves
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        if (isvalidmove(i, j, k, l) && board[k][l].getPieceType() != '.' &&
                            !(board[k][l].getPieceType() == 'r' || board[k][l].getPieceType() == 'n' ||
                              board[k][l].getPieceType() == 'b' || board[k][l].getPieceType() == 'q' ||
                              board[k][l].getPieceType() == 'k' || board[k][l].getPieceType() == 'p')) {//if black pieces can be eaten,it eats
                            found_capturing_move = true;//if founded,returns true
                            cout << "You can play " << char('a' + j) << 8 - i << char('a' + l) << 8 - k << endl;
                            number1 = i;
                            number2 = j;
                            number3 = k;
                            number4 = l;
                            break;
                        }
                    }
                    if (found_capturing_move) {//if true,break  
                        break;
                    }
                }
            }
        }
    }

    if (!found_capturing_move) {
        // If no capturing move found, use the random logic
        do {
            number1 = rand() % 8;
            number2 = rand() % 8;
            number3 = rand() % 8;
            number4 = rand() % 8;
        } while (!isvalidmove(number1, number2, number3, number4));//until found valid moves,produce random moves
        cout << "You can play " << char('a' + number2) << 8 - number1 << char('a' + number4) << 8 - number3 << endl;
    }
}
void Chessboard::ischeckmate(){//this function is checkmate mechanism.Logic is same for move function
//if there is no false statemend,it means there is check position.Just we need to find king positions and row 2 anc col2 is the same with these
if(turn%2==1){//if turn is of black player
int x,y;
int a,b;	
for(int i=0;i<8;i++){
	for(int j=0;j<8;j++){
		if(board[i][j].getPieceType()=='k'){
		x=i;
		y=j;
		break;	//find the  position of black king
		}
	}
}//we find the coordinate of the piece.
for(int i=0;i<8;i++){
	for(int j=0;j<8;j++){
		if(board[i][j].getPieceType()=='P'){//if other player's piecetype is pawn
			if(board[i-1][j+1].getPieceType()=='k' || board[i-1][j-1].getPieceType()=='k'){
				mate2=1;
				cout<<"Check!"<<endl;//controls this pawn can make check or not.If it is,game over
			}	
		}
	    if(board[i][j].getPieceType()=='R'){//if other player's piecetype is rock(logic is the same wtih move function)
	        a=i;
		b=j;
	
			if(a>x){
for(int k=a-1;k>=x;k--){
	if(board[k][b].getPieceType()!='.'){
        if(board[k][b].getPieceType()=='k'){
        	mate2=1;
        	cout<<"Check"<<endl;
		}

	}
}	
}
else if(a<x){
	for(int k=a+1;k<=x;k++){
			if(board[k][b].getPieceType()!='.'){
				if(board[k][b].getPieceType()=='k'){
					mate2=1;
				cout<<"Check!"<<endl;
				}
	}
	}
	}
else if(b>y){
for(int k=b-1;k>=y;k--){
		if(board[a][k].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='k'){
					mate2=1;
				cout<<"Check!"<<endl;
				}

	}
	}		
}	
else if(b<y){
	for(int k=b+1;k<=y;k++){
			if(board[a][k].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='k'){
					mate2=1;
				cout<<"Check!"<<endl;

				} 
	}
	}
}		
		}
		if(board[i][j].getPieceType()=='N'){//if other player's piecetype is knight
		a=i;
		b=j;	
	if (abs((x-a)*(x-a)+(y-b)*(y-b))==5) {
			mate2=1;
				cout<<"Check!"<<endl;
}				
		}
		if(board[i][j].getPieceType()=='B'){//if other player's piecetype is bishop
		a=i;
		b=j;
		if (abs(a - x)== abs(b - y)){
		if (a < x) {
        if(b>y){
    	int l=b;
    	for(int k=l+1;k<=x;k++){
    		if(board[k][--l].getPieceType()!='.'){
            if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
			}
		}
    	}
    	else if(b<y){
    		int l=b;
    	for(int k=a+1;k<=x;k++){
    		if(board[k][++l].getPieceType()!='.'){
  if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
			}
		
		}
		}
} else if (a > x) {
    if(b>y){
    int	l=b;
    for(int k=a-1;k>=x;k--){
    	if(board[k][--l].getPieceType()!='.'){
      if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
		}
    	
	}	
	}
	else if(b<y){
	int l=b;
    for(int k=a-1;i>=x;i--){
    	if(board[k][++l].getPieceType()!='.'){
    	  if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
		}    	
	}
	
	}
}	
}		
		}
		if(board[i][j].getPieceType()=='Q'){//if other player's piecetype is queen
		a=i;
		b=j;
if (a == x || b== y) {	
			if(a>x){
for(int k=a-1;k>=x;k--){
	if(board[k][b].getPieceType()!='.'){
        if(board[k][b].getPieceType()=='k'){
        	mate2=1;
        	cout<<"Check"<<endl;
		}
	}
}	
}
else if(a<x){
	for(int k=a+1;k<=x;k++){
			if(board[k][b].getPieceType()!='.'){
				if(board[k][b].getPieceType()=='k'){
					mate2=1;
				cout<<"Check!"<<endl;
				}
	}
	}
	}
else if(b>y){
for(int k=b-1;k>=y;k--){
		if(board[a][k].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='k'){
					mate2=1;
				cout<<"Check!"<<endl;
				}

	}
	}		
}	
else if(b<y){
	for(int k=b+1;k<=y;k++){
			if(board[a][i].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='k'){
					mate2=1;
				cout<<"Check!"<<endl;
				} 

	}
	}
}		
}
else if (abs(a - x)== abs(b - y)){
		
		if (a < x) {
    if(b>y){
    	int l=b;
    	for(int k=l+1;k<=x;k++){
    		if(board[k][--l].getPieceType()!='.'){
            if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
			}
		}
    	}
    	else if(b<y){
    		int l=b;
    	for(int k=a+1;k<=x;k++){
    		if(board[k][++l].getPieceType()!='.'){
  if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
			}
		
		}
		}
} else if (a > x) {
    if(b>y){
    int	l=b;
    for(int k=a-1;k>=x;k--){
    	if(board[k][--l].getPieceType()!='.'){
      if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
		}
    	
	}	
	}
	else if(b<y){
	int l=b;
    for(int k=a-1;i>=x;i--){
    	if(board[k][++l].getPieceType()!='.'){
    	  if(board[k][l].getPieceType()=='k'){
            	mate2=1;
            	cout<<"Check!"<<endl;
			}
		}    	
}
	
}
}	
}
}			
}	
}			
}	
else if(turn%2==0){//if turn is of white player
int x,y;
int a,b;	
for(int i=0;i<8;i++){
	for(int j=0;j<8;j++){
		if(board[i][j].getPieceType()=='K'){
		x=i;
		y=j;
		break;	
		}
	}
}//we find the coordinate of the piece.
for(int i=0;i<8;i++){
	for(int j=0;j<8;j++){
		if(board[i][j].getPieceType()=='p'){
			if(board[i+1][j+1].getPieceType()=='K' || board[i+1][j-1].getPieceType()=='K'){
				mate1=1;
				cout<<"Check!"<<endl;
			}	
		}//******************************************************
	    if(board[i][j].getPieceType()=='r'){
	    a=i;
		b=j;
if (a == x || b== y) {	
			if(a>x){
for(int k=a-1;k>=x;k--){
	if(board[k][b].getPieceType()!='.'){
        if(board[k][b].getPieceType()=='K'){
        	mate1=1;
        	cout<<"Check"<<endl;
		}
	}
}	
}
else if(a<x){
	for(int k=a+1;k<=x;k++){
			if(board[k][b].getPieceType()!='.'){
				if(board[k][b].getPieceType()=='K'){
					mate1=1;
				cout<<"Check!"<<endl;
				}
	}
	}
	}
else if(b>y){
for(int k=b-1;k>=y;k--){
		if(board[a][k].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='K'){
					mate1=1;
				cout<<"Check!"<<endl;
				}

	}
	}		
}	
else if(b<y){
	for(int k=b+1;k<=y;k++){
			if(board[a][i].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='K'){
					mate1=1;
				cout<<"Check!"<<endl;
				} 
	}
	}
}		
}
		}
		if(board[i][j].getPieceType()=='n'){
		a=i;
		b=j;		
	if (abs((x-a)*(x-a)+(y-b)*(y-b))==5) {
			mate1=1;
				cout<<"Check!"<<endl;
}
		
						
		}
		a=i;
		b=j;
		if(board[i][j].getPieceType()=='b'){
		a=i;
		b=j;
		if (abs(a - x)== abs(b - y)){	
		if (a < x) {
    if(b>y){
    	int l=b;
    	for(int k=l+1;k<=x;k++){
    		if(board[k][--l].getPieceType()!='.'){
            if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
			}
		}
    	}
    	else if(b<y){
    		int l=b;
    	for(int k=a+1;k<=x;k++){
    		if(board[k][++l].getPieceType()!='.'){
  if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
			}
		
		}
		}
} else if (a > x) {
    if(b>y){
    int	l=b;
    for(int k=a-1;k>=x;k--){
    	if(board[k][--l].getPieceType()!='.'){
      if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Chec!"<<endl;
			}
		}
    	
	}	
	}
	else if(b<y){
	int l=b;
    for(int k=a-1;i>=x;i--){
    	if(board[k][++l].getPieceType()!='.'){
    	  if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
		}    	
	}
	
	}
}	
}		
		}
		if(board[i][j].getPieceType()=='q'){
		a=i;
		b=j;
if (a == x || b== y) {	
			if(a>x){
for(int k=a-1;k>=x;k--){
	if(board[k][b].getPieceType()!='.'){
        if(board[k][b].getPieceType()=='K'){
        	mate1=1;
        	cout<<"Check"<<endl;
		}
	}
}	
}
else if(a<x){
	for(int k=a+1;k<=x;k++){
			if(board[k][b].getPieceType()!='.'){
				if(board[k][b].getPieceType()=='K'){
					mate1=1;
				cout<<"Check!"<<endl;
				}
	}
	}
	}
else if(b>y){
for(int k=b-1;k>=y;k--){
		if(board[a][k].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='K'){
					mate1=1;
				cout<<"Check!"<<endl;
				}
	}
	}		
}	
else if(b<y){
	for(int k=b+1;k<=y;k++){
			if(board[a][i].getPieceType()!='.'){
	if(board[a][k].getPieceType()=='K'){
					mate1=1;
				cout<<"Check!"<<endl;
				} 
	}
	}
}		
}
else if (abs(a - x)== abs(b - y)){
		
		if (a < x) {
    if(b>y){
    	int l=b;
    	for(int k=l+1;k<=x;k++){
    		if(board[k][--l].getPieceType()!='.'){
            if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
			}
		}
    	}
    	else if(b<y){
    		int l=b;
    	for(int k=a+1;k<=x;k++){
    		if(board[k][++l].getPieceType()!='.'){
  if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
			}
		
		}
		}
} else if (a > x) {
    if(b>y){
    int	l=b;
    for(int k=a-1;k>=x;k--){
    	if(board[k][--l].getPieceType()!='.'){
      if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
		}
    	
	}	
	}
	else if(b<y){
	int l=b;
    for(int k=a-1;i>=x;i--){
    	if(board[k][++l].getPieceType()!='.'){
    	  if(board[k][l].getPieceType()=='K'){
            	mate1=1;
            	cout<<"Check!"<<endl;
			}
		}    	
	}
	
	}
}	
}
			}			
	}	
}	
}			
}
void Chessboard::writefile()const{//write the board positions to the file
	  ofstream outFile("Board.txt",ios::app);
   if (!outFile.is_open()) {
        cerr << "Error opening file: Board.txt"<< endl; //if there is no file
        return;
    }
    outFile << "Current Chess Board State:" << endl;
    for (int i = 0; i < 8; i++) {
        if (i != 8) {
            outFile << 8 - i << " | ";
        }
        for (int j = 0; j < 8; j++) {
            outFile << board[i][j].getPieceType() << "  ";
        }
        outFile << endl;
    }
    outFile << "    ";
    for (int i = 0; i < 22; i++) {
        outFile << "-";
    }
    outFile << endl << "    ";
    for (int i = 0; i < 8; i++) {
        outFile << char('a' + i) << "  ";
    }
    outFile << endl << endl;
    outFile.close();
}	
void Chessboard::underattack(int k,int l){//if black pieces are in underattack,black player loses points
if(board[k][l].getPieceType()=='p')
blackScore=blackScore-0.5;
if(board[k][l].getPieceType()=='b')
blackScore=blackScore-1.5;
if(board[k][l].getPieceType()=='n')
blackScore=blackScore-1.5;
if(board[k][l].getPieceType()=='q')
blackScore=blackScore-4.5;
if(board[k][l].getPieceType()=='r')
blackScore=blackScore-2.5;
}
void Chessboard::underattack2(int k,int l){//if white pieces are in underattack,white player loses points
if(board[k][l].getPieceType()=='P')
whiteScore=whiteScore-0.5;
if(board[k][l].getPieceType()=='B')
whiteScore=whiteScore-1.5;
if(board[k][l].getPieceType()=='N')
whiteScore=whiteScore-1.5;
if(board[k][l].getPieceType()=='Q')
whiteScore=whiteScore-4.5;
if(board[k][l].getPieceType()=='R')
whiteScore=whiteScore-2.5;
}	
void Chessboard::isunderattack(){//controls the pieces are in under attack or not
//logic is the same with move function.İf pieces can eat other player's piece,player will lose some points
if(turn%2==1){
	for(int i=0;i<8;i++){//these four for loop for determine positin of the boards
		for(int j=0;j<8;j++){
			for(int k=0;k<8;k++){
				for(int l=0;l<8;l++){
		if(board[i][j].getPieceType()=='R'){
			if (i == k || j == l) {
if(i>k){
for(int m=i-1;m>l;m--){
	if(board[m][j].getPieceType()!='.'){
   underattack(m,j);
   break;
	}
}
}
else if(i<k){
	for(int m=i+1;m<k;m++){
			if(board[m][j].getPieceType()!='.'){
        underattack(m,j);
        break;
	}
	}
	}
else if(j>l){
for(int m=j-1;m>l;m--){
		if(board[i][m].getPieceType()!='.'){
		underattack(i,m);
		break;
	}
	}		
}	
else if(j<l){
	for(int m=j+1;m<l;m++){
			if(board[i][m].getPieceType()!='.'){
 underattack(i,m);
 break;
	}
	}
}
}
		}			
			if(board[i][j].getPieceType()=='N'){
			if (abs((k-i)*(k-i)+(l-j)*(l-j))==5) {
 underattack(k,l);
 break;
}
		}			
			if(board[i][j].getPieceType()=='B'){
			 if (abs(i - k) == abs(j - l)) {
    if (i < k) {
    int a = j;
    for (int m = i + 1; m < k; m++) {
        if (board[m][a++].getPieceType() != '.') {
            underattack(m,a);
            break;
        }
    }
} else if (i > k) {
    int a = j;
    for (int m = i - 1; m > k; m--) {
        if (board[m][a++].getPieceType() != '.') {
          underattack(m,a);
          break;
        }
    }
}	        
    } 	
		}			
			if(board[i][j].getPieceType()=='Q'){
			if (i == k || j == l) {
if(i>k){
for(int m=i-1;m>k;m--){
	if(board[m][j].getPieceType()!='.'){
  underattack(m,j);
  break;
	}
}	
}
else if(i<k){
	for(int m=i+1;m<k;m++){
			if(board[m][j].getPieceType()!='.'){
       underattack(m,j);
       break;
	}
	}
	}
else if(j>l){
for(int m=j-1;m>l;m--){
		if(board[i][m].getPieceType()!='.'){
	underattack(i,m);
	break;
	}
	}		
}	
else if(j<l){
	for(int m=j+1;m<l;m++){
			if(board[i][m].getPieceType()!='.'){
        underattack(i,m);
        break;
	}
	}
}
}
	    if (i < k) {
    int a = j;
    for (int m = i + 1; m < k; m++) {
        if (board[m][a++].getPieceType() != '.') {
            underattack(m,a);
            break;
        }
    }
} else if (i > k) {
    int a = j;
    for (int m = i - 1; m > k; m--) {
        if (board[m][a++].getPieceType() != '.') {
            underattack(m,a);
            break;
        }
    }
}        
    } 			
if(board[i][j].getPieceType()=='P'){		
if(i>k){
if(i-k==1){

if(abs(l-j)==1){
		if(board[k][l].getPieceType()!='.'){	
			underattack(k,l);
			break;
}
}	
}	
}
}		
}							
}
}			
}
}
else if(turn%2==0){

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			for(int k=0;k<8;k++){
				for(int l=0;l<8;l++){
		if(board[i][j].getPieceType()=='r'){
			if (i == k || j == l) {
if(i>k){
for(int m=i-1;m>l;m--){
	if(board[m][j].getPieceType()!='.'){
   underattack2(m,j);
   break;
	}
}	
}
else if(i<k){
	for(int m=i+1;m<k;m++){
			if(board[m][j].getPieceType()!='.'){
        underattack2(m,j);
        break;
	}
	}
	}
else if(j>l){
for(int m=j-1;m>l;m--){
		if(board[i][m].getPieceType()!='.'){
		underattack2(i,m);
		break;
	}
	}		
}	
else if(j<l){
	for(int m=j+1;m<l;m++){
			if(board[i][m].getPieceType()!='.'){
 underattack2(i,m);
 break;
	}
	}
}
}
		}			
			if(board[i][j].getPieceType()=='n'){
			if (abs((k-i)*(k-i)+(l-j)*(l-j))==5) {
 underattack2(k,l);
 break;
}
		}			
			if(board[i][j].getPieceType()=='b'){
			 if (abs(i - k) == abs(j - l)) {
    if (i < k) {
    int a = j;
    for (int m = i + 1; m < k; m++) {
        if (board[m][a++].getPieceType() != '.') {
            underattack2(m,a);
            break;
        }
    }
} else if (i > k) {
    int a = j;
    for (int m = i - 1; m > k; m--) {
        if (board[m][a++].getPieceType() != '.') {
          underattack2(m,a);
          break;
        }
    }
}
} 
    }			
			if(board[i][j].getPieceType()=='q'){
			if (i == k || j == l) {
if(i>k){
for(int m=i-1;m>k;m--){
	if(board[m][j].getPieceType()!='.'){
  underattack2(m,j);
  break;
	}
}	
}
else if(i<k){
	for(int m=i+1;m<k;m++){
			if(board[m][j].getPieceType()!='.'){
       underattack2(m,j);
	break;
	}
	}
	}
else if(j>l){
for(int m=j-1;m>l;m--){
		if(board[i][m].getPieceType()!='.'){
	underattack2(i,m);
	break;
	}
	}		
}	
else if(j<l){
	for(int m=j+1;m<l;m++){
			if(board[i][m].getPieceType()!='.'){
        underattack2(i,m);
        break;
	}
	}
}
}
   if (i < k) {
    int a = j;
    for (int m = i + 1; m < k; m++) {
        if (board[m][a++].getPieceType() != '.') {
            underattack2(m,a);
            break;
        }
    }
} else if (i > k) {
    int a = j;
    for (int m = i - 1; m > k; m--) {
        if (board[m][a++].getPieceType() != '.') {
            underattack2(m,a);
            break;
        }
    }
}	        
    } 			
if(board[i][j].getPieceType()=='p'){
			
		
if(i<k){
if(i-k==1){

if(abs(l-j)==1){
		if(board[k][l].getPieceType()!='.'){	
			underattack2(k,l);
break;
}
}	
}	
}
}
}			
}
}
}
}
}//logic was the same.
      
