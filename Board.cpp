#include "Board.h"



 Board::Board()
 {
	 for (int i = 0; i < ROWS; i++)//HARDCODED
	 {
		 for (int j = 0; j < COLS; j++) // true == bWALL , false == bPATH
		 {
			 if (i == 0 || i == ROWS - 1 || (i != 7 && (j == 0 || j == COLS - 1)))
				 field[i][j] = bWALL;
			 else if (i == 1)
			 {
				 if (j == 3 || j == 4 || j == 21 || j == 22)
					 field[i][j] = bWALL;
				 else
					 field[i][j] = bPATH;
			 }
			 else if (i == 2)
			 {
				 if (j == 1 || j == 5 || j == 8 || j == 17 || j == 20 || j == 24)
					 field[i][j] = bPATH;
				 else
					 field[i][j] = bWALL;
			 }
			 else if (i == 3)
			 {
				 if (j == 6 || j == 7 || j == 18 || j == 19)
					 field[i][j] = bWALL;
				 else
					 field[i][j] = bPATH;
			 }
			 else if (i == 4)
			 {
				 if (j == 1 || j == 8 || j == 17 || j == 24)
					 field[i][j] = bPATH;
				 else
					 field[i][j] = bWALL;
			 }
			 else if (i == 5)
			 {
				 if (j == 3 || j == 22)
					 field[i][j] = bWALL;
				 else
					 field[i][j] = bPATH;
			 }
			 else if (i == 6)
			 {
				 if (j == 4 || j == 6 || j == 19 || j == 21)
					 field[i][j] = bPATH;
				 else
					 field[i][j] = bWALL;
			 }
			 else if (i == 7)
			 {
				 if (j > 8 && j < 17)
					 field[i][j] = bWALL;
				 else
					 field[i][j] = bPATH;
			 }
			 else if (i == 8)
			 {
				 if (j == 4 || j == 6 || j == 19 || j == 21)
					 field[i][j] = bPATH;
				 else
					 field[i][j] = bWALL;
			 }
			 else if (i == 9)
			 {
				 if (j == 7 || j == 18)
					 field[i][j] = bWALL;
				 else
					 field[i][j] = bPATH;
			 }
			 else if (i == 10)
			 {
				 if (j == 1 || j == 3 || j == 6 || j == 8 || j == 17 || j == 19 || j == 22 || j == 24)
					 field[i][j] = bPATH;
				 else
					 field[i][j] = bWALL;
			 }
			 else if (i == 11)
			 {
				 if (j == 2 || (j > 10 && j < 15) || j == 23)
					 field[i][j] = bWALL;
				 else
					 field[i][j] = bPATH;
			 }
		 }


	 }
	 for (int i = 0; i < ROWS; ++i)
		 for (int j = 0; j < COLS; j++)
		 {

			 cells[i][j].setMyCoord(i, j); //  give cell his coord / id

			 if (!isSecretdoor(i, j)) //  if field == 1 -> its a wall
			 {

				 cells[i][j].setMyContent(WALL);
			 }
			 else if (isSecretdoor(i, j))     //  its a path with food 
				 cells[i][j].setMyContent(PATH);
			 else
				 cells[i][j].setMyContent(FOOD);

		 }
	 
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
	 
 
void Board::printBoard() 
{			
//            1         2         3         4         5 
		//  012345678901234567890123456789012345678901234567890
	cout << "###################################################" << endl//0
		<< "# . . ### . . . . . . . . . . . . . . . . ### . . #" << endl//1 // play occurs on even indexes cells only (because of spaces between chars
		<< "# . ##### . ### . ############### . ### . ##### . #" << endl//2
		<< "# . . . . . ### . . . . . . . . . . ### . . . . . #" << endl//3
		<< "# . ########### . ############### . ########### . #" << endl//4
		<< "# . . # . . . . . . . . . . . . . . . . . . # . . #" << endl//5
		<< "####### . ### . #####         ##### . ### . #######" << endl//6
		<< "        . . . . . ####       #### . . . . .        " << endl//7
		<< "####### . # . ####################### . # . #######" << endl//8
		<< "# . . . . . . # . . . .     . . . . # . . . . . . #" << endl//9
		<< "# . # . ### . # . ############### . # . ### . # . #" << endl//10
		<< "# . # . . . . . . . . ####### . . . . . . . . # . #" << endl//11
		<< "###################################################";//12
} 	    //  012345678901234567890123456789012345678901234567890
		//            1         2         3         4         5


bool Obstacle(short i, short j)
{
	return ((j == 4 || j== 36 ) && (i == 2 || i == 3 || i == 4 || i == 6 || i==7 || i == 8));//||()||()||()||())
}
