#pragma once
#include "Board.h"



class Game
{
	bool colored;
	char choice=0;
	bool win=false;
	short score=0;
	bool pause;
	Board br;
	bool everyothermove = true;

public:
	void ghosts_movemaker();
	void setDif();
	void Color(){
		short cho;
		cout << "for color mode enter 1, for B&W enter anything else : ";
		cin >> cho;
		cho == 1 ? colored = true : colored = false;
	}
	void NewRound();
	void printScore(Point); 
	void Loser();
	void Winner();
	void pauseGAME();
	void updateDics(Direction& cur);
	void printMenu();
	void setChoice();
	void printInstructions();
	void play();
	void ResetGame();
	void printlegend(Point pt, short hp);
	bool Over()//indicator to end game loop
	{
		if (br.Pac().getHP() == 0)
		{
			win = false;
			return true;
		}
		if (score == br.getCrumbs())
		{
			win = true;
			return true;
		}
		else
			return false;
	}
	void Engine();
};

