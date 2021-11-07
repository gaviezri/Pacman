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

void Game::play()  //  this is where the magic happens (!)
{
	bool TEST;
	Direction cur_dic=DEF , next_dic = DEF; // initialzing for the switch 

	Ghost ghost1(Point(11, 6)), ghost2(Point(14, 6));

	br.printBoard();
	updateDics(cur_dic);//game is frozen until first hit
	do
	{
		if (_kbhit())
		{
			updateDics(cur_dic, next_dic);// assign users input to nextdic and save the previous as cur -- NOT WORKING WELL E_RELEVENT ASSCI KEYS VALUES.
		}
		if (pause)	
			pauseGAME();
		
		if (WALL != br.nextCellCont(next_dic, pac.getPos().getCoord()))   // checks if next move is a wall RECOGNIZE NEXT AS PATH?!
		{
			movement(next_dic);
			cur_dic = next_dic;
			next_dic = DEF;
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

		TEST = !Over();

	} while (TEST);
}

void Game::pauseGAME()
{
	gotoxy(12, 20);
	cout << "Press Any Key To Continue.";
	while (!_getch());
	pause = false;
	gotoxy(12, 20);
	cout << "                           ";
}
void Game::movement(Direction dic)
{
	//const unsigned int& _x = pac.getPos().getCoord()[0], &_y = pac.getPos().getCoord()[1];   //extraction of pacman current position.
	
	short cell_c = br.nextCellCont(dic, pac.getPos().getCoord());

	gotoxy(pac.getPos().getCoord()[0] * 2, pac.getPos().getCoord()[1]);
	cout << " ";  //deleting previous pacman symbol from board.

	pac.updateMove(dic);  // move pacman in cur_direction

	gotoxy(pac.getPos().getCoord()[0] * 2, pac.getPos().getCoord()[1]);
	cout << "C";

	if (cell_c == FOOD)
	{
		score++;
		br.changeFood2Path(br.getCell(pac.getPos().getCoord()[0], pac.getPos().getCoord()[1]));
	}

	Sleep(500);

}


void Game::updateDics(Direction& cur, Direction& nxt)
{
	char move;
	move = _getch();
	
	if (move == 'w' || move == 'W') nxt = UP;
	if (move == 's' || move == 'S') nxt = DOWN;
	if (move == 'a' || move == 'A') nxt = LEFT;
	if (move == 'd' || move == 'D') nxt = RIGHT;
	if (move == 'p' || move == 'P') pause = true;
	
}

void Game::updateDics(Direction& cur)
{
	char move;
	move = _getch();
	if (move == 'a' || move == 'A') cur = LEFT;
	if (move == 'd' || move == 'D') cur = RIGHT;

}
