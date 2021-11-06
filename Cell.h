#pragma once

#include "Point.h"

/* remove headers*/

enum cellcontent {PATH = 0 , WALL = 1 , FOOD = 2 };



class Cell
{
	cellcontent myContent;
	Point myCoord;

public:
	cellcontent getMyContent()
	{
		return myContent;
	}

	const unsigned short* getMyCoord()
	{
		return myCoord.getCoord();
	}

	void setMyContent(cellcontent cont)
	{
		myContent = cont;
	}

	void setMyCoord(unsigned short x, unsigned short y)
	{
		myCoord.setCoord(x, y);
	}

};

