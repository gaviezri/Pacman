#include "Game.h"
void Game::NewRound()
{
	cout << "\a"; // SOUND FOR COLLISON!
	if (pac.getHP() != 0)
	{
		pac.HitByGhost();// -1 hp
		pac.printHP(colored); // 
		pauseGAME();
		pac.resetMe();// reset pac pos
		g1.resetMe(br.getCell(g1.getPos()[0], g1.getPos()[1]).getMyContent(), colored);//rest ghosts and print their previous cell content back
		g2.resetMe(br.getCell(g2.getPos()[0], g2.getPos()[1]).getMyContent(), colored);
	}
}

void Game::printMenu()
{
	cout << "\033[37m";
	ResetGame();
	br = Board();
	system("cls");
	short color;
	cout << "for color mode enter 1, for B&W enter 0 : ";
	color = _getch() - 48;
	br.setcolor(color == 1 ? true : false);
	
	system("cls");
	cout << (br.getcolor() == true ? "\033[33m" : "\033[37m") << "#############################################" << endl << endl;
	cout << " Welcome to Gal & Omri's version of PACMAN !" << endl;
	cout << " Please select one of the following options :" << endl;
	cout << " 1) Start a new game" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;
	cout << "#############################################" << endl;
	setChoice();

}

void  Game::setChoice()
{
	choice = _getch() - 48;
	system("cls");

	while(choice != 1 && choice != 8 && choice != 9)    /*  makes sure that the player chose one of the given options*/
	{
		cout << "Invalid choice!" << endl;

		cout << "Please select one of the following options." << endl;
		cout << " 1) Stat a new game" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl;

		choice = _getch()-48;
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
	cout << " To move UP = 'W'" << endl << " To move DOWN = 'X'" << endl << " To move LEFT = 'A'" << endl << " To move RIGHT = 'D'"<<endl<<"To stay in your place = S" << endl;
	cout << " Press any key for main menu" << endl;

	while (!_kbhit());  /*  the player will let us know that he finished reading and ready to start again*/
	_getch(); /*  "removes" the key used from screen*/
	printMenu();	
}

void Game::play()  //  this is where the magic happens (!)
{	
	ShowConsoleCursor(false);
	pac.resetHP();
	colored = br.getcolor();
	bool everyothermove = true;
	Direction cur_dic=DEF , next_dic = DEF, last_dic = DEF; // initialzing for the switch 
	br.printBoard();
	pac.printHP(colored); 
	printScore();
	pac.movement(DEF, br, score);   // PRINTING
	g1.Movement(br);				//	CHARACTERS BEFORE GAME STARTS
	g2.Movement(br);				//
	updateDics(cur_dic);//game is frozen until first hit1
	do
	{
		if (_kbhit())
			updateDics(next_dic);// assign next move to next_dic
		if (pause)	// if P / p was hit
			pauseGAME();
		if (_kbhit())
			updateDics(next_dic);// in case user ended PAUSE with the new move
		
		if (next_dic == STAY)
			cur_dic = STAY;

		if (pac.isPortaling()) // user cannot engage pacman while he is tunneling, like mario going inside pipes
		{
			pac.movement(last_dic, br, score);//-------------------->>>>> TODO PRINT SCORE METHOD
			cur_dic = last_dic;
		}

		else if (WALL != br.nextCellCont(next_dic, pac.getPos()))  //advance to next direction if its not a wall
		{
			pac.movement(next_dic, br, score);
			last_dic = cur_dic = next_dic;// remember the new directio
			next_dic = DEF; // default the next direction
		}
		else if (WALL != br.nextCellCont(cur_dic, pac.getPos())) // advance in current direction if the 
		{																	// requested next isnt possible
			pac.movement(cur_dic, br, score);
			last_dic = cur_dic;
		}
		else
			Sleep(300);
		if (Collision())
			NewRound();
		if (everyothermove)
		{
			g1.Movement(br);
			g2.Movement(br);
			everyothermove = false;
		}
		else
			everyothermove = true;
		
		
	 if (Collision())
			 NewRound();
		 cout.flush();
		 printScore();
	} while (!Over());
	if (win == true)
		Winner();
	else
		Loser();
}

bool Game::Collision()
{
	const unsigned short* PAC = pac.getPos(), *G1 = g1.getPos(), *G2 = g2.getPos();
	if (PAC[0] == G1[0] && PAC[1] == G1[1])
		return true;
	if (PAC[0] == G2[0] && PAC[1] == G2[1])
		return true;
	return false;
	
}

void Game::printScore()
{
	 gotoxy(2, 14);
	 
	 cout << (colored ? "\033[29m" : "\033[37m") << "SCORE: " << score;
}

void Game::ResetGame()
{
	pac.resetMe();
	g1.resetMe(br.getCell(g1.getPos()[0], g1.getPos()[1]).getMyContent(), colored);
	g2.resetMe(br.getCell(g1.getPos()[0], g1.getPos()[1]).getMyContent(), colored);
	score = 0;
	pause = false;
	win = false;
	choice = 0;
	colored = false;
}

void Game::Winner()
{
	system("cls");
	gotoxy(0, 5);
	cout << (br.getcolor() == true ? "\033[33m" : "\033[37m")<<"CONGRATULATIONS! You've eaten all the breadcrumbs (Rewards will be sent upon request)." << endl;
	pauseGAME();
	printMenu();
}

void Game::Loser()
{
	system("cls");
	gotoxy(11, 5);
	cout << (br.getcolor() == true ? "\033[33m" : "\033[37m") << "Yikes! better luck next time..." << endl;
	pauseGAME();
	printMenu();
}

void Game::pauseGAME()
{
	gotoxy(12, 20);
	cout << "Press Any Key To Continue.";
	_getch();
	pause = false;
	gotoxy(12, 20);
	cout << "                           ";
}


void Game::updateDics( Direction& nxt)
{
	char move;
	move = _getch();
	if (move == 'w' || move == 'W' || move == '\'') nxt = UP;
	if (move == 'x' || move == 'X' || move == 'ס') nxt = DOWN;
	if (move == 'a' || move == 'A' || move == 'ש') nxt = LEFT;
	if (move == 'd' || move == 'D' || move == 'ג') nxt = RIGHT;
	if (move == 's' || move == 'S' || move == 'ד') nxt = STAY;
	if (move == 'p' || move == 'P' || move == 'פ' || move == 27) pause = true;
}


