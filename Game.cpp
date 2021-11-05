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

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

Direction Game::charToDic(char ch)  // converts given char to enum represntation
{
	if (ch == 'w' || ch == 'W' || ch == 38) return UP;
	if (ch == 's' || ch == 'S' || ch == 40) return DOWN;
	if (ch == 'a' || ch == 'A' || ch == 37) return LEFT;
	if (ch == 'd' || ch == 'D' || ch == 39) return RIGHT;
	if (ch == 'p' || ch == 'P') return PAUSE;
	if (ch == 27) return ESC;
}

void Game::play()  //  this is where the magic happens (!)
{
	Board br;
	char move;
	Direction dic = UP; // initialzing for the switch 
	Character pac('C',Point(25,9)) , ghost1('?',Point(22,6)), ghost2('?', Point(28,6));
	
	do
	{
		if (_kbhit())
		{
			move = _getch();  // record move only if user enterd one
			dic = charToDic(move);  // converts given char to enum represntation

			if ( !(br.isWall(dic, pac.getPos().getCoord() )))   // checks if next move is a wall 
			{
				pac.updateMove(dic); 
			}
		}	
		
		cout << "chill its working just fine" << endl;
		exit(0);
		
	} while (1);
}
