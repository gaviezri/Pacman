#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT,PAUSE=11,STAY=12,DEF,QUIT};
enum class Content {WALL = (int)'#', PATH = (int)' ', FOOD = (int)'.' };

class Point {
	unsigned short coord[2];
	void ClearPac_updateCoord(unsigned short newval, bool Xflag);

public:
	Point(unsigned short _x = -1, unsigned short _y =  -1)
	{
		coord[0] = _x;
		coord[1] = _y;
	}

	const unsigned short* getCoord()
	{
		return coord;
	}

	const unsigned short getX()
	{
		return coord[0];
	}
	const unsigned short getY()
	{
		return coord[1];
	}


	void setCoord(int _x, int _y);

	bool operator==(const Point&);
	bool operator!=(const Point&)const;
	Point operator+(const Point& other);
	Point operator-(const Point& other);

	bool portals(Direction dic,vector<string>);
	void updateCoord(Direction);
	static bool isBlank(char);
};

void ShowConsoleCursor(bool showFlag = false);
void gotoxy(int x=0, int y=0);

