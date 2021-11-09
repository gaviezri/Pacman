#include "Board.h"



 Board::Board()
 {
	 for (int y = 0; y < ROWS; y++)//HARDCODED
	 {
		 for (int x = 0; x < COLS; x++) 
		 {	
			 cells[y][x].setMyCoord(y, x);

			 if (y == 0 || y == ROWS - 1 || (y != 7 && (x == 0 || x == COLS - 1)))
				 cells[y][x].setMyContent(WALL);
			 else if (y == 1)
			 {
				 if (x == 3 || x == 4 || x == 21 || x == 22)
					 cells[y][x].setMyContent(WALL);
				 else
					 cells[y][x].setMyContent(FOOD);
			 }
			 else if (y == 2)
			 {
				 if (x == 1 || x == 5 || x == 8 || x == 17 || x == 20 || x == 24)
					 cells[y][x].setMyContent(FOOD);
				 else
					 cells[y][x].setMyContent(WALL);
			 }
			 else if (y == 3)
			 {
				 if (x == 6 || x == 7 || x == 18 || x == 19)
					 cells[y][x].setMyContent(WALL);
				 else
					 cells[y][x].setMyContent(FOOD);
			 }
			 else if (y == 4)
			 {
				 if (x == 1 || x == 8 || x == 17 || x == 24)
					 cells[y][x].setMyContent(FOOD);
				 else
					 cells[y][x].setMyContent(WALL);;
			 }
			 else if (y == 5)
			 {
				 if (x == 3 || x == 22)
					 cells[y][x].setMyContent(WALL);
				 else
					 cells[y][x].setMyContent(FOOD);
			 }
			 else if (y == 6)
			 {
				 if (x == 4 || x == 7 || x == 18 || x == 21)
					 cells[y][x].setMyContent(FOOD);
				 else
					 cells[y][x].setMyContent(WALL);
			 }
			 else if (y == 7)
			 {
				 if((x>=0 && x<=3)||(x>=22 && x<=25))
					 cells[y][x].setMyContent(PATH);
				 else if (x > 8 && x < 17)
					 cells[y][x].setMyContent(WALL);
				 else
					 cells[y][x].setMyContent(FOOD);
			 }
			 else if (y == 8)
			 {
				 if (x == 4 || x == 6 || x == 19 || x == 21)
					 cells[y][x].setMyContent(FOOD);
				 else
					 cells[y][x].setMyContent(WALL);
			 }
			 else if (y == 9)
			 {
				 if(x==12 || x==13)
					 cells[y][x].setMyContent(PATH);

				 else if (x == 7 || x == 18)
					 cells[y][x].setMyContent(WALL);
				 else
					 cells[y][x].setMyContent(FOOD);
			 }
			 else if (y == 10)
			 {
				 if (x == 1 || x == 3 || x == 6 || x == 8 || x == 17 || x == 19 || x == 22 || x == 24)
					 cells[y][x].setMyContent(FOOD);
				 else
					 cells[y][x].setMyContent(WALL);
			 }
			 else if (y == 11)
			 {
				 if (x == 2 || (x > 10 && x < 15) || x == 23)
					 cells[y][x].setMyContent(WALL);
				 else
					 cells[y][x].setMyContent(FOOD);
			 }
		 }


	 }
 }
	
 short Board::nextCellCont(Direction dic, const unsigned short* _pos)   // checks if next move is a wall
 {
	 unsigned short x = _pos[0], y = _pos[1];
	
if (x - 1 >= 0 && x + 1 < 26)//index control to prevent runtime when approaching secret passages
		 switch (dic)
		 {
		 case UP:
			 return (cells[--y][x].getMyContent());

			 break;
		 case DOWN:
			 return (cells[++y][x].getMyContent());
			 break;
		 case LEFT:
			 return (cells[y][--x].getMyContent());
			 break;
		 case RIGHT:
			 return (cells[y][++x].getMyContent());
			 break;
		 case DEF:
			//conditions for secret passage

		 default:
			 return WALL;
			 break;
		 }
	 else return PATH;// secret passage
 }
	 
 
void Board::printBoard() 
{			

		//                      1                   2       
		//  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
     cout<< (getcolor() == true ? "\033[34m" : "\033[37m")
		<< "###################################################" << endl//0
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


