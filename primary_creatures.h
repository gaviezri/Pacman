#pragma once
#include "Point.h"

class primary_creatures
{
protected:
	char avatar;
	Point pos;
	Point def_pos;

public:
	//-------------movements of creatures-------------
	const Point& getPos() { return pos; }
	void setPos(const Point& p) { pos = p; }
	void setX(unsigned int x) { pos.setX(x); }
	void setY(unsigned int y) { pos.setY(y); }
	void resetMe() { pos = def_pos; }
	void printMe() {
		gotoxy(pos.getX(), pos.getY());
		cout << avatar;
	}
	char getAvatar() { return avatar; }
	void clearMe(char cont)
	{
		gotoxy(pos.getX(), pos.getY()); // putting cursor on character's place and run it over with the cell content
		cout << (cont == (int)Content::PATH ? " " : "."); // checks cells content and print it.
	}
	void clearMe()
	{
		gotoxy(pos.getX(), pos.getY());
		cout <<" "; 
	}

};

