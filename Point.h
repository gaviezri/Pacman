#pragma once

class Point {
	size_t xy[2];
public:
	void setCoord(int x, int y);
	const size_t* getCoord();
};

void Point::setCoord(int x, int y)
{
	this->xy[0] = x;
	this->xy[1] = y;
}

const size_t* Point::getCoord()
{
	return xy;
}