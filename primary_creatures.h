#pragma once
#include "Point.h"

class primary_creatures
{
protected:
	char avatar;
	Point pos;
	Point def_pos;

public:
	void resetMe() { pos = def_pos; }
	void PrintMe(bool colored) { gotoxy(pos.getX(), pos.getY()); cout << (colored ? "\033[33m" : "\033[37m") << avatar; }

};

