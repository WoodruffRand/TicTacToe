///////////////////////////////////////
//Name		:		Randall Woodruff
//Class		:		CSC 122
//Date		:		10/2/13
//File		:		CellProbability.cpp
//Description: This is a class that used to assess the properties of a given move on the game board
//This class is intended to be used within a recursive search tree as a passed parameter as the game is 
//played forward from each spot on the board.  
// 
// CellProbability class encapsulates all data gathered during  search process in order to enable comparisons
// of board moves 

#include "CellProbability.h"

//Function: CellProbability(void)
//Usage: TTBoard CellProbability=CellProbability(void);
//Description: constructor for cell probability, initializes all instance variables 
CellProbability::CellProbability(void)
{
	wins=0;
	losses=0;
	ties=0;
	roundDepth=0;
	lossDepth=-1;//initialized to -1 to indicate if loss not encountered 
	winDepth=-1;//initialized to -1 to indicate if win not encountered 
	forcedLoss=false;
}



	/*setters*/
int CellProbability::addWin(){
	return ++wins;
}
int CellProbability::addLoss(){
	return ++losses;
}
int CellProbability::addTie(){
	return ++ties;
}
	


void CellProbability::addDepth(){
	roundDepth++;
}

void CellProbability::removeDepth(){
	roundDepth--;
}
	
void CellProbability::setWinDepth(){
	if(winDepth==-1||winDepth>roundDepth){
		winDepth=roundDepth;
	}
}

void CellProbability::setLossDepth(){
	if(lossDepth==-1||lossDepth>roundDepth){
	lossDepth=roundDepth;
	}
}

void CellProbability::setForcedLoss(){
	forcedLoss=true;
}


	/*getters*/
int CellProbability::getWins(){
	return wins;
}
int CellProbability::getLosses(){
	return losses;
}
int CellProbability::getTies(){
	return ties;
}

int CellProbability::getDepth(){
	return roundDepth; 
}

int CellProbability::getWinDepth(){
	return winDepth;
}

int CellProbability::getLossDepth(){
	return lossDepth;
}

bool CellProbability::deadEnd(){
	return forcedLoss;
}

CellProbability::~CellProbability(void)
{
}
