#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT,PAUSE=11,ESC=12,DEF};


class Point {
	unsigned short coord[2];
	friend class Pacman;
	friend class Ghost;
	
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

	void updateCoord(Direction dic, const char& avatar);

};


void gotoxy(int x=0, int y=0);

