#pragma once

class Point {
	unsigned short coord[2]; // [0] == X cord , [1] == Y cord
public:
	void setCoord(int x, int y);
	const unsigned short* getCoord();
};

void Point::setCoord(int x, int y)
{
	coord[0] = x;
	coord[1] = y;
}

const unsigned short* Point::getCoord()
{
	return coord;
}