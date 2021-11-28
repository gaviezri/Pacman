#pragma once
#include "Cell.h"
#include <conio.h> 
#include <vector>
#include <fstream>
#include <sstream>
#include "Pacman.h"
#include "Ghost.h"

class _Board
{
	vector<string> Org_map, Play_map;    // We creat 2 identical maps; one to keep for new game beginnings 
	Pacman pac;						   // and one to play and change in real time.
	vector<Ghost> ghosts;
	Point legend;
	short rows = 0, cols = 0;

public:
	_Board();
	void changeVisualCells();
	void printMap(bool colored);
	char nextCellCont(Point pos, Direction dic);      // returns map-cell contant in a given postion.
	void changeFood2Path(Point pos) { Play_map[pos.getY()][pos.getX()] = ' '; }
	void resetMap();
	void printMe(Ghost g, bool colored) { gotoxy(g.getPos().getX(), g.getPos().getY()); cout << (colored ? "\033[31m" : "\033[37m") << 'G';}
	void printMe(Pacman pac, bool colored) { gotoxy(pac.getPos().getX(), pac.getPos().getY()); cout << (colored ? "\033[33m" : "\033[37m") << 'C'; }
};