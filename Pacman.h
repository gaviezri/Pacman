#pragma once
#include "primary_creatures.h"



class Pacman:public primary_creatures
{
	short HP = 3;   //pacmans health
	
public:
	Pacman(Point p) { pos = def_pos = p, avatar = 'C'; };
	Pacman() {};
	short getHP() { return HP; }
	void resetHP() { HP = 3; }
	void HitByGhost() { --HP; gotoxy(2 * pos.getX(), pos.getY()); cout << " ";  pos = def_pos; }
	void updateMove(Direction dic, bool colored,vector<string>);
	Point& getPos() { return pos; }
	void PrintMe(bool colored) { gotoxy(pos.getX(), pos.getY()); cout << (colored ? "\033[33m" : "\033[37m") << 'C'; }

};


