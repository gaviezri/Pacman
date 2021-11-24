#pragma once

#include "Point.h"




const short WALL = 1;
const short PATH = 0;
const short FOOD = 2;


class Cell
{
	mutable short myContent;
	Point myCoord;

public:
	short getMyContent() const
	{
		return myContent;
	}

	const unsigned short* getMyCoord()
	{
		return myCoord.getCoord();
	}

	void setMyContent(short cont)
	{
		myContent = cont;
	}

	void setMyCoord(unsigned short x, unsigned short y)
	{
		myCoord.setCoord(x, y);
	}

};

