#pragma once
#include "primary_creatures.h"



class Pacman:public primary_creatures
{
	short HP = 3;   //pacmans health
public:
	Pacman() { avatar = 'C'; };
	short getHP() { return HP; }
	void resetHP() { HP = 3; }
	void HitByGhost() { --HP; gotoxy(2 * pos.getX(), pos.getY()); cout << " ";  pos = def_pos; }
	/*void updateMove(const Direction& dic)//pacman
	{
		clearMe();
		pos.updateCoord(dic);
		printMe();

	}*/
	void updateMove(const Direction& dic,bool silent)//pacman
	{
		if(!silent)clearMe();
		pos.updateCoord(dic);
		if(!silent)	printMe();

	}
	void setDef_pos(Point&& x) { def_pos = x; }
};


