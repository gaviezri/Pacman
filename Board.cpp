#include "Board.h"

Board::Board()
{
	ifstream myFile("C:\\Users\\gavie\\Desktop\\mapa2.txt", ios_base::in);  // need to ask what will be the name of the text files that we will recive!
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
	pac.updateMove(dic, colored,Play_map);
	if (cell_c == '.')
	{
		score++;
		changeFood2Path(pac.getPos());
	}
	

}
void Board::AnalyzeAround(Ghost g, char* conts, bool* paths)
{
	int i = 0;
	Point gPos = g.getPos();
	unsigned short Y = gPos.getY(), X = gPos.getX();


	conts[int(Direction::UP)] = Play_map[Y - 1][X],	//assigning the array of the cells content around current ghost
		conts[int(Direction::DOWN)] = Play_map[Y + 1][X],	// position on the beggining of her move.
		conts[(int)Direction::LEFT] = Play_map[Y][X - 1],
		conts[(int)Direction::RIGHT] = Play_map[Y][X + 1];

	
	if (isOnBorder((gPos - Point(1, 0))))
		conts[int(Direction::LEFT)] = (char)Content::WALL;
	if (isOnBorder((gPos - Point(0, 1))))
		conts[int(Direction::UP)] = (char)Content::WALL;
	if (isOnBorder((gPos + Point(1, 0))))
		conts[int(Direction::RIGHT)] = (char)Content::WALL;
	if (isOnBorder((gPos + Point(0, 1))))
		conts[int(Direction::DOWN)] = (char)Content::WALL;

	for ( i = 0; i < 4; i++)
	{
		if (conts[i] == (char)Content::WALL)
		{
			paths[i] = false;
		}
		else
			paths[i] = true;
	}
}
bool Board::isOnBorder(Point pos)
{
	unsigned short X = pos.getX(), Y = pos.getY();
	return (X == 0 || Y == 0 || X == Play_map[Y].length() - 1 || Y == rows-1);
}
bool Board::isBlankOnBorder(Point pos)
{
	return(isOnBorder(pos) && isblank(Play_map[pos.getY()][pos.getX()]));
}

void getOptions(vector<Direction>& d, bool* paths)
{
	d.clear();
	for (int j = 0; j < 4; ++j)
		if (paths[j])  d.push_back((Direction)j);
}
void Board::moveGhost(bool colored)
{
	char cont_around[4], next_cont;		//wall counter count actual walls, path around just indicate wether there is a path and we are manipulating the opposite direction to act
	vector<Direction> options;
	Direction opposite_dic;
	bool path_around[4];             // bool array that indicate by index using enum if theres a path in a given direction
	for (int i = 0; i < ghosts.size(); i++)
	{
		AnalyzeAround(ghosts[i], cont_around, path_around);
	
		nextContAndOppDic(ghosts[i].getcurDic(), opposite_dic, next_cont, cont_around);//checking whats the next cell's content in the current direction im going and 
																  // updating my opposite direction
		path_around[(int)opposite_dic] = false;  // We want the ghost to treat the opposite direction as if it was a wall.

		getOptions(options,path_around);

		
		if (next_cont == (int)Content::WALL) //  + Or T Or L Or  or DeadEnd  junction approaching T from side or from front
			switch (options.size())
			{
			case 0:// Dead-End go opposite direction
				ghosts[i].updateMove(ghosts[i].setcurDic(opposite_dic), colored,Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
				break;
			case 1:// ion
				ghosts[i].updateMove(ghosts[i].setcurDic(options[0]), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);
				break;
			default://T Junc 
				ghosts[i].updateMove(ghosts[i].setcurDic(options[rand() % (options.size())]), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);// choose randomly from options
				break;
			}
		else if (options.size()>=2)
			ghosts[i].updateMove(ghosts[i].setcurDic(options[rand() % (options.size())]), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);// in a 4 way junc - choose randomly
		else
			ghosts[i].updateMove(ghosts[i].getcurDic(), colored, Play_map[ghosts[i].getPos().getY()][ghosts[i].getPos().getX()]);// continue same way

		

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