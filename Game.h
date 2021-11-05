#pragma once
#include "Board.h"
#include "Character.h"



class Game
{
	short int choice;

public:
	void printMenu();
	void setChoice();
	void printInstructions();
	void play();
	Direction charToDic(char ch);
};

