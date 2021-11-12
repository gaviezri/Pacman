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

void Ghost::Movement(const Board& br)//getting board by reference hence const to avoid corruption & memory efficient matters
{
	bool color = br.getcolor();            
	if (def_moves_count < 4)								// this section is to make the ghost leave their cage safely and unharmed.
	{														//
		updateMove(UP, br.getcolor(), 0);					// the 1st 3 moves of the ghost is UP-UP->Left/Right
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
		short cont_around[4], wall_counter = 0, next_cont;		//wall counter count actual walls, path around just indicate wether there is a path and we are manipulating the opposite direction to act
		// as a wall by changing path_around. and keep wall_counter for real
		bool path_around[4]; // bool array that indicate by index using enum if theres a path in a given direction
		cont_around[UP] = br.getCell(cur_pos.coord[0], cur_pos.coord[1]-1).getMyContent(),		//assigning the array of the cells content around current ghost
		cont_around[DOWN] = br.getCell(cur_pos.coord[0],1+cur_pos.coord[1]).getMyContent(),		// position on the beggining of her move.
			cont_around[LEFT] = br.getCell(cur_pos.coord[0]-1, cur_pos.coord[1]).getMyContent(),
			cont_around[RIGHT] = br.getCell(1+cur_pos.coord[0], cur_pos.coord[1]).getMyContent();

		if (cur_pos.coord[0] == 4 && cur_pos.coord[1] == 7) //if ghosts are on the enterance to a secret passage / left or right
			cont_around[LEFT] = WALL;	
		if (cur_pos.coord[0] == 21 && cur_pos.coord[1] == 7)// ditto
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

		nextContAndOpDic(cur_move, op_dic, next_cont, cont_around);//checking whats the next cell's content in the current direction im going and 
																  // updating my opposite direction

		path_around[op_dic] = false;  // We want the ghost to treat the opposite direction as if it was a wall.

		if (next_cont == WALL || wall_counter == 1 ) //  + Or T Or L Or  or DeadEnd  junction approaching T from side or from front
			switch (wall_counter)
			{
			case 3:
				updateMove(cur_move = op_dic, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());// Dead-End go opposite direction
				break;
			case 2:
					switch (rand() % 2)// two ways available, opposite direction or another one thats availabe RANDOMLY .... L Junc :)
					{
						case 0:// opposite direction
							updateMove(cur_move = op_dic, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());
							break;
						case 1://direction availabe beside opposite
							for(int i =0;i<4;i++)
								if (path_around[i])//extracting which direction is possible and using the index equilavnt of enum we update the move.
								{
									updateMove(cur_move = Direction(i), color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent());
									break;
								}
					}
					break;	
			case 1: // approaching T junction in the split (from the root to the top +)
				Direction twoOptions[2]; // not include opposite
				for (int j = 0, i = 0; i < 4; ++i)    // we look for the two non-WALL options
					if (path_around[i]) twoOptions[j++] = (Direction)i;// randomly pick 1 of them 
				updateMove(cur_move = twoOptions[rand() % 2], color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent()); 
			}
		else
			updateMove(cur_move, color, br.getCell(cur_pos.coord[0], cur_pos.coord[1]).getMyContent()); // no wall? continue same way
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