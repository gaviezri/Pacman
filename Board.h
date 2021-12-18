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
#include <algorithm>

using std::vector;

constexpr unsigned short MAXBOARD_WIDTH = 80;
constexpr unsigned short MAXBOARD_HEIGHT = 25;


class Board
{
	vector<vector<string>> Org_maps;       // We creat 2 identical maps; one to keep for new game beginnings (each time we switch map we update the play map)
	vector<string> Play_map;			  // and one to play and change in real time.
	vector<string>  screen_files;        //  stores all pathes to maps.

	Pacman pac;	
	vector<Ghost> ghosts;
	Fruit fruit;
	Point legend;

	unsigned short active_map = 0;
	static unsigned short total_maps;

	bool legend_flag = false;
	bool pacman_flag = false;
	bool undefined_characters = false;
	short rows = 25;
	short cur_rows_len = 0;
	short breadcrumbs = 0;

private:
	//-------------------------pacman movement-----------------------------------
	bool findBorder_Top(const unsigned short& col, unsigned short& line);
	void changeFood2Path(Point pos) { Play_map[pos.getY()][pos.getX()] = ' '; }
	//------------------------NPC movement------------------------------------
	void premoveDatacollection(char& next_cont, char* cont_around, bool* path_around, NPC& G, Direction& opposite_dic, vector<Direction>& options);
	void nextContAndOppDic(Direction dic, Direction& op_dic, char& next_cont, char* cont_around);
	void AnalyzeAround(NPC& g, char* conts, bool* paths);
	void NoviceMovement(const vector<Direction>&,const Direction&, const char&, bool, NPC& G);
	void BestMovement(const vector<Direction>& options, const bool& colored, Ghost& G, const Direction& opposite_dic,const char& next_cont);
	int BestMovement_Util(Point dest, Point cur);
	vector<vector<bool>> createTrackingMap();
	//-----------------------------ctor-----------------------------------------
	void create_PlayMap_from_Org(int y,const short&);
	void insert_legend();
	void insert_legend_row(const unsigned& y, const unsigned& x);
	void getScreen_names();
	void CreateOrg_maps();
	void setCur_row_len();
public:
	Board();
	//---------------------map--------------------------------------
	static short getTotal_maps() { return total_maps; }
	void loadNew_map();
	vector<string>& getPlay_map() { return Play_map; }
	//----------------------utilities---------------------------------------------
	const Point& getlegend() const { return legend; }
	const bool& getLegend_flag() const { return legend_flag; }
	const bool& getPacman_flag() const { return pacman_flag; }
	const bool& getundefinedchars_flag() const { return undefined_characters; }
	const int getMapNum() { return active_map; }
	const vector<string>& getScreen_files() { return screen_files; }
	void setActive_map(int x) { active_map = x; }
	bool isOnBorder(Point pos);
	bool isTopBorder(const unsigned& X, const unsigned& Y);
	bool isInBorder(Point pos);
	void resetCharacters()
	{
		if (ghosts.empty()) 
			fruit.setPos(pac.getPos()); 
		else fruit.setPos(ghosts[rand() % ghosts.size()].getPos());
		pac.resetMe();
		for (auto& g : ghosts) g.resetMe();
	}
	short getCrumbs() { return breadcrumbs; }
	char nextCellCont(Point pos, Direction dic);      // returns map content in a given postion.
	bool Collision();
	void printMap(bool colored);
	static bool isBlank(char a) { return a == ' ' || a == '%' || a == '.'; }
	bool isportal(const unsigned short& X, const unsigned short& Y);
	bool in_legend_area(const int& x, const int& y);
	void MapErrors();
	const short getRows() { return rows; }
	//-------------------pacman---------------------------
	Pacman& get_pac() { return pac; }
	void movePac(Direction dic, bool colored,unsigned short& score);
	bool portals( Direction&, Direction&,Point& pos,unsigned short&);
	void pacEatsfruit(unsigned short&, unsigned short&);
	void move_in_border(Direction&, Direction&, Direction&, const bool& colored, unsigned short& score);
	//----------------------ghosts----------------------
	vector<Ghost>& get_ghosts_vec() { return ghosts; }
	Ghost& get_ghost(int i) { return ghosts[i]; } // needs to be changed in Game.cpp and therefor not const.
	void NPCmoveGenerator(bool colored,int,unsigned short&, unsigned short&);
	//-----------------------------fruit---------------------------------------
	Fruit& getFruit() { return fruit; }
	Point getvalidPos(){
		if (ghosts.size()) return ghosts[rand() % ghosts.size()].getPos();
		else return pac.getPos();
	}
};