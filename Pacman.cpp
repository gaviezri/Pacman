#include "Pacman.h"



void Pacman::updateMove(Direction dic, bool colored,vector<string> map)
{
	clearMe();
	pos.updateCoord(dic);//
	printMe(colored);
	
}
