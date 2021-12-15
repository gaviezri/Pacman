#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
const int IntToChar = 48;
enum class Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
using namespace std;

enum class Direction { UP, DOWN, LEFT, RIGHT,PAUSE=11,STAY=12,DEF,QUIT};
enum class Content {WALL = (int)'#', PATH = (int)' ', FOOD = (int)'.' };
void setTextColor(Color colorToSet);


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
	static bool U_above_D(const Point& U, const Point& D) { return U.coord[1] + 1 == D.coord[1]; }
	static bool L_left_R(const Point& L, const Point& R) { return R.coord[0]  == L.coord[0] + 1; }
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

