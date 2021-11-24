#include "Game.h"

void PacmanLogo()
{
	gotoxy(0,10);
	cout << "     ___        ___           ___           ___           ___           ___" << endl
		<< "    /  /\\      /  /\\         /  /\\         /__/\\         /  /\\         /__/\\" << endl
		<< "   /  /::\\    /  /::\\       /  /:/        |  |::\\       /  /::\\        \\  \\:\\" << endl
		<< "  /  /:/\\:\\  /  /:/\\:\\     /  /:/         |  |:|:\\     /  /:/\\:\\        \\  \\:\\" << endl
		<< " /  /:/~/:/ /  /:/~/::\\   /  /:/  ___   __|__|:|\\:\\   /  /:/~/::\\   _____\\__\\:\\" << endl
		<< "/__/:/ /:/ /__/:/ /:/\\:\\ /__/:/  /  /\\ /__/::::| \\:\\ /__/:/ /:/\\:\\ /__/::::::::\\" << endl
		<< "\\  \\:\\/:/  \\  \\:\\/:/__\\/ \\  \\:\\ /  /:/ \\  \\:\\~~\\__\\/ \\  \\:\/:/__\\/  \\  \\:\\~~\\~~\\/" << endl
		<< " \\  \\::/    \\  \\::/       \\  \\:\\  /:/   \\  \\:\\        \\  \\::/       \\  \\:\\ ~~~		"<< endl
		<< "  \\  \\:\\     \\  \\:\\        \\  \\:\\/:/     \\  \\:\\        \\  \\:\\        \\  \\:\\" << endl
		<< "   \\  \\:\\     \\  \\:\\        \\  \\::/       \\  \\:\\        \\  \\:\\        \\  \\:\\" << endl
		<< "    \\__\\/      \\__\\/         \\__\\/         \\__\\/         \\__\\/         \\__\\/ ";

	Sleep(2500);
	system("cls");
}

void Game::NewRound() // when pac meets ghost
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

void Game::setDif()
{
	cout << "Select your difficulty" << endl << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	    	
	char ch=-1;
	while (ch != 0 && ch != 1 && ch != 2)
	{
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
	ResetGame();
	br = Board();// reset br
	system("cls");
	short color;
	cout << "for color mode enter 1, for B&W enter anything else : ";
	color = _getch() - 48;
	br.setcolor(color == 1 ? true : false);
	
	system("cls");
	cout << (br.getcolor() == true ? "\033[33m" : "\033[37m") << "#############################################" << endl << endl;
	cout << " Welcome to Gal & Omri's version of PACMAN !" << endl;
	cout << " Please select one of the following options :" << endl;
	cout << " 1) Start a new game" << endl<< " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;
	cout << "#############################################" << endl;
	setChoice();
}

void  Game::setChoice()
{
	choice = _getch() - 48;
	system("cls");

	while(choice != 1 && choice != 8 && choice != 9 )    //  makes sure that the player chose one of the given options
	{
		cout << "Invalid choice!" << endl;

		cout << "Please select one of the following options." << endl;
		cout << " 1) Start a new game" << endl  << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;

		choice = _getch()-48;
		system("cls");
	}

	switch (choice)
	{
	case 1:
		Engine();
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
	printMenu();	
}

void Game::Engine()
{
	setDif();
	pac.resetHP();
	colored = br.getcolor();
	bool everyothermove = true;
	Direction cur_dic = DEF, next_dic = DEF, last_dic = DEF; // initialzing for the switch 
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
		if (pause)	// if P / p /Esc was hit
			pauseGAME();
		if (next_dic == MENU)
			printMenu();
		if (_kbhit())
			updateDics(next_dic);// in case user ended PAUSE with the new move

		if (next_dic == STAY)// pac is now frozen on the current cell until next input is recieved
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
		if (everyothermove)//ghost movement manager that makes ghost move everyother move that pacman makes
		{
			g1.Movement(br);
			g2.Movement(br);
			everyothermove = false;// switch off
		}
		else
			everyothermove = true;// switch on


		if (Collision())//if one of the ghosts and pacman share the same cell
			NewRound();//update necessary info and reset avatars to default positions
		printScore();
	} while (!Over());
	if (win == true)
		Winner();// cout message
	else
		Loser();// kanal
}

void Game::play()  //  this is where the magic happens (!)
{	
	ShowConsoleCursor(false);
	cout << "\033[37m";// to reset color loaded on cout
	system("cls");
	PacmanLogo();
	printMenu();
}

bool Game::Collision()// ghost and pac share same cell
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
	pac.resetMe();//return to def pos 
	g1.resetMe(br.getCell(g1.getPos()[0], g1.getPos()[1]).getMyContent(), colored);// return to def pos and print back the content of the cell the ghost was on
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
	_getch();//stall the program until a key is hit
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
	if (move == '\t') nxt = MENU;
}


