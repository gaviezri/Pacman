#pragma once
#include "Cell.h"
const short ROWS = 20;
const short COLS = 20;

class Board
{
	Cell cells[ROWS][COLS];	// the cell of the board
	bool field[ROWS][COLS]; // 0 == path/food , 1 == wall


};

