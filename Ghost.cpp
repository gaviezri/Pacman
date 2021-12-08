#include "Ghost.h"


 Difficulty Ghost::diffic=Difficulty::NOVICE;

 void Ghost::setDif(int dif)
{
	switch (dif)
	{
	case 1:
		diffic = Difficulty::NOVICE;
		break;
	case 2:
		diffic = Difficulty::GOOD;
		break;
	case 3:
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
	clearMe(colored, cont);
	pos.updateCoord(dic);
	printMe(colored);
}


