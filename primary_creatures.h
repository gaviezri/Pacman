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
	void clearMe(bool colored,char cont)
	{
		gotoxy(pos.getX(), pos.getY()); // putting cursor on character's place and run it over with the cell content
		if (colored)
			setTextColor(Color::BLUE);
		cout << (cont == (int)Content::PATH ? " " : "."); // checks cells content and print it.
	}
	void clearMe()
	{
		gotoxy(pos.getX(), pos.getY());
		cout <<" "; 
	}
};

