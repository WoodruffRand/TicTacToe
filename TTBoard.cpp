///////////////////////////////////////
//Name		:		Randall Woodruff
//Class		:		CSC 122
//Date		:		10/2/13
//File		:		TTBoard.cpp
//Description: This is a class that defines the tick tac toe board.  
// Board Class simplifies IO needs of main program and provides safety checks including 
//1. Checking and preventing out of range board indexes 
//2. Blocks Attempts to set invalid player indicators on board
//3. Check if game has resulted in win loss or tie
//Board Class Also includes methods to facilitate recursive searches including
//1. Weather a cell has been used 
//2. If game has concluded and if so what is the result
//3. Unset cell function 

#include "TTBoard.h"
#include <iostream>
#include <string>

using namespace std;

//Function: TTBoard(void)
//Usage: TTBoard board=TTBoard(void);
//Description: sets up empty tick tack toe board
TTBoard::TTBoard(void)
{	//setup board grid
	
	lP= 179;
	f= 196;
	t= 197;
	boardGrid[0]="\t\t1|2|3";
	boardGrid[1]="\t\t4|5|6";
	boardGrid[2]="\t\t7|8|9";
	//set board to empty
	for(int i=0;i<nCol;i++){
		for(int j=0;j<nRow;j++){
			board[i][j]='e';// e used to represent empty cell 
		}//end inner for loop
		cout<<endl;
	}//end out for loop 
}

//deconstructor 
TTBoard::~TTBoard(void)
{
}

//Function: setSquare
//Usage: bool flag=setSquare(int x, int y, char move)
//x: board index (0-8)
//move: your x or 0
//Description: function to store new moves into board
//contains bounds checking to make sure move is inside board
//as well as checks to see if cell is already taken and 
//checks to make sure that char is either x or o
//if board is unable to accept move, returns false, if move set, returns true 
bool TTBoard::setSquare(int xb, char move){
	if(xb>8) {
		cout<< "Invalid board index."<<endl;	
		return false; //checks that x and y are in range 
	}
	int y = xb%nCol;
	int x = xb/nRow;
		
	if(move!='x'&&move!='o'){//check user provided correct character
		cout<<"invalid board character"<<endl;
		return false;//returns false to indicate turn not completed 
	}
	
	if(board[x][y]=='e'){//checks that board spot is empty 
		board[x][y]=move;
		return true;//move successful
	}else{
		cout<<"error loading move, cell already taken"<<endl;
		return false;//move not successful 
	}
}


//Function: unsetSquare
//Usage: void unsetSquare(int x)
//x: board index (0-8)
//Description: Removes any moves from given index.
//Designed primarily when building recursive search trees 
void TTBoard::unsetSquare(int xb){
	if (xb>8) {
		cout<<"invalid index on emptyCell check"<<endl;
		return;
	}else{
		int y = xb%nCol;
		int x = xb/nRow;

		board[x][y]='e';
		return;
	}

}


//Function: cellEmpty()
//Usage:bool flag= cellEmpty(int x);
//Description: checks given board index(0-8) if cell is takes 
bool TTBoard::cellEmpty(int xb){
	if (xb>8) {
		cout<<"invlaid index on empyuCell check"<<endl;
		return false;
	}
	int y = xb%nCol;
	int x = xb/nRow;
	
	if(board[x][y]=='e') return true;
	else return false; 
}

//function: cout<<TTBoard
//Usage: cout<<TTBoard;
//Description: Overloaded operator to be able to 
//Directly  input TTBoard object to cout stream 
ostream& operator<<(ostream& os,const TTBoard& temp){
	os<<endl<<endl;
	for(int i=0;i<temp.nCol;i++){
		os<<" ";
		for(int j=0;j<temp.nRow;j++){
			if(temp.board[i][j]=='e') os<<' ';
			else os<<temp.board[i][j];
			if(j<2) os<<"|";
			else os<<temp.boardGrid[i]<< endl;
			}
		os<<endl;
		if(i<2) os<<"-------\t\t-------"<<endl;
	}
	return os;
}

//Function: print
//Usage: void print()
//Description: prints current board state to screen along with index map for player to use 
void TTBoard::print(){
	cout<<endl<<endl;
	for(int i=0;i<nCol;i++){
		cout<<" ";
		for(int j=0;j<nRow;j++){
			if(board[i][j]=='e') cout<<' ';
			else cout<<board[i][j];
			if(j<2) cout<<lP;
			else cout<<boardGrid[i]<< endl;
			}
		//cout<<endl;
		if(i<2) cout<<" "<<f<<t<<f<<t<<f<<"\t\t"<<f<<t<<f<<t<<f<<endl;
	}
}

//Function: checkWin()
//Usage:void checkWin()
//Description:checks to see if game has ended 
//If a given player has one, returns player character
//If game is tied returns '1'
//If game is still in play returns '0'; 
char TTBoard::checkWin(){
	char colls= checkColl();
	if(colls!='0') return colls;//checks columns for end state 
	char rows= checkRow();
	if(rows!='0') return rows;// checks rows for end state
	char dx= checkDs();
	if(dx!='0') return dx;//checks diagonals for end state
	if(full()) return '1';//detects tie 
	return '0';//game not over 
}


//checks collums for winner
char TTBoard::checkColl(){
	char firstC=' ';
	int nMatched;
	for(int i=0;i<nCol;i++){
		int nMatched=0;
		firstC =board[0][i];
		for(int j=1;j<nCol;j++){
			char currC= board[j][i];
			if (board[j][i]==firstC&&board[j][i]!='e') nMatched++;
		}
		if(nMatched>=2) return board[0][i];
		firstC=' ';
	}
	return '0'; 
}
	
//checks rows for winner
char TTBoard::checkRow(){
	char firstC=' ';
	int nMatched;
	for(int i=0;i<nCol;i++){
		int nMatched=0;
		firstC =board[i][0];//
		for(int j=1;j<nCol;j++){
			char currC= board[i][j];//
			if (board[i][j]==firstC&&board[i][j]!='e') nMatched++;//
		}
		if(nMatched>=2) return board[i][0];
		firstC=' ';
	}
	return '0'; 

}

//checks diagonals for winner 
char TTBoard::checkDs(){
	if((board[0][0]==board[1][1])&&(board[1][1]==board[2][2])&&board[0][0]!='e') return board[0][0];
	if((board[0][2]==board[1][1])&&(board[1][1]==board[2][0])&&board[0][2]!='e') return board[0][2];
	return '0';

}

//checks if board has not moves left, used to decided tie 
//itertates over all board cells, returns false if any are empty 
bool TTBoard::full(){
	for(int i=0;i<nCol;i++){
		for(int j=0;j<nCol;j++){
			if(board[i][j]=='e') return false;
		}
	}
	return true;
}