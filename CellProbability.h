///////////////////////////////////////
//Name		:		Randall Woodruff
//Class		:		CSC 122
//Date		:		10/2/13
//File		:		CellProbability.h
//Description: This is a class that used to assess the properties of a given move on the game board
//This class is intended to be used within a recursive search tree as a passed parameter as the game is 
//played forward from each spot on the board.  
// 
// CellProbability class encapsulates all data gathered during  search process in order to enable comparisons
// of board moves 


//intended use of variables
//1. roundDepth:  Used to track depth in search tree
//2. lossDepth: set to smallest search depth at which computer is found to lose 
//3. winDepth: set to smallest search depth to which computer is found to win 
//4. forcedLoss: boolean flag used to indicate a board move that will lead to a path where computer 
// can be double checked, or forced into a loss 
#pragma once
class CellProbability
{
public:
	//Function: CellProbability(void)
	//Usage: TTBoard CellProbability=CellProbability(void);
	//Description: constructor for cell probability, initializes all instance variables 
	CellProbability(void);
	~CellProbability(void);
	/*setters*/
	
	//Function: addWin();
	//Usage: int nwins =addWin();
	//Description: increments number of wins and returns new value; 
	int addWin();
	
	//Function: addLoss();
	//Usage: int nLosses =addLoss();
	//Description: increments number of Losses and returns new value
	int addLoss();
	
	//Function: addTie();
	//Usage: int nTies =addTie();
	//Description: increments number of ties and returns new value
	int addTie();
	
	//Function: addDepth();
	//Usage: void addDepth(void);
	//Description: increments search depth 
	void addDepth();
	
	//Function: removeDepth();
	//Usage: void removeDepth(void);
	//Description: decrements search depth 
	void removeDepth();
	
	//Function: setWinDepth();
	//Usage: void setWinDepth(void);
	//Description: sets win depth to current search depth 
	void setWinDepth();
	
	//Function: setLossDepth();
	//Usage: void setLossDepth(void);
	//Description: sets loss depth to current search depth 
	void setLossDepth();
	
	//Function: setForcedLoss()
	//Usage: void setForcedLoss(void)
	//Description: sets Foreced loss to true
	void setForcedLoss();
	
	/*getters*/
	
	//Function: getWins();
	//Usage: int nWins =getWins();
	//Description: returns number of wins encountered 
	int getWins();
	
	//Function: getLosses();
	//Usage: int nLosses =getLosses();
	//Description: returns number of wins encountered 
	int getLosses();

	//Function: getTies();
	//Usage: int nTies =getTies();
	//Description: returns number of ties encountered
	int getTies();

	//Function: getDepth();
	//Usage: int currDepth =getDepth();
	//Description: returns current search depth
	int getDepth();
	
	//Function: getWinDepth();
	//Usage: int winDepth =getWinDepth();
	//Description: returns number of depth at which soonest win is encountered
	int getWinDepth();
	
	//Function: getLossDepth();
	//Usage:int nLosses getLosses();
	//Description: returns number of depth at which soonest loss is encountered
	int getLossDepth();
	
	//Function: deadEnd();
	//Usage:bool flag =deadEnd();
	//Description: returns true if move path contains a possible double cross 
	bool deadEnd();
private: 
	int wins;
	int losses;
	int ties;
	int roundDepth;
	int lossDepth;
	int winDepth;
	bool forcedLoss;
};

