#include "Board.h"

 void Board::initBoard()
{
	for (int i = 0; i < ROWS;++i)
		for (int j = 0; j < COLS; ++j)
		{
			cells[i][j].setMyCoord(i, j); //  give cell his coord / id

			if (field[i][j]) //  if field == 1 -> its a wall
			{
				
				cells[i][j].setMyContent(WALL);
			}
			else     //  its a path with food 
				cells[i][j].setMyContent(FOOD);
		}

}

 void Board::setField()
 {
	 for(int i =0;i<ROWS;++i)
		 for (int j = 0;j < COLS; ++j)
		 {
			 if (i == 0 || i == 19 || j == 0 || j == 19) //top row/col & last row/col are walls by default
				 field[i][j] = 1;
			 else if (j % 4 == 0 || i % 7 == 0)
				 field[i][j] == 1;
		 }
 }
void Board::printBoard() //
{
	for (int i = 0; i < ROWS;++i)
		for (int j = 0; j < COLS; ++j)
		{
			if (this->cells[i][j].getMyContent() == PATH)
				cout << "   "; //triple space
			else if (this->cells[i][j].getMyContent() == FOOD) // tp be updated later on for different foods
				cout << " ° ";//triple with the center as token
			else if (this->cells[i][j].getMyContent() == WALL)
				cout << " ■ ";
		}
	
}