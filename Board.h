#pragma once
#include "Cell.h"
#include <iostream>
#include <conio.h>

const short ROWS = 20;
const short COLS = 20;



class Board
{
	Cell cells[ROWS][COLS];	// the cell of the board
	bool field[ROWS][COLS]; // 0 == path/food , 1 == wall
	Board();
	
public:
	
	void initBoard();
	void printBoard();
	void updateCell(unsigned short x, unsigned short y, cellcontent cont);
};

inline bool isSecretdoor(int i, int j)//secret passage check by coord
{
	if (i == 0 && (j == 9 || j == 10)) 
		return true;

	if ((i == 5 || i == 6) && j == 0)
		return true;

	if (i == 19 && (j == 9 || j == 10))
		return true;

	if ((i == 5 || i == 6) && j == 19)
		return true;
}