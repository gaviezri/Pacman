#pragma once
#include "Cell.h"
#include <conio.h>  // Y tho?

const short ROWS = 13;
const short COLS = 25;
const bool bPATH = false;
const bool bWALL = true;

class Board
{
	Cell cells[ROWS][COLS];	// the cell of the board
	bool field[ROWS][COLS]; // 0 == path/food , 1 == wall
	short int breadcrumbs = 10;//count breadcrumbs!
	
public:
	Board();
	void printBoard();
	cellcontent nextCellCont(Direction dic, const unsigned short* _pos);

	void changeFood2Path(Cell cur)
	{
		cur.setMyContent(PATH);
	}

	Cell getCell(short _x, short _y)
	{
		return cells[_x][_y];
	}

};

inline bool isSecretdoor(int i, int j)//secret passage check by coord
{
	return (i == 5 && (j == 0 || j == 40));
}


inline bool IsOnBorder(int i, int j) { return (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1); }
