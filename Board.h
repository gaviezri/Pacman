#pragma once
#include "Cell.h"
#include <iostream>
const short ROWS = 20;
const short COLS = 20;

class Board
{
	Cell cells[ROWS][COLS];	// the cell of the board
	bool field[ROWS][COLS]; // 0 == path/food , 1 == wall
	
public:
	void setField();
	void initBoard();
	void printBoard();
	void updateCell(unsigned short x, unsigned short y, cellcontent cont);
};

