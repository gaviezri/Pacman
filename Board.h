#pragma once

#include <conio.h> 
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>    
#include <queue>    
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

using std::vector;



class Board
{
	vector<vector<string>> Org_maps;       // We creat 2 identical maps; one to keep for new game beginnings (each time we switch map we update the play map)
	vector<string> Play_map;			  // and one to play and change in real time.
	vector<string>  screen_files;        //  stores all pathes to maps.
	Pacman pac;	

	vector<Ghost> ghosts;
	Fruit fruit;
	Point legend;

	int map_num = 0;
	bool legend_flag = false;
	short rows = 0;
	short breadcrumbs = 0;

private:
	//-------------------------pacman movement-----------------------------------
	bool findBorder_Top(const unsigned short& col, unsigned short& line);
	void changeFood2Path(Point pos) { Play_map[pos.getY()][pos.getX()] = ' '; }
	static bool isBlank(char a) { return a == ' ' || a == '%' || a == '.'; }
	bool isTopBorder(const unsigned& X, const unsigned& Y);

	//------------------------ghosts movement------------------------------------
	void premoveDatacollection(char& next_cont, char* cont_around, bool* path_around, NPC& G, Direction& opposite_dic, vector<Direction>& options);
	void nextContAndOppDic(Direction dic, Direction& op_dic, char& next_cont, char* cont_around);
	void AnalyzeAround(NPC g, char* conts, bool* paths);
	void NoviceMovement(const vector<Direction>&,const Direction&, const char&, bool, NPC& G);
	void BestMovement(const vector<Direction>& options, const bool& colored, Ghost& G, const Direction& opposite_dic,const char& next_cont);
	int BestMovement_Util(Point dest, Point cur);
	vector<vector<bool>> createTrackingMap();
	//-----------------------------ctor-----------------------------------------

	void create_PlayMap_from_Org(int y);
	void insert_legend();
	void insert_legend_row(int y, int x);

public:
	Board();

	//---------------------map--------------------------------------

	void loadNew_map();
	vector<string>& getPlay_map() { return Play_map; }
	const Point& getlegend() const { return legend; }
	const bool getLegend_flag() const { return legend_flag; }
	const int getMapNum() { return map_num; }
	const vector<string>& getScreen_files() { return screen_files; }
	void setMap_num(int x) { map_num = x; }
	bool out_of_line(const Point& pos, const Direction& dic);
	bool isOnBorder(Point pos);

	//----------------------utilities---------------------------------------------

	void resetCharacters() { pac.resetMe(); fruit.setPos(pac.getPos()); for (auto& g : ghosts) g.resetMe(); }
	short getCrumbs() { return breadcrumbs; }
	char nextCellCont(Point pos, Direction dic);      // returns map content in a given postion.
	bool Collision();
	void printMap(bool colored);
	static bool isBlank(char a) { return a == ' ' || a == '%' || a == '.'; }
	bool isOnBorder(Point pos);
	bool isTopBorder(const unsigned& X, const unsigned& Y);
	bool isInBorder(Point pos);
	//-------------------pacman---------------------------
	Pacman& get_pac() { return pac; }
	void movePac(Direction dic, bool colored, short& score);
	bool portals(Direction dic, Point& pos);
	
	//----------------------ghosts----------------------

	vector<Ghost>& get_ghosts_vec() { return ghosts; }
	Ghost& get_ghost(int i) { return ghosts[i]; } // needs to be changed in Game.cpp and therefor not const.
	void moveGhost(bool colored,int);
	const vector<Ghost>& Ghosts() { return ghosts; }
	void NPCmoveGenerator(bool colored,int);
};