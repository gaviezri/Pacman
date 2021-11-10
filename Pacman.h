#pragma once
#include "Point.h"// might raise error --- probably will need to be removed elsewhere
#include "Ghost.h"


class Pacman
{
	const char avatar = 'C';
	Point pos;
	short HP = 3;   //pacmans health
	const Point def_pos = Point(13, 9);  // for printing
	bool inPortal=false;

public:
	bool isPortaling() { return inPortal; }
	void Portaling(bool mode) { inPortal = mode; }
	Pacman() { pos = def_pos; };
	void resetMe() { pos = def_pos; inPortal = false; HP = 3; }
	short getHP(){return HP;}
	void HitByGhost(){--HP;}
	Point getPos() { return(pos); }
	void printMe(bool colored) { cout << (colored == true ? "\033[33m" : "\033[37m") << avatar; }
	void updateMove(Direction dic, bool colored);
	bool Collision(Ghost ghost1, Ghost ghost2);// is pacman and ghost on same cell

};

