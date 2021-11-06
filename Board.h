#pragma once
#include "Cell.h"
#include <conio.h>

const short ROWS = 13;
const short COLS = 26;


class Board
{
	Cell cells[ROWS][COLS];	// the cell of the board
 	short int breadcrumbs = 10;//count breadcrumbs!
	
public:
	Board();
	void printBoard();
	cellcontent NextCellCont(Direction dic, const unsigned short* _pos);
	/*void EatCrumbs(const unsigned short* _pos) //breadcrumbs method
	{
		if (cells[_pos[0]][_pos[1]]);
	}
	*/
	//void updateCell(unsigned short x, unsigned short y, cellcontent cont);
};

inline bool isSecretdoor(int i, int j)//secret passage check by coord
{
	return (i == 7 && (j == 0 || j == 25));
}




inline bool IsOnBorder(int i, int j) { return (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1); }
