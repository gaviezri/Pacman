#pragma once
#include <conio.h> 
#include <vector>
#include <fstream>
#include <sstream>
#include "Pacman.h"
#include "Ghost.h"
using std::vector;



class Board
{
	vector<string> Org_map, Play_map;    // We creat 2 identical maps; one to keep for new game beginnings 
	Pacman pac;						   // and one to play and change in real time.
	vector<Ghost> ghosts;
	Point legend;
	bool legend_flag = false;
	short rows = 0, cols = 0;
	short breadcrumbs = 0;
	

public:
	Board();
	void create_map_from_file();
	
	vector<string>& getPlay_map() { return Play_map; }
	const Point& getlegend() const { return legend; }
	bool getLegend_flag() const { return legend_flag; }
	Pacman& Pac() { return pac; }
	void movePac(Direction dic, bool colored, short& score);

	const vector<Ghost>& Ghosts() { return ghosts; }
	Ghost& Ghosts(int i) { return ghosts[i]; } // needs to be changed in Game.cpp and therefor not const.
	void moveGhost(bool colored);

	short getCrumbs() { return breadcrumbs; }
	char nextCellCont(Point pos, Direction dic);      // returns map-cell contant in a given postion.
	void changeFood2Path(Point pos) { Play_map[pos.getY()][pos.getX()] = ' '; }
	bool isBlankOnBorder(Point pos);
	bool isOnBorder(Point pos);

	void AnalyzeAround(Ghost g, char* conts, bool* paths);

	bool Collision();
	void printMap(bool colored);

	void resetMap();
	void resetCharacters() { pac.resetMe(); for (auto g : ghosts) g.resetMe(); }
	void nextContAndOppDic(Direction dic, Direction& op_dic, char& next_cont, char* cont_around);
};