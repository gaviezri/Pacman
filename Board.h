#pragma once
#include "Cell.h"
#include <conio.h> 

const short ROWS = 13;
const short COLS = 26;



class Board
{
	Cell cells[ROWS][COLS];
	bool colored;
 		
public:
	Board();
	void printBoard();
	short nextCellCont(Direction dic, const unsigned short* _pos) const;
	void setcolor(bool val) { colored = val; }
	bool getcolor() const { return colored; }
	void changeFood2Path(Cell& cur)	{cur.setMyContent(PATH);}
	
	// Overloading getcell by reference is used to change cell content when needed, const to protect board data & efficency 
	Cell& getCell(const short _x,const short _y) 
	{
		return cells[_y][_x];
	}

	const Cell getCell(const short _x, const short _y) const
	{
		return cells[_y][_x];
	}

};

