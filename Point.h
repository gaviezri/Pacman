#pragma once
#include <iostream>
#include <string>// problematic?
#include <Windows.h>
#include <vector>
const int IntToChar = 48;

using namespace std;

struct Error
{
	string msg;

	Error(string _msg) : msg(_msg) {}
};

enum class Direction {
	UP, DOWN, LEFT, RIGHT, PAUSE = 11, STAY = 12, DEF, QUIT
};


enum class Content {WALL = (int)'#', PATH = (int)' ', FOOD = (int)'.' };

inline Direction charToDic(char ch) 
{
	if (ch == 'w' || ch == 'W') return Direction::UP;
	if (ch == 'x' || ch == 'X' ) return Direction::DOWN;
	if (ch == 'a' || ch == 'A') return  Direction::LEFT;
	if (ch == 'd' || ch == 'D') return Direction::RIGHT;
	if (ch == 's' || ch == 'S') return Direction::STAY;
}

inline char dicToChar(Direction dic)
	{
	switch (dic)
	{
	case Direction::UP:
		return 'W';
		break;
	case Direction::DOWN:
		return 'X';
		break;
	case Direction::LEFT:
		return 'A';
		break;
	case Direction::RIGHT:
		return 'D';
		break;
	case Direction::STAY:
		return 'S';
		break;
	}
	}

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
Point extractPointFromStr(std::string::iterator&, std::string::iterator);
