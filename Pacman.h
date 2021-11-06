#pragma once
#include "Point.h"// might raise error --- probably will need to be removed elsewhere
#include "Ghost.h"

class Pacman
{
	char avatar = 'C';
	Point pos;
	short HP = 3;   //pacmans health

public:
	Pacman( Point _pos)
	{
		pos = _pos;
	}
	
	short getHP()
	{
		return HP;
	}
	void HitByGhost()
	{
		--HP;
	}

	void updateMove(Direction dic)
	{
		pos.updateCoord(dic);
	}

	void copyPos(Point newPos)
	{
		pos = newPos;
	}

	Point getPos()
	{
		return(pos);
	}

	void printMe()
	{
		cout << avatar;
	}
	bool Collision(Ghost ghost1,Ghost ghost2) // is pacman and ghost on same cell
	{
		const unsigned short * _Pos = pos.getCoord();
		const unsigned short* _gPos1 = ghost1.getPos();
			const unsigned short* _gPos2 = ghost2.getPos();

		return ((_Pos[0] == _gPos1[0] && _Pos[1] == _gPos1[1]) || (_Pos[0] == _gPos2[0] && _Pos[1] == _gPos2[1]));
	}
};

