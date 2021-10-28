#include "Point.h"

void Point::setCoord(int x, int y)
{
	coord[0] = x;
	coord[1] = y;
}

const unsigned short* Point::getCoord()
{
	return coord;
}