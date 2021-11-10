#include "Ghost.h"

void nextContAndOpDic(Direction dic, Direction& op_dic, short& next_cont, short* cont_around)
{
	switch (dic)
	{
	case UP:
		op_dic = DOWN;
		next_cont = cont_around[UP];
		break;
	case DOWN:
		op_dic = UP;
		next_cont = cont_around[DOWN];
		break;
	case LEFT:
		op_dic = RIGHT;
		next_cont = cont_around[LEFT];
		break;
	case RIGHT:
		op_dic = LEFT;
		next_cont = cont_around[RIGHT];
		break;
	default:
		op_dic = DEF;
		break;
	}
}

void Ghost::Movement(Direction dic, const Board& br)
{
	bool color = br.getcolor();
	if (def_moves_count < 2)
	{
		updateMove(UP, br.getcolor(), 0);
	}
	if (def_moves_count == 2)
	{
		updateMove(first_move , color, 1);
	}

	short cont_around[4], wall_counter = 0, next_cont;
	bool path_around[4];
	cont_around[UP] = br.getCell(cur_pos.coord[0], --cur_pos.coord[1]).getMyContent(),
	cont_around[DOWN] = br.getCell(cur_pos.coord[0], ++cur_pos.coord[1]).getMyContent(),
	cont_around[LEFT] = br.getCell(--cur_pos.coord[0], cur_pos.coord[1]).getMyContent(),
	cont_around[RIGHT] = br.getCell(++cur_pos.coord[0], cur_pos.coord[1]).getMyContent();
	
	for (auto cont : cont_around)
	{
		if (cont == WALL)
		{
			wall_counter++; // counting walls around ghost pos
			path_around[cont] = false;
		}
		else
			path_around[cont] = true;
	}
	Direction op_dic;

	nextContAndOpDic(dic,op_dic,next_cont,cont_around);

	path_around[op_dic] = false;  // We want the ghost to treat the opposite direction as if it was a wall.

	if (next_cont == WALL)
		switch (wall_counter)
		{
		case 3:
			updateMove(op_dic,color, br.getCell(cur_pos.coord[0],cur_pos.coord[1]).getMyContent());
			break;
		case 2:
			for (int i = 0; i < 4; ++i)
			{
				if (path_around[i])
				{
					updateMove(Direction(i), color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());
					break;
				}
			}
			break;
		case 1:
			Direction twoOptions[2];
			for (int j = 0,i = 0; i < 4; ++i)    // we look for the two non-WALL options
				if (path_around[i]) twoOptions[j++] = (Direction)i;

			updateMove(twoOptions[rand()%2], color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());  // we randomly choose one of the possible directions and move the ghost there
			break;
		}
	else
		updateMove(dic, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());  // we randomly choose one of the possible directions and move the ghost there

	
}



void Ghost::updateMove(Direction dic, bool colored, short cont)
{
	gotoxy(2 * cur_pos.coord[0], cur_pos.coord[1]);// putting cursor on ghost's place and run it over with the cell contant
	cout << (cont == PATH ? " " : "."); // checks cells contant and print it.
	cur_pos.updateCoord(dic,'G');

	gotoxy(2 * cur_pos.coord[0], cur_pos.coord[1]);
	printMe(colored);
}