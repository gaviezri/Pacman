#pragma once
#include "GhostBehaviour.h"
#include "Board.h"

class Ghost {
	const char avatar = 'G';
	Point cur_pos;
	const Point def_pos;
	const Direction first_move;
	static short def_moves_count;

public:
	const unsigned short* getPos() { return cur_pos.getCoord(); }
	//moving func
	void PrintME() { cout << avatar; }
	Ghost();
	Ghost(Point _pos, Direction first): cur_pos(_pos), def_pos(_pos), first_move(first) {} // (13,7) (14,7) 
	void Movement(Direction dic ,const Board& br);
	void updateMove(Direction dic, bool colored, short cont);
	void printMe(bool colored) { cout << (colored == true ? "\033[33m" : "\033[37m") << avatar; }
	void resetMe() { cur_pos = def_pos; }
};