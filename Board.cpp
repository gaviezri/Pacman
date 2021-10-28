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

 Board::Board()
 {
	 for(int i =0;i<ROWS;++i)
		 for (int j = 0;j < COLS; ++j)
		 {
			 if ((i == 0 || i == 19 || j == 0 || j == 19)&&(!isSecretdoor(i,j))) //top row / col & last row / col are walls by default
				 field[i][j] = 1;												 //beside secret passages

			 else if((j % 4 == 2) || (i % 3 == 2))
				 field[i][j] = 1;
			 
			 else
				field[i][j] = 0;
		 } 
	 initBoard();//check later
 }
void Board::printBoard() //
{
	for (int i = 0; i < ROWS;++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			if (cells[i][j].getMyContent() == PATH)
				cout << "   "; //triple space
			else if (cells[i][j].getMyContent() == FOOD) // tp be updated later on for different foods
				cout << " . ";//triple with the center as token
			else if (cells[i][j].getMyContent() == WALL)
				cout << " @ ";
		}
		cout << endl;
	}
		
	
}