#pragma once
#include "Point.h"// might raise error --- probably will need to be removed elsewhere


class Character
{
	char avatar;
	Point pos;

public:
	Character(char _avatar, Point _pos)
	{
		avatar = _avatar;
		pos = _pos;
	}
	

	inline void updateMove(Direction dic)
	{
		pos.updateCoord(dic);
	}

	inline void copyPos(Point newPos)
	{
		pos = newPos;
	}

	inline Point getPos()
	{
		return(pos);
	}

	inline void printMe()
	{
		cout << avatar;
	}
};

