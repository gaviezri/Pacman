#pragma once

class Point {
	unsigned short coord[2]; // [0] == X cord , [1] == Y cord
public:
	void setCoord(int x, int y);
	const unsigned short* getCoord();
};

