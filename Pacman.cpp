#include "Pacman.h"



void Pacman::updateMove(Direction dic, bool colored,vector<string> map)
{
	gotoxy( pos.getX(), pos.getY());// putting cursor on pac's place and run it over with space
	cout << " ";
	pos.updateCoord(dic);//
	PrintMe(colored);
	
		
}
