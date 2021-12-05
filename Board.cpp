#include "Board.h"

Board::Board()
{
	ifstream myFile("C:\\Users\\gavie\\Desktop\\mapa1.txt", ios_base::in);  // need to ask what will be the name of the text files that we will recive!
	string tmp_line;

	short  sum_cols = 0;

	while (!myFile.eof())
	{
		getline(myFile, tmp_line);
		Org_map.push_back(tmp_line);

		create_map_from_file();                    // initializing visual cells map from given file

		Play_map.push_back(Org_map[rows++]);  // copying from orignal map to the play map. increment of the rows happens here.
		
		sum_cols += tmp_line.length();
	}

	cols = sum_cols / rows;

	myFile.close();
}

void Board::create_map_from_file()
{
	short y = rows;

	for (int x = 0; x < Org_map[y].length(); ++x)
	{
		switch (Org_map[y][x])    
		{
		case ' ':
			Org_map[y][x] = '.';
			breadcrumbs++;
			break;
		case '%':
			Org_map[y][x] = ' ';
			break;
		case '$':
			Org_map[y][x] = ' ';
			ghosts.push_back(Ghost(Point(x,y))); 
			break;
		case '@':
			Org_map[y][x] = ' ';
			pac = Pacman(Point(x,y));
			break;
		case '&':
			Org_map[y][x] = ' ';
			legend = Point(x, y);
			break;
		}
	}
}

void Board::printMap(bool colored)
{
	for (int i = 0; i < rows; ++i) cout<<(colored ? "\033[34m" : "\033[37m") << Play_map[i] << endl;
}

void Board::nextContAndOppDic(Direction dic, Direction& op_dic, char& next_cont, char* cont_around)
{
	switch (dic)
	{
	case Direction::UP:
		op_dic = Direction::DOWN;
		next_cont = cont_around[(int)Direction::UP];
		break;
	case Direction::DOWN:
		op_dic = Direction::UP;
		next_cont = cont_around[(int)Direction::DOWN];
		break;
	case Direction::LEFT:
		op_dic = Direction::RIGHT;
		next_cont = cont_around[(int)Direction::LEFT];
		break;
	case Direction::RIGHT:
		op_dic = Direction::LEFT;
		next_cont = cont_around[(int)Direction::RIGHT];
		break;
	default:
		op_dic = Direction::DEF;
		break;
	}
}

char Board::nextCellCont(Point pos , Direction dic)
{
	unsigned short x = pos.getX(), y = pos.getY();

	switch (dic)
	{
	case Direction::UP:
		return (Play_map[--y][x]);
		break;
	case Direction::DOWN:
		return (Play_map[++y][x]);
		break;
	case Direction::LEFT:
		return (Play_map[y][--x]);
		break;
	case Direction::RIGHT:
		return (Play_map[y][++x]);
		break;
	default:
		return (int)Content::WALL;
		break;
	}
}

void Board::resetMap()      // copying the original map to the play map.
{
	Play_map.clear();

	for (int i = 0; i < rows; ++i)
	{
		Play_map.push_back(Org_map[i]);
	}
}

void Board::movePac(Direction dic, bool colored, short& score)
{
	char cell_c = nextCellCont(pac.getPos(), dic);
	pac.updateMove(dic, colored,rows,cols);

	if (cell_c == '.')
	{
		score++;
		changeFood2Path(pac.getPos());
	}
	

}

void Board::moveGhost(bool colored)
{

	char cont_around[4], next_cont;		//wall counter count actual walls, path around just indicate wether there is a path and we are manipulating the opposite direction to act
	short wall_counter = 0;            // as a wall by changing path_around. and keep wall_counter for real
	bool path_around[4];             // bool array that indicate by index using enum if theres a path in a given direction
	for (int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].AnalyzeAround(cont_around, path_around, Play_map, rows, cols, wall_counter);


		Direction opposite_dic;

		nextContAndOppDic(ghosts[i].getcurDic(), opposite_dic, next_cont, cont_around);//checking whats the next cell's content in the current direction im going and 
																  // updating my opposite direction

		path_around[(int)opposite_dic] = false;  // We want the ghost to treat the opposite direction as if it was a wall.

		if (next_cont == (int)Content::WALL || wall_counter == 1) //  + Or T Or L Or  or DeadEnd  junction approaching T from side or from front
			switch (wall_counter)
			{
			case 3:
				ghosts[i].updateMove(ghosts[i].setcurDic(opposite_dic), colored,Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);// Dead-End go opposite direction
				break;
			case 2:
				/*switch (rand() % 2)// two ways available, opposite direction or another one thats availabe RANDOMLY .... L Junc :)
				{
				case 0:// opposite direction
					ghosts[i].updateMove(ghosts[i].setcurDic(opposite_dic), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
					break;*/
				//case 1://direction availabe beside opposite
					for (int j = 0; j < 4; j++)
						if (path_around[j])//extracting which direction is possible and using the index equilavnt of enum we update the move.
						{
							ghosts[i].updateMove(ghosts[i].setcurDic(Direction(j)), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
							break;
						}
				
				break;
			case 1: // approaching T junction 
				Direction twoOptions[2]; // not include the opposite
				for (int k = 0, j = 0; j < 4 && k<2; ++j)    // we look for the two non-WALL options
					if (path_around[j]) twoOptions[k++] = (Direction)j;// randomly pick 1 of them which is not the opposite! 
				ghosts[i].updateMove(ghosts[i].setcurDic(twoOptions[rand() % 2]), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
				break;
			/*case 0:
				Direction threeOptions[3];
				for (int k = 0, j = 0; j < 4 && k < 3; ++j)    // we look for the two non-WALL options
					if (path_around[j]) threeOptions[k++] = (Direction)j;// randomly pick 1 of them which is not the opposite! 
				ghosts[i].updateMove((ghosts[i].getcurDic() = threeOptions[rand() % 3]), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
				break;*/
			}
		else
			ghosts[i].updateMove(ghosts[i].getcurDic(), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
		// no wall? continue same way
	}
}

bool Board::Collision()
{
	for (auto g : ghosts)
	{
		if (pac.getPos() == g.getPos())
			return true;
	}
	return false;
}