///////////////////////////////////////
//Name		:		Randall Woodruff
//Class		:		CSC 122
//Date		:		10/2/13
//File		:		TickTackToe.cpp
//Description: 
//Goal: implement a tick tac toe program with options for 2 human players 
//or player and computer opponent 
//AI will be bassed on a depth first recursive search tree that explores game space looking for in order
//1.  Immediate player wins
//2.  Forced losses in future turns by player
//3.  Total branch win loss tie ratios 
//Improvements to search tree should include peak function to improve "intelligence" 
//with which simulated computer and player moves are made
// Cell probability class used to study characteristics of a given branch and encapsulate branch data
// Board Class simplifies IO needs of main program and provides safety checks including 
//1. out of range board indexes 
//2. Attempting to set invalid player indicators on board
//Board Class Also includes methods to facilitate recursive searches including
//1. Weather a cell has been used 
//2. If game has concluded and if so what is the result



#include <iostream>
#include <sstream>
#include "TTBoard.h"
#include "CellProbability.h"

using namespace std;
/*constants */

const char STLC= 218;
const char STRC= 191;
const char SBLC= 192;
const char SBRC= 217;

const char TLC= 201;
const char TRC= 187;
const char BLC= 200;
const char BRC= 188;

const char DL= 205;
const char L= 196;
const char DRL= 186;
const char RL= 179;
/*Functional Protypes*/
void printWelcome();
void printInsturctions();
void playerTurn(TTBoard &board,char xORo);
void computerTurn(TTBoard &board,char xORo);
bool gameEnd(TTBoard &board);
void mainMenu();
void twoPlayer();
void playComputer();
void calcCProb(int cell,TTBoard &board,CellProbability &prob);
void simCompTurn(int cell,TTBoard &board,CellProbability &prob);
bool simPlayerTurn(int cell,TTBoard &board,CellProbability &prob);
bool tempPBetter(CellProbability old,CellProbability temp);


int getInt(std::string prompt);

/*Main*/
int main(){
	printWelcome();
	mainMenu();
	return 0;
}



void printWelcome(){
	cout<<TLC;
	for(int i=0;i<78;i++) cout<<DL;
	cout<<TRC;

	cout<<DRL<<"________________________!!!WELCOME TO TICK TACK TOE!!!________________________"<<DRL;
	cout<<DRL<<"                      +Publish and coded by Woodruff Coding+                  "<<DRL;
	cout<<DRL<<" Bringing the power of Text-Based Gamming to Quad Core Processors Since 2013  "<<DRL;
	cout<<DRL<<"                                                                              "<<DRL;
	cout<<DRL<<"Version 0.0001                                                                "<<DRL;
	
	cout<<BLC;
	for(int i=0;i<78;i++) cout<<DL;
	cout<<BRC;

	
	cout<<"\n\n";
}


void printInsturctions(){
	cout<< "This is a simple implementation of the pen and paper game tick tac toe"<<endl;
	cout<< "for an emulated dos prompt."<<endl;
	cout<<"How to play: The player who succeeds in completing an horizontal, vertical, or"<<endl;
	cout<<"diagonal row wins the game."<<endl;

	cout<<"When playing the computer the player will always be 'x', and the computer, 'o'."<<endl;
}


//Function mainMenu()
//Usage: mainMenu():
//-------------------
//loop structure containing main program options
//options are 1. Two Player game, 2. Play against computer, 3. Insructions, 4. Quit.
//user choices are decided through simple switch statement.  
//with exception of quit, option choices will be executed and eventualy return to main
void mainMenu(){
	bool cont = true;
	while(cont){
		//print menu options 
		
		 
		
		 
		 
		
		cout<<STLC;
		for(int i=0; i<20;i++)cout<<L;
		cout<<STRC<<endl;
		
		cout<<RL<<"     Main Menu      "<<RL<<endl;
		
		cout<<SBLC;
		for(int i=0; i<20;i++)cout<<L;
		cout<<SBRC<<endl;

		cout<<"\t(1). Two Player Game."<<endl;
		cout<<"\t(2). Play against computer."<<endl;
		cout<<"\t(3). Instructions."<<endl;
		cout<<"\t(4). Quit."<<endl;
		cout<<"\t";
		for(int i=0; i<20;i++)cout<<L;
		cout<<endl;
		//reads in user choice 
		int uChoice=getInt("Enter choice: ");
		
		//executes user choice
		switch(uChoice){

			case 1:	twoPlayer(); break;
			case 2:	playComputer();	break;
			case 3: printInsturctions();break;
			case 4:cont= false; break;
			default:system("cls");cout<<uChoice<<" is not a valid choice.  Please try again."<<endl;
		}//end of switch
	}
}

void twoPlayer(){
	TTBoard gameBoard= TTBoard();
	system("cls");
	while(true){//system clear disabled for sample output 
		gameBoard.print();//replaced by overloaded cout function 
		
		playerTurn(gameBoard,'x');
		system("cls");
		gameBoard.print();//replaced by overloaded cout function 
		if(gameEnd(gameBoard)) break;
		playerTurn(gameBoard,'o');
		system("cls");
		gameBoard.print();//replaced by overloaded cout function 
		if(gameEnd(gameBoard)) break;
		system("cls");
	}
}


void playComputer(){
	TTBoard gameBoard= TTBoard();
	system("cls");
	while(true){
		gameBoard.print();
		if(gameEnd(gameBoard)) break;
		playerTurn(gameBoard,'x');
		system("cls");
		gameBoard.print();
		if(gameEnd(gameBoard)) break;
		computerTurn(gameBoard,'o');
		system("cls");
		gameBoard.print();
		
		system("cls");
	}

}




void playerTurn(TTBoard &board,char xORo){
	while(true){
		int x;
		cout<<"Player "<<xORo<<" ";
		x= getInt("enter cell number: ");
		if(board.setSquare(x-1,xORo)) break;
		else cout<<"invalid move, please retry"<<endl;
	}

	return;
}


void computerTurn(TTBoard &board,char xORo){
	CellProbability bestProb;
	int bestIndex;
	for (int i=0;i<9;i++){
		if(board.cellEmpty(i)){
			CellProbability tProb;
			calcCProb(i,board, tProb);
			
			string forced;
			if(tProb.deadEnd()==true) forced="true";
			else forced="false";
			//cout<<"Index: "<<i+1<<" %wins: "<<tProb.getWins() <<" %Losses: "<< tProb.getLosses()<<"% ties: "<<
			//	tProb.getTies()<<"Lose in" <<tProb.getLossDepth()<<" Forced loss:"<<forced<<endl;
 			if(tempPBetter(bestProb,tProb)) {
				bestProb=tProb;
				bestIndex=i;
			}
			board.unsetSquare(i);
		}
	}
	board.setSquare(bestIndex,'o');
}

 void calcCProb(int cell,TTBoard &board,CellProbability &prob){
	simCompTurn(cell,board, prob);
}


void simCompTurn(int cell,TTBoard &board,CellProbability &prob){
	board.setSquare(cell,'o');
	prob.addDepth();
	char boardState= board.checkWin();
	switch(boardState){
		case 'x':prob.addLoss(); prob.setLossDepth(); return;//x wins
		case 'o':prob.addWin(); prob.setWinDepth();return;// o wins
		case '1':prob.addTie(); return;// tie 
		case '0': break;//game not over, continue to evalauate
		default:cout<<"error evaluating probablity at tree terminious"<<endl;
	}
	int coutLosses=0;
	int playableSquares=0;
	for (int i=0;i<9;i++){
		if(board.cellEmpty(i)){
			playableSquares++;
			if(simPlayerTurn(i,board, prob)) coutLosses++;//if player move wins next round incremnet losses 
			board.unsetSquare(i);//unset move
			prob.removeDepth();
		}
	}
	if(coutLosses>1&&prob.getDepth()==3) prob.setForcedLoss();
}


bool simPlayerTurn(int cell,TTBoard &board,CellProbability &prob){
	board.setSquare(cell,'x');//x is player char 
	prob.addDepth();
	char boardState= board.checkWin();
	switch(boardState){
		case 'x':prob.addLoss(); prob.setLossDepth(); return true;//x(player) wins
		case 'o':prob.addWin(); prob.setWinDepth();return false;// o wins
		case '1':prob.addTie(); return false;// tie 
		case '0': break;//game not over, continue to evalauate
		default:cout<<"error evaluating probablity at tree terminious"<<endl;
	}
	
	for (int i=0;i<9;i++){
		if(board.cellEmpty(i)){
			simCompTurn(i,board, prob);
			board.unsetSquare(i);
			prob.removeDepth();
		}
	}
	return false;

}


bool tempPBetter(CellProbability old,CellProbability temp){
	if(old.getWins()==0 && old.getLosses()==0 &&old.getTies()==0) return true;
	if(old.getLossDepth()==2&&temp.getLossDepth()!=2) return true;
	//if(old.getWinDepth()>2&&temp.getWinDepth()<2) return true;
	double pLOld = old.getLosses()*1.0/(old.getLosses()+old.getWins()+old.getTies());
	double pLTemp = temp.getLosses()*1.0/(temp.getLosses()+temp.getWins()+temp.getTies());


	if(pLOld>pLTemp) return true;
	return false;

}

bool gameEnd(TTBoard &board){
	char result=board.checkWin();
	if(result!='0'&&result!='1') {
			cout<<"The winner is " <<result<<"."<<endl;
			return true;
	} else if(result=='1'){
		cout<<"Its a tie!" <<"."<<endl;
		return true;
	} else 	return false;

	cout<<"error in evaluting win, result symbol " <<result<<"generated"<<endl;
	return false;
}

int getInt(std::string prompt){
	std::string input;
	int rVal;
	while(true){	
		std::cout<<prompt;
		std::cin>>input;
		std::stringstream sstream(input);
		sstream>>rVal;
		if(!sstream.fail()&&sstream.eof()) return rVal;
		else std::cout<<"Invalid intger syntax."<<std::endl;
	}
	std::cin.clear();
}



