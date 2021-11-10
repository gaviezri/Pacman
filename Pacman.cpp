#include "Pacman.h"

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
bool Pacman::Collision(Ghost ghost1, Ghost ghost2) // is pacman and ghost on same cell
{
	const unsigned short* _Pos = pos.getCoord();
	const unsigned short* _gPos1 = ghost1.getPos();
	const unsigned short* _gPos2 = ghost2.getPos();

	return ((_Pos[0] == _gPos1[0] && _Pos[1] == _gPos1[1]) || (_Pos[0] == _gPos2[0] && _Pos[1] == _gPos2[1]));
}