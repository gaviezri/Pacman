#pragma once
#include "Ghost.h"
#include "Pacman.h"



class Game
{
	bool colored = false;
	char choice;
	bool win;
	bool pause = false;
	short score = 0;
	Board br;
	Pacman pac;
	Ghost g1;
	Ghost g2;
	Game() { Ghost g1(Point(14, 7), LEFT), g2(Point(13, 7), RIGHT); };
public:
	void Loser();
	void Winner();
	void pauseGAME();
	void updateDics(Direction& cur);
	void printMenu();
	void setChoice();
	void printInstructions();
	void play();
	void ResetGame();
	void movement(Direction dic);
	bool Over()//indicator to end game loop
	{
		if (pac.getHP() == 0)
		{
			win = false;
			return true;
		}
		if (score == 136)
		{
			win = true;
			return true;
		}
		else
			return false;
	}
};

