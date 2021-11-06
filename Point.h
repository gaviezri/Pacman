#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT,PAUSE=11,ESC=12};

class Point {
	unsigned short coord[2];

public:
	Point(unsigned short _x = 1, unsigned short _y = 1)
	{
		coord[0] = _x;
		coord[1] = _y;
	}

	const unsigned short* getCoord()
	{
		return coord;
	}


	void setCoord(int _x, int _y);

	void updateCoord(Direction dic);

};

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}