#pragma once
#include "Cell.h"
#include <conio.h>

const short ROWS = 11;
const short COLS = 42;


class Board
{
	Cell cells[ROWS][COLS];	// the cell of the board
	bool field[ROWS][COLS]; // 0 == path/food , 1 == wall
	
public:
	Board();
	void initCells();
	void printBoard();
	bool isWall(Direction dic, const unsigned short* _pos);

	//void updateCell(unsigned short x, unsigned short y, cellcontent cont);
};

inline bool isSecretdoor(int i, int j)//secret passage check by coord
{
	return (i == 5 && (j == 0 || j == 40));
}




inline bool IsOnBorder(int i, int j) { return (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1); }
