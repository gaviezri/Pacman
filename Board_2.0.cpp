#include "Board_2.0.h"

_Board::_Board()
{
	ifstream myFile("C:\\Users\\Omri\\Desktop\\mapa1", ios_base::in);  // need to ask what will be the name of the text files that we will recive!
	string tmp_line;

	short  sum_cols = 0;

	while (!cin.eof())
	{
		getline(myFile, tmp_line);
		Org_map.push_back(tmp_line);

		changeVisualCells();                    // initializing visual cells map from given file

		Play_map.push_back(Org_map[rows++]);  // copying from orignal map to the play map. increment of the rows happens here.
		sum_cols += tmp_line.length();
	}

	cols = sum_cols / rows;

	myFile.close();
}

void _Board::changeVisualCells()
{
	short y = rows;

	for (int x = 0; x < Org_map[y].length(); ++x)
	{
		switch (Org_map[y][x])    
		{
		case ' ':
			Org_map[y][x] = '.';
			break;
		case '%':
			Org_map[y][x] = ' ';
			break;
		case '$':
			Org_map[y][x] = ' ';
			ghosts.push_back(Ghost(Point(y,x),DEF)); 
			break;
		case '@':
			Org_map[y][x] = ' ';
			pac = Pacman(Point(y,x));
		case '&':
			Org_map[y][x] = ' ';
			legend = Point(y, x);
		}
	}
}

void _Board::printMap(bool colored)
{
	for (int i = 0; i < rows; ++i) cout<<(colored ? "\033[34m" : "\033[37m") << Play_map[i] << endl;
}

char _Board::nextCellCont(Point pos , Direction dic)
{
	unsigned short x = pos.getX(), y = pos.getY();

	switch (dic)
	{
	case UP:
		return (Play_map[--y][x]);
		break;
	case DOWN:
		return (Play_map[++y][x]);
		break;
	case LEFT:
		return (Play_map[y][--x]);
		break;
	case RIGHT:
		return (Play_map[y][++x]);
		break;
	default:
		return '#';
		break;
	}
}

void _Board::resetMap()      // copying the original map to the play map.
{
	Play_map.clear();

	for (int i = 0; i < rows; ++i)
	{
		Play_map.push_back(Org_map[i]);
	}
}