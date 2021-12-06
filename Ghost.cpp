#include "Ghost.h"


 Difficulty Ghost::diffic=Difficulty::NOVICE;

 void Ghost::setDif(int dif)
{
	switch (dif)
	{
	case 0:
		diffic = Difficulty::NOVICE;
		break;
	case 1:
		diffic = Difficulty::GOOD;
		break;
	case 2:
		diffic = Difficulty::BEST;
		break;
	}
	
}

Difficulty Ghost::getDif()
{
	return Ghost::diffic;
}





 
 

void Ghost::updateMove(Direction dic, bool colored, short cont)
{
	gotoxy(pos.getX(), pos.getY());// putting cursor on ghost's place and run it over with the cell contant
	cout <<(colored ? "\033[34m" : "\033[37m") <<(cont == (int)Content::PATH ? " " : "."); // checks cells contant and print it.
	pos.updateCoord(dic);
	printMe(colored);
}

