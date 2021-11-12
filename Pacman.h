#pragma once
#include "Point.h"
#include "Board.h"


class Pacman
{
	const char avatar = 'C';
	Point pos;  
	short HP = 3;   //pacmans health
	const Point def_pos = Point(13, 9);  // for printing
	bool inPortal=false;
	

public:
	void movement(Direction dic, Board& br, short&);
	bool isPortaling() { return inPortal; }
	void Portaling(bool mode) { inPortal = mode; }
	Pacman() { pos = def_pos; };
	void resetMe() { pos = def_pos; inPortal = false; }
	short getHP(){return HP;}
	void printHP(bool s);
	void resetHP() { HP = 3; }
	void HitByGhost() { --HP; gotoxy(2 * pos.coord[0], pos.coord[1]); cout << " ";  pos = def_pos; }
	const unsigned short * getPos() { return pos.getCoord(); }
	void printMe(bool colored) { cout << (colored == true ? "\033[33m" : "\033[37m") << avatar; }
	void updateMove(Direction dic, bool colored);
};

