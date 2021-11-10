#pragma once
#include "Board.h"
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

