#pragma once
#include "Board.h"
#include "Pacman.h"



class Game
{
	short int choice;
	bool win;
	short score = 0;
	Board br;
	Pacman pac;

public://score funcs!
	void updateDics(Direction& cur, Direction& nxt);
	void printMenu();
	void setChoice();
	void printInstructions();
	void play();
	Direction charToDic(char ch);
	void movement(Direction dic);
	bool Over(short int bc)//indicator to end game loop
	{
		if (pac.getHP() == 0)
		{
			win = false;
			return true;
		}
		else if (bc == 0)
		{
			win = true;
			return true;
		}
		else
			return false;
	}
};

