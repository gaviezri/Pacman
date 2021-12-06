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
	void printMe(bool colored) {
		gotoxy(pos.getX(), pos.getY()); if (colored) { if (avatar == 'C')setTextColor(Color::BROWN); else if (avatar == 'G')setTextColor(Color::RED); else setTextColor(Color::WHITE); cout << avatar; }
	}

};

