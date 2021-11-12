#include "Pacman.h"


void Pacman::printHP(bool colored)
{
	gotoxy(39, 14); cout << "                           ";
	gotoxy(39, 14); cout << (colored == true ? "\033[34m" : "\033[37m") <<"LIVES: "; for (int i = 0; i < HP; i++) cout << (colored == true ? "\033[33m" : "\033[37m") << avatar << " ";
}

void Pacman::movement(Direction dic, Board& br,short& score)
{
	short cell_c = br.nextCellCont(dic, pos.coord);
	updateMove(dic, br.getcolor());

	if (cell_c == FOOD)
	{
		score++;
		br.changeFood2Path(br.getCell(pos.coord[0], pos.coord[1]));
	}
	Sleep(300);
}
void Pacman::updateMove(Direction dic, bool colored)
{
	gotoxy(2 * pos.coord[0], pos.coord[1]);// putting cursor on pac's place and run it over with space
	cout << " ";
	pos.updateCoord(dic,'C');
	if ((pos.coord[0] < 3 || (pos.coord[0] > 22)) && pos.coord[1] == 7)
		inPortal = true;
	else
		inPortal = false;
	gotoxy(2 * pos.coord[0], pos.coord[1]);
	printMe(colored);
}
