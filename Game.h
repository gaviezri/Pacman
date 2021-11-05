#pragma once

#include <iostream>
#include <conio.h>

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT, PAUSE, ESC };


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

