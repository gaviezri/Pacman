#include "Point.h"


void Point::setCoord(int _x, int _y)
{
	coord[0] = _x;
	coord[1] = _y;
}

void Point::portals(Direction dic, short rows, short cols)//comparison between indexes in same string (horizontaly) & first and last (relatively, meunach)
{
	if (coord[0] == 0 && dic == Direction::LEFT)
		coord[0] = cols - 1;
	else if (coord[0] == cols - 1 && dic == Direction::RIGHT)
		coord[0] = 0;
	else if (coord[1] == 0 && dic == Direction::UP)
		coord[1] = rows - 1;
	else if (coord[1] == rows - 1 && dic == Direction::DOWN)
		coord[1] = 0;
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
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

bool Point::operator==(const Point& other)
{
	return (other.coord[0] == coord[0] && other.coord[1] == coord[1]);
}
bool Point::operator!=(const Point& other)const
{
	return (other.coord[0] != coord[0] || other.coord[1] != coord[1]);
}