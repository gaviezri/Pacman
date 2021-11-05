#include "Board.h"

 void Board::initCells()
{
	for (int i = 0; i < ROWS;++i)
		for (int j = 0; j < COLS; ++j)
		{
			cells[i][j].setMyCoord(i, j); //  give cell his coord / id

			if (!isSecretdoor(i,j)) //  if field == 1 -> its a wall
			{
				
				cells[i][j].setMyContent(WALL);
			}
			else if(isSecretdoor(i,j))     //  its a path with food 
				cells[i][j].setMyContent(PATH);
			else 
				cells[i][j].setMyContent(FOOD);

		}

}

 Board::Board()
 {
	
	 
 }
	
 bool Board::isWall(Direction dic, const unsigned short* _pos)   // checks if next move is a wall
 {
	 unsigned short x = _pos[0], y = _pos[1];

	 switch (dic)
	 {
	 case UP:
		 return (field[x][--y] == 1);
		 break;
	 case DOWN:
		 return (field[x][++y] == 1);
		 break;
	 case LEFT:
		 return (field[--x][y] == 1);
		 break;
	 case RIGHT:
		 return (field[++x][y] == 1);
		 break;

	 default:
		 break;
	 }
 }
	 
 
void Board::printBoard() //
{			//           1 1 1 1 2 2 2 2 2 3 3 3 3
			// 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 
	cout <<"#######################################" << endl//0
		<< "# . . . . # . . . . . . . . # . . . . #"  << endl//1 // play occurs on even indexes cells only (because of spaces between chars
		<< "# . ### . # . ########### . # . ### . #" << endl
		<< "# . # . . . . . . . . . . . # . . # . #" << endl//3
		<< "# . # . ### . ##       ## . ### . # . #" << endl//4
		<< "  . . . . . . #         # . . . . . .  " << endl//5
		<< "  . # . ### . ########### . ### . # .  " << endl//6
		<< "# . # . . # . . . . . . . . # . . # . #" << endl//7
		<< "# . ### . # . ########### . # . ### . #" << endl//8
		<< "# . . . . # . . . . . . . . # . . . . #" << endl//9
		<< "#######################################";
}

bool Obstacle(short i, short j)
{
	return ((j == 4 || j== 36 ) && (i == 2 || i == 3 || i == 4 || i == 6 || i==7 || i == 8));//||()||()||()||())
}
