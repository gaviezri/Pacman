#pragma once

#include "GhostBehaviour.h"
#include "Board.h"

class Ghost {
	char avatar = '?';
	Point cur_pos;
	Point def_pos;
	
public:
	const unsigned short* getPos() { return cur_pos.getCoord(); }
	//moving func
	void PrintME() { cout << avatar; }
	Ghost(Point _pos) { cur_pos = def_pos = _pos; } 
	void Movement();
	void Reset();
};