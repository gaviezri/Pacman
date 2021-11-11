#pragma once
#include "Ghost.h"
#include "Pacman.h"



class Game
{
	bool colored;
	char choice=0;
	bool win=false;
	bool pause = false;
	short score=0;
	Board br;
	Pacman pac;
	Ghost g1 = Ghost(Point(11, 7), LEFT);
	Ghost g2 = Ghost(Point(14, 7), RIGHT);
public:
	void printScore(bool colored) { gotoxy(2, 14); cout.flush(); cout << (colored == true ? "\033[29m" : "\033[37m") << "SCORE: " << score; }
	void Loser();
	void Winner();
	static void pauseGAME();
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
};

