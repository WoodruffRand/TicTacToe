///////////////////////////////////////
//Name		:		Randall Woodruff
//Class		:		CSC 122
//Date		:		10/2/13
//File		:		TTBoard.h
//Description: This is a class that defines the tick tac toe board.  
// Board Class simplifies IO needs of main program and provides safety checks including 
//1. Checking and preventing out of range board indexes 
//2. Blocks Attempts to set invalid player indicators on board
//3. Check if game has resulted in win loss or tie
//Board Class Also includes methods to facilitate recursive searches including
//1. Weather a cell has been used 
//2. If game has concluded and if so what is the result
//3. Unset cell function 


#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class TTBoard
{
public:
	
	//Function: TTBoard(void)
	//Usage: TTBoard board=TTBoard(void);
	//Description: sets up empty tick tack toe board
	TTBoard(void);
	~TTBoard(void);

	//Function: setSquare
	//Usage: bool flag=setSquare(int x, int y, char move)
	//x: board index (0-8)
	//move: your x or 0
	//Description: function to store new moves into board
	//contains bounds checking to make sure move is inside board
	//as well as checks to see if cell is already taken and 
	//checks to make sure that char is either x or o
	//if board is unable to accept move, returns false, if move set, returns true 
	bool setSquare(int x, char move);
	
	
	//Function: unsetSquare
	//Usage: void unsetSquare(int x)
	//x: board index (0-8)
	//Description: Removes any moves from given index.
	//Designed primarily when building recursive search trees 
	void unsetSquare(int x);
	
	
	//Function: print
	//Usage: void print()
	//Description: prints current board state to screen along with index map for player to use 
	void print();

	//Function: checkWin()
	//Usage:void checkWin()
	//Description:checks to see if game has ended 
	//If a given player has one, returns player character
	//If game is tied returns '1'
	//If game is still in play returns '0'; 
	char checkWin();


	//Function: cellEmpty()
	//Usage:bool flag= cellEmpty(int x);
	//Description: checks given board index(0-8) if cell is takes 
	bool cellEmpty(int x);

	

	//function: cout<<TTBoard
	//Usage: cout<<TTBoard;
	//Description: Overloaded operator to be able to 
	//Directly  input TTBoard object to cout stream 
	friend ostream& operator<<(ostream& os,const TTBoard& temp);

private:
	/*privat Ivars*/
	char board[3][3];//used to store board state, store char from moves 
	string boardGrid[3];//used in printing player board map
	const static int nRow= 3;//used to parameterize number of rows in board
	const static int nCol=3;//used to parameterize number of collums in board
	char lP;
	char f;
	char t;
	/*pirvate functions*/
	//checks collums for winner
	char checkColl();
	
	//checks rows for winner
	char checkRow();

	//checks diagonals for winners 
	char checkDs();

	//checks if board has not moves left, used to decided tie 
	bool full();
};

