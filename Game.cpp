#include "Game.h"


void Game::printMenu()
{
	system("cls");

	cout << "#############################################" << endl << endl;
	cout << " Welcome to Gal & Omri's version of PACMAN !" << endl;
	cout << " Please select one of the following options :" << endl;
	cout << " 1) Start a new game" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;
	cout << "#############################################" << endl;
	setChoice();

}

void  Game::setChoice()
{
	cin >> choice;
	system("cls");

	while(choice != 1 && choice != 8 && choice != 9)    /*  makes sure that the player chose one of the given options*/
	{
		cout << "Invalid choice!" << endl;

		/*std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');*/  // need to ask about this

		cout << "Please select one of the following options." << endl;
		cout << " 1) Stat a new game" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl;

		cin >> choice;
		system("cls");
	}

	switch (choice)
	{
	case 1:
		Game::play();
		break;
	case 8:
		printInstructions();
		break;
	case 9:
		cout << "Thanks for playing!! see you next time!";
		exit(1);
		break; 
	default:
		break;
	}
}

void  Game::printInstructions()
{
	cout << "The Pacman must eat all the breadcrumbs shown on screen." << endl << "The Pacman can walk freely as long as no wall is hit" << endl << " every breadcrumb is worth one point" << endl;
	cout << "Each round the Pacman starts with 3 lifes." << endl << "The Pacman must avoid contact with the ghost at all cost! if not one life will be removed." << endl;
	cout << "The player will win the game if all breadcrumbs on board are eaten and lose if all lifes are lost." << endl;
	cout << " To move UP = 'W'" << endl << " To move DOWN = 'S'" << endl << " To move LEFT = 'A'" << endl << " To move RIGHT = 'D'" << endl;
	cout << " Press any key for main menu" << endl;

	while (!_kbhit());  /*  the player will let us know that he finished reading and ready to start again*/
	_getch(); /*  "removes" the key used from screen*/

	Game::printMenu();	
	
}

/*Direction Game::charToDic(char ch)  // converts given char to enum represntation
{
	if (ch == 'w' || ch == 'W' || ch == -32) return UP;
	if (ch == 's' || ch == 'S' || ch == 80) return DOWN;
	if (ch == 'a' || ch == 'A' || ch == 75) return LEFT;
	if (ch == 'd' || ch == 'D' || ch == 77) return RIGHT;
	if (ch == 'p' || ch == 'P') return PAUSE;
	if (ch == 27) return ESC; 
	return DEF;
}*/

void Game::play()  //  this is where the magic happens (!)
{
	Direction cur_dic = UP, next_dic = UP; // initialzing for the switch 

	Ghost ghost1(Point(11, 6)), ghost2(Point(14, 6));

	br.printBoard();
	do
	{
		if (_kbhit())
		{
			updateDics(cur_dic, next_dic);// assign users input to nextdic and save the previous as cur -- NOT WORKING WELL E_RELEVENT ASSCI KEYS VALUES.
		}


		if (WALL != br.nextCellCont(next_dic, pac.getPos().getCoord()))   // checks if next move is a wall RECOGNIZE NEXT AS PATH?!

		{
			movement(next_dic);
		}
		else if (WALL != br.nextCellCont(cur_dic, pac.getPos().getCoord()))
		{

			movement(cur_dic);
		}

		if (pac.Collision(ghost1, ghost2))
		{
			//resetCharacterAndPrintingBREADCRUMBSifNecessary
			pac.HitByGhost();
		}



	} while (1);/*!Over(pac, breadcrum*/
}
void Game::movement(Direction dic)
{
	const unsigned int& _x = pac.getPos().getCoord()[0], &_y = pac.getPos().getCoord()[1];   //extraction of pacman current position.

	short cell_c = br.nextCellCont(dic, pac.getPos().getCoord());

	gotoxy(_x * 2, _y); 
	cout << " ";  //deleting previous pacman symbol from board.

	pac.updateMove(dic);  // move pacman in cur_direction
	gotoxy(_x * 2, _y);
	cout << "C";

	if (cell_c == FOOD)
	{
		score++;
		br.changeFood2Path(br.getCell(_x, _y));
	}



}


void Game::updateDics(Direction& cur, Direction& nxt)
{
	char move;
	
		_getch(); // skip the [
		cur = nxt;
		switch (move = _getch()) { // the real value
		case 'A':
			nxt = UP;
			break;
		case 'B':
			nxt = DOWN;
			break;
		case 'C':
			nxt = RIGHT;
			break;
		case 'D':
			nxt = LEFT;
			break;
		}// PAUSE, ESC , DEF
	
}