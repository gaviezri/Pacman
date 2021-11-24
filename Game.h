#pragma once
#include "Ghost.h"
#include "Pacman.h"



class Game
{
	bool colored;
	char choice=0;
	bool win=false;
	short score=0;
	bool pause;
	Board br;
	Pacman pac;
	Ghost g1 = Ghost(Point(11, 7), LEFT);
	Ghost g2 = Ghost(Point(14, 7), RIGHT);
public:
	void setDif();
	void NewRound();
	void printScore(); 
	void Loser();
	void Winner();
	void pauseGAME();
	void updateDics(Direction& cur);
	void printMenu();
	void setChoice();
	void printInstructions();
	void play();
	void ResetGame();
	bool Collision();
	bool Over()//indicator to end game loop
	{
		if (pac.getHP() == 0)
		{
			win = false;
			return true;
		}
		if (score == 139)
		{
			win = true;
			return true;
		}
		else
			return false;
	}
	void Engine();
};

