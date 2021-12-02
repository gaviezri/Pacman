#pragma once
#include "Point.h"
#include "Board.h"


class Pacman
{
	Point pos;  
	short HP = 3;   //pacmans health
	Point def_pos;  // for printing	

public:
	void movement(Direction dic, Board& br, short&);
	Pacman(Point p) { pos = def_pos = p; };
	Pacman() {};
	void resetMe() { pos = def_pos; }
	short getHP(){return HP;}
	void printHP(bool s);
	void resetHP() { HP = 3; }
	void HitByGhost() { --HP; gotoxy(2 * pos.coord[0], pos.coord[1]); cout << " ";  pos = def_pos; }
	void updateMove(Direction dic, bool colored);
	Point getPos() { return pos; }
};


