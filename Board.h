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
private:
	bool findBorder_Top(const unsigned short& col, unsigned short& line);
	void create_map_from_file();
	void changeFood2Path(Point pos) { Play_map[pos.getY()][pos.getX()] = ' '; }
	void AnalyzeAround(Ghost g, char* conts, bool* paths);



public:
	Board();
	
	vector<string>& getPlay_map() { return Play_map; }
	const Point& getlegend() const { return legend; }
	bool getLegend_flag() const { return legend_flag; }
	Pacman& Pac() { return pac; }
	void movePac(Direction dic, bool colored, short& score);
	short getCrumbs() { return breadcrumbs; }
	char nextCellCont(Point pos, Direction dic);      // returns map-cell contant in a given postion.
	void nextContAndOppDic(Direction dic, Direction& op_dic, char& next_cont, char* cont_around);

	const vector<Ghost>& Ghosts() { return ghosts; }
	Ghost& Ghosts(int i) { return ghosts[i]; } // needs to be changed in Game.cpp and therefor not const.
	void moveGhost(bool colored);

	static bool isBlank(char a) { return a == ' ' || a == '%' || a == '.'; }
	bool isBlankOnBorder(Point pos);
	bool isOnBorder(Point pos);
	bool isTopBorder(const unsigned& X, const unsigned& Y);


	bool portals(Direction dic, Point& pos);

	bool Collision();
	void printMap(bool colored);

	void resetMap();
	void resetCharacters() { pac.resetMe(); for (auto g : ghosts) g.resetMe(); }
};