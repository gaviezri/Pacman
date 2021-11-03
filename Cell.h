#pragma once

#include "Point.h"

using namespace std;

/* remove headers*/

enum cellcontent {PATH = 0 , WALL = 1 , FOOD = 2 };



class Cell
{
	cellcontent myContent;
	Point myCoord;
public:
	cellcontent getMyContent();
	const unsigned short* getMyCoord();
	void setMyContent(cellcontent cont);
	void setMyCoord(unsigned short x, unsigned short y);
};

