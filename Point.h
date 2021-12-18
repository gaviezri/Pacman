#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
const int IntToChar = 48;

using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT,PAUSE=11,STAY=12,DEF,QUIT};
enum class Content {WALL = (int)'#', PATH = (int)' ', FOOD = (int)'.' };



class Point {
	unsigned short coord[2];

public:
	Point(unsigned short _x = 0, unsigned short _y = 27)
	{
		coord[0] = _x;
		coord[1] = _y;
	}
	//--------------------getters--------------------
	const unsigned short getX()const{return coord[0];}
	const unsigned short getY()const{return coord[1];}
	//-------------setters---------------------
	void setX(unsigned short x) { coord[0] = x; }
	void setY(unsigned short y) { coord[1] = y; }
	void setCoord(int _x, int _y);
	//------------------operators-----------------------
	bool operator==(const Point&)const;
	bool operator!=(const Point&)const;
	Point operator+(const Point& other)const;
	Point operator-(const Point& other)const;
	bool operator<(const Point& other)const;

	//--------positioning&movement------------------------
	void updateCoord(Direction);
	void ClearPac_updateCoord(unsigned short newval, bool Xflag);
};

void ShowConsoleCursor(bool showFlag = false);
void gotoxy(int x=0, int y=0);

