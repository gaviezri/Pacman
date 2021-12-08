#pragma once
#include <conio.h> 
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include "Pacman.h"
#include "Ghost.h"

using std::vector;



class Board
{
	vector<vector<string>> Org_maps;       // We creat 2 identical maps; one to keep for new game beginnings (each time we switch map we update the play map)
	vector<string> Play_map;			  // and one to play and change in real time.
	Pacman pac;						  
	vector<Ghost> ghosts;
	Point legend;
	bool legend_flag = false;
	short rows;
	short breadcrumbs = 0;

private:
	bool findBorder_Top(const unsigned short& col, unsigned short& line);
	void create_map_from_file(int map_num);
	void changeFood2Path(Point pos) { Play_map[pos.getY()][pos.getX()] = ' '; }
	void AnalyzeAround(Ghost g, char* conts, bool* paths);



public:
	Board();
	void scanMap(ifstream myFile, string tmp_line, vector<string>& cur_map);
	void loadNew_map(int map_num);

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

	void resetCharacters() { pac.resetMe(); for (auto g : ghosts) g.resetMe(); }
};