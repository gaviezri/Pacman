#include "Point.h"


void Point::setCoord(int _x, int _y)
{
	coord[0] = _x;
	coord[1] = _y;
}


void Point::updateCoord(Direction dic, const char& avatar)
{

	if (avatar == 'C' && coord[0] == 0 && coord[1] == 7 && dic == LEFT)//entering left secret passage;
		coord[0] = 25; //transport to right side of board
	else if (avatar == 'C' && coord[0] == 25 && coord[1] == 7 && dic == RIGHT) //entering right secret passage
		coord[0] = 0;// ...

	else
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
		case STAY:
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