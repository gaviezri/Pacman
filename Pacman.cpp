#include "Pacman.h"



void Pacman::updateMove(Direction dic, bool colored,short rows, short cols)
{
	gotoxy(/*2 **/ pos.getX(), pos.getY());// putting cursor on pac's place and run it over with space
	cout << " ";
	pos.updateCoord(dic);//
	pos.portals(dic, rows, cols);
	PrintMe(colored);
}
