#include "Point.h"



void Point::setCoord(int _x, int _y)
{
	coord[0] = _x;
	coord[1] = _y;
}

void Point::ClearPac_updateCoord(unsigned short newval, bool Xflag)
{
	gotoxy(coord[0], coord[1]);
	cout << " ";
	if (Xflag)
		coord[0] = newval;
	else
		coord[1] = newval;

}

void Point::updateCoord(Direction dic)
{
	switch (dic)
	{
	case Direction::UP:
		if(coord[1]-1>=0)
			coord[1]--;
		break;
	case Direction::DOWN:
		if(coord[1]+1<=80)
		coord[1]++;
		break;
	case Direction::LEFT:
		if(coord[0]-1 >=0)
		coord[0]--;
		break;
	case Direction::RIGHT:
		if(coord[1]+1<=200)
		coord[0]++;
		break;
	case Direction::STAY:
		break;
	default:
		break;
	}
}

bool Point::operator==(const Point& other)const
{
	return (other.coord[0] == coord[0] && other.coord[1] == coord[1]);
}

bool Point::operator!=(const Point& other)const
{
	return (other.coord[0] != coord[0] || other.coord[1] != coord[1]);
}

Point Point::operator+(const Point& other)const
{
	return Point(coord[0] + other.coord[0], coord[1] + other.coord[1]);
	
}

bool Point::operator<(const Point& other)const
{
	return pow(coord[0],2) + pow(coord[1],2) < pow(other.coord[0], 2) + pow(other.coord[1], 2);
}

Point Point::operator-(const Point& other)const
{
	short int X = static_cast<short int>(coord[0] - other.coord[0]);
	short int Y = static_cast<short int>(coord[1] - other.coord[1]);

	if (X < 0)
		X = 0;
	if (Y < 0)
		Y = 0;
	return Point(X,Y);
}

Point extractPointFromStr(std::string::iterator& pstr)
{	
	int i = 0;
	string Xval, Yval;
	if (*pstr != '(') throw Error("Error: Line 87 in Point.cpp - the pointer of result is unsynchronized");

	
		while (*(++pstr) != ',')
		{
			Xval[i++] = *pstr;
		}
		i = 0;
		while (*(++pstr) != ')')
		{
			Yval[i++] = *pstr;
		}
		++pstr;
	return Point(unsigned short(std::stoul(Xval)), unsigned short(std::stoul(Yval)));
}

void ShowConsoleCursor(bool showFlag)// To hide Cursor on console 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
