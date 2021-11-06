#include "Point.h"


void Point::setCoord(int _x, int _y)
{
	coord[0] = _x;
	coord[1] = _y;
}


void Point::updateCoord(Direction dic)
{
	switch (dic)
	{
	case UP:
		coord[1]--;
		break;
	case DOWN:
		coord[1]++;
		break;
	case LEFT:
		coord[0]--;
		break;
	case RIGHT:
		coord[0]++;
		break;

	default:
		break;
	}
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}