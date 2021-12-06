#include "Game.h"
void PacmanLogo();

void Game::play()  //  this is where the magic happens (!)
{
	ShowConsoleCursor(false);
	cout << "\033[37m";// to reset color loaded on cout
	system("cls");
	PacmanLogo();
	Color();
	system("cls");
menu:
	printMenu();
	setChoice();
	switch (choice)
	{
	case 1:
		Engine();
		ResetGame();
		break;
	case 8:
		printInstructions();
		break;
	case 9:
		cout << endl << endl << endl << "          Thanks for playing!! see you next time!" << endl << endl << endl << endl;
		Sleep(3000);
		exit(1);
		break;
	default:
		break;
	}
	goto menu;
}




/*void Game::NewRound() // when pac meets ghost
{
	cout << "\a"; // SOUND FOR COLLISON!
	pac.HitByGhost();// -1 hp
	if (pac.getHP() != 0)
	{
		pac.printHP(colored); // update remaining lives on screen
		pac.resetMe();// reset pac pos
		gotoxy(2*pac.getPos()[0],pac.getPos()[1]);
		pac.printMe(colored);
		g1.resetMe(br.getCell(g1.getPos()[0], g1.getPos()[1]).getMyContent(), colored);//reset ghosts and print their previous cell content back
		g2.resetMe(br.getCell(g2.getPos()[0], g2.getPos()[1]).getMyContent(), colored);
		pauseGAME();
	}
}
*/
void Game::setDif()
{
	
	    	
	char ch=-1;
	while (ch != 0 && ch != 1 && ch != 2)
	{
		system("cls");
		cout << "Select your difficulty" << endl << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "0 = \"Novice\"" << endl << "1 = \"Good\"" << endl << "2 = \"Best\"" << endl;
		cout << "selection: ";
		ch = _getch()-48;
	}
	Ghost::setDif(ch);
	system("cls");
	cout << "LET'S GO!";
	Sleep(2000);
	system("cls");
}

void Game::printMenu()
{
	
	system("cls");
	cout << (colored ? "\033[33m" : "\033[37m") << "#############################################" << endl << endl;
	cout << " Welcome to Gal & Omri's version of PACMAN !" << endl;
	cout << " Please select one of the following options :" << endl;
	cout << " 1) Start a new game" << endl<< " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;
	cout << "#############################################" << endl;
}

void  Game::setChoice()
{
	choice = _getch() - 48;
	

	while(choice != 1 && choice != 8 && choice != 9 )    //  makes sure that the player chose one of the given options
	{
		system("cls");
		cout << "Invalid choice!" << endl;

		cout << "Please select one of the following options." << endl;
		cout << " 1) Start a new game" << endl  << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;

		choice = _getch()-48;
	}
}

void  Game::printInstructions()
{
	cout << "The Pacman must eat all the breadcrumbs shown on screen." << endl << "The Pacman can walk freely as long as no wall is hit" << endl << " every breadcrumb is worth one point" << endl;
	cout << "Each round the Pacman starts with 3 lifes." << endl << "The Pacman must avoid contact with the ghost at all cost! if not one life will be removed." << endl;
	cout << "The player will win the game if all breadcrumbs on board are eaten and lose if all lifes are lost." << endl;
	cout << " To move UP = 'W'" << endl << " To move DOWN = 'X'" << endl << " To move LEFT = 'A'" << endl << " To move RIGHT = 'D'" << endl << "To stay in your place = S" << endl << "To exit game and go to main menu = TAB" << endl<<"To Pause game = P or Esc"<<endl;
	cout << endl<<" Press any key for main menu" << endl;

	while (!_kbhit());  //  the player will let us know that he finished reading and ready to start again
	_getch(); //  "removes" the key used from screen	
}
void Game::ghosts_movemaker()
{
	if (everyothermove)//ghost movement manager that makes ghost move everyother move that pacman makes
		{
			br.moveGhost(colored);

			everyothermove = false;// switch off
		}
		else
			everyothermove = true;// switch on
}
void Game::Engine()
{
	setDif(); // sets the difficulty of the ghosts
	br.Pac().resetHP();
	
	Direction cur_dic = Direction::DEF, next_dic = Direction::DEF, last_dic = Direction:: DEF; // initialzing for the switch 
	br.printMap(colored);
	//printlegend(br.getlegend(), br.Pac().getHP());
	br.Pac().PrintMe(colored);   // PRINTING
	for (auto g : br.Ghosts())
		g.PrintMe(colored);
	updateDics(cur_dic);//game is frozen until first hit1
	do
	{
		if (_kbhit())
			updateDics(next_dic);// assign next move to next_dic    
		if (pause)	// if P / p /Esc was hit
			pauseGAME();
		if (next_dic == Direction::QUIT)
			printMenu();
		if (_kbhit())
			updateDics(next_dic);// in case user ended PAUSE with the new move

		if (next_dic == Direction::STAY)// pac is now frozen on the current cell until next input is recieved
			cur_dic = Direction::STAY;

		else if (br.Pac().getPos().portals(cur_dic, br.getPlay_map()))
			br.Pac().PrintMe(colored);
				
		else if (int(Content::WALL) != br.nextCellCont(br.Pac().getPos(),next_dic))  //advance to next direction if its not a wall
		{
			br.movePac(next_dic, colored,score);
			last_dic = cur_dic = next_dic;// remember the new directio
			next_dic = Direction::DEF; // default the next direction
		}
		else if (int(Content::WALL) != br.nextCellCont(br.Pac().getPos(), cur_dic)) // advance in current direction if the 
		{																	// requested next isnt possible
			br.movePac(cur_dic, colored, score);
			last_dic = cur_dic;
		}

		Sleep(300);
		if (br.Collision());
			//NewRound();
		
		ghosts_movemaker();


		if (br.Collision());//if one of the ghosts and pacman share the same cell
			//NewRound();//update necessary info and reset avatars to default positions
//		printScore(br.getlegend());
	} while (!Over());
	if (win == true)
		Winner();// cout message
	else
		Loser();// kanal
}




void Game::printScore(Point legend)
{
	 gotoxy(legend.getX(),legend.getY());
	 
	 cout << (colored ? "\033[29m" : "\033[37m") << "SCORE: " << score;
}

void Game::ResetGame()
{
	br.resetCharacters();
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
	cout << (colored ? "\033[33m" : "\033[37m")<<"CONGRATULATIONS! You've eaten all the breadcrumbs (Rewards will be sent upon request)." << endl;
	pauseGAME();

}

void Game::Loser()
{
	system("cls");
	gotoxy(11, 5);
	cout << (colored ? "\033[33m" : "\033[37m") << "Yikes! better luck next time..." << endl;
	pauseGAME();
}

void Game::pauseGAME()
{
	gotoxy(12, 20);
	cout << "Press Any Key To Continue.";
	_getch();//stall the program until a key is hit
	pause = false;
	gotoxy(12, 20);
	cout << "                           ";
}


void Game::updateDics( Direction& nxt)
{
	char move;
	move = _getch();
	if (move == 'w' || move == 'W' || move == '\'') nxt = Direction::UP;
	if (move == 'x' || move == 'X' || move == 'ס') nxt = Direction::DOWN;
	if (move == 'a' || move == 'A' || move == 'ש') nxt = Direction::LEFT;
	if (move == 'd' || move == 'D' || move == 'ג') nxt = Direction::RIGHT;
	if (move == 's' || move == 'S' || move == 'ד') nxt = Direction::STAY;
	if (move == 'p' || move == 'P' || move == 'פ' || move == 27) pause = true;
	if (move == '\t') nxt = Direction::QUIT;
}



void PacmanLogo()
{
	gotoxy(0, 10);
	cout << "     ___        ___           ___           ___           ___           ___" << endl
		<< "    /  /\\      /  /\\         /  /\\         /__/\\         /  /\\         /__/\\" << endl
		<< "   /  /::\\    /  /::\\       /  /:/        |  |::\\       /  /::\\        \\  \\:\\" << endl
		<< "  /  /:/\\:\\  /  /:/\\:\\     /  /:/         |  |:|:\\     /  /:/\\:\\        \\  \\:\\" << endl
		<< " /  /:/~/:/ /  /:/~/::\\   /  /:/  ___   __|__|:|\\:\\   /  /:/~/::\\   _____\\__\\:\\" << endl
		<< "/__/:/ /:/ /__/:/ /:/\\:\\ /__/:/  /  /\\ /__/::::| \\:\\ /__/:/ /:/\\:\\ /__/::::::::\\" << endl
		<< "\\  \\:\\/:/  \\  \\:\\/:/__\\/ \\  \\:\\ /  /:/ \\  \\:\\~~\\__\\/ \\  \\:\/:/__\\/  \\  \\:\\~~\\~~\\/" << endl
		<< " \\  \\::/    \\  \\::/       \\  \\:\\  /:/   \\  \\:\\        \\  \\::/       \\  \\:\\ ~~~		" << endl
		<< "  \\  \\:\\     \\  \\:\\        \\  \\:\\/:/     \\  \\:\\        \\  \\:\\        \\  \\:\\" << endl
		<< "   \\  \\:\\     \\  \\:\\        \\  \\::/       \\  \\:\\        \\  \\:\\        \\  \\:\\" << endl
		<< "    \\__\\/      \\__\\/         \\__\\/         \\__\\/         \\__\\/         \\__\\/ ";

	Sleep(2500);
	system("cls");
}
