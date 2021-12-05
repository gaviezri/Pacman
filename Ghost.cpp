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





 
 void Ghost::AnalyzeAround(char* conts, bool* paths, vector<string> map,const short& rows,const short& cols,short& wall_counter)
 {
	 wall_counter = 0;

	 conts[int(Direction::UP)] = map[pos.getY() - 1][pos.getX()],	//assigning the array of the cells content around current ghost
		 conts[int(Direction::DOWN)] = map[pos.getY() + 1][pos.getX()],	// position on the beggining of her move.
		 conts[(int)Direction::LEFT] = map[pos.getY()][pos.getX() - 1],
		 conts[(int)Direction::RIGHT] = map[pos.getY()][pos.getX() + 1];
	//secret passaage wants attention here!

	 for (int i = 0; i < 4; i++)
	 {
		 if (conts[i] == (char)Content::WALL)
		 {
			 wall_counter++; // counting walls around ghost pos
			 paths[i] = false;
		 }
		 else
			 paths[i] = true;
	 }
 }

void Ghost::updateMove(Direction dic, bool colored, short cont)
{
	gotoxy(/*2 **/ pos.getX(), pos.getY());// putting cursor on ghost's place and run it over with the cell contant
	cout <<(colored ? "\033[34m" : "\033[37m") <<(cont == (int)Content::PATH ? " " : "."); // checks cells contant and print it.
	pos.updateCoord(dic);
	printMe(colored);
}

