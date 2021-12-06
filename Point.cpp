#include "Point.h"


void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


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
		coord[1]--;
		break;
	case Direction::DOWN:
		coord[1]++;
		break;
	case Direction::LEFT:
		coord[0]--;
		break;
	case Direction::RIGHT:
		coord[0]++;
		break;
	case Direction::STAY:
		break;
	default:
		break;
	}
}

void ShowConsoleCursor(bool showFlag)// To hide Cursor on console 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}


bool Point::operator==(const Point& other)
{
	return (other.coord[0] == coord[0] && other.coord[1] == coord[1]);
}
bool Point::operator!=(const Point& other)const
{
	return (other.coord[0] != coord[0] || other.coord[1] != coord[1]);
}
Point Point::operator+(const Point& other)
{
	return Point(coord[0] + other.coord[0], coord[1] += other.coord[1]);
	
}
Point Point::operator-(const Point& other)
{
	return Point(coord[0] - other.coord[0], coord[1] - other.coord[1]);

}