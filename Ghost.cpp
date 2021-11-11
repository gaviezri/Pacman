#include "Ghost.h"


short Ghost::def_moves_count=0;

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

void Ghost::Movement(const Board& br)//FIX BUGS HERE
{
	bool color = br.getcolor();
	if (def_moves_count < 4)
	{
		updateMove(UP, br.getcolor(), 0);
		def_moves_count++;
	}
	else if (def_moves_count == 4 || def_moves_count == 5)
	{
		cur_move = first_move;
		updateMove(cur_move , color, 1);
		def_moves_count++;
	}
	else
	{
		short cont_around[4], wall_counter = 0, next_cont;
		bool path_around[4];
		cont_around[UP] = br.getCell(cur_pos.coord[0], cur_pos.coord[1]-1).getMyContent(),
		cont_around[DOWN] = br.getCell(cur_pos.coord[0],1+cur_pos.coord[1]).getMyContent(),
			cont_around[LEFT] = br.getCell(cur_pos.coord[0]-1, cur_pos.coord[1]).getMyContent(),
			cont_around[RIGHT] = br.getCell(1+cur_pos.coord[0], cur_pos.coord[1]).getMyContent();
		if (cur_pos.coord[0] == 4 && cur_pos.coord[1] == 7)
			cont_around[LEFT] = WALL;
		if (cur_pos.coord[0] == 21 && cur_pos.coord[1] == 7)
			cont_around[RIGHT] = WALL;
		for (int i = 0 ;i<4; i ++)
		{
			if (cont_around[i] == WALL)
			{
				wall_counter++; // counting walls around ghost pos
				path_around[i] = false;
			}
			else
				path_around[i] = true;
		}
		Direction op_dic;

		nextContAndOpDic(cur_move, op_dic, next_cont, cont_around);

		path_around[op_dic] = false;  // We want the ghost to treat the opposite direction as if it was a wall.

		if (next_cont == WALL || wall_counter == 1 ) // T Or L or DeadEnd  junction approaching T from side or from front
			switch (wall_counter)
			{
			case 3:
				updateMove(cur_move = op_dic, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());// Dead-End go opposite direction
				break;
			case 2:
					switch (rand() % 2)// two ways available, opposite direction or another one thats availabe RANDOMLY :)
					{
						case 0:// opposite
							updateMove(cur_move = op_dic, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());
							break;
						case 1://the other possible
							for(int i =0;i<4;i++)
								if (path_around[i])
								{
									updateMove(cur_move = Direction(i), color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());
									break;
								}
					}
					break;	
			case 1: // approaching T junction in the split (from the root to the top T)
				Direction twoOptions[2];
				for (int j = 0, i = 0; i < 4; ++i)    // we look for the two non-WALL options
					if (path_around[i]) twoOptions[j++] = (Direction)i;
				updateMove(cur_move = twoOptions[rand() % 2], color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());  // we randomly choose one of the possible directions and move the ghost there
			}
		else
			updateMove(cur_move, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());  // we randomly choose one of the possible directions and move the ghost there
	}	
}



void Ghost::updateMove(Direction dic, bool colored, short cont)
{
	gotoxy(2 * cur_pos.coord[0], cur_pos.coord[1]);// putting cursor on ghost's place and run it over with the cell contant
	cout <<(colored ? "\033[34m" : "\033[37m") <<(cont == PATH ? " " : "."); // checks cells contant and print it.
	cur_pos.updateCoord(dic,'G');

	gotoxy(2 * cur_pos.coord[0], cur_pos.coord[1]);
	printMe(colored);
}