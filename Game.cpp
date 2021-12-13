#include "Game.h"

int Game::moves_made_this_level=0;

void PacmanLogo()
{
	setTextColor(Color::LIGHTMAGENTA);
	gotoxy(0, 8);
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

	Sleep(2000);
	system("cls");
}

void Game::play()  //  this is where the magic happens (!)
{
	ShowConsoleCursor(false);
	setTextColor(Color::WHITE);
	system("cls");
	PacmanLogo();
menu:
	Color();
	system("cls");
	printMenu();
	setChoice();
	switch (choice)
	{
	case 1:
		if (br.getMapNum() < 0)
		{
			cout << "EROR 9345: Please make sure you have a valid map in your working directory before entring!";
			_getch();
			system("cls");
		}
		else
		{
			Engine();
			ResetGame();
		}
		break;
	case 2:
		system("cls");
		cout << " enter map name: " << endl;
		load_specific_Map();
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

void Game::load_specific_Map()
{
	string name = getMapName();
	vector<string> screen_files = br.getScreen_files();
	bool found = false;
	for (int i = 0; i < screen_files.size(); ++i)
	{
		if (screen_files[i].substr(2, screen_files[i].length() - 9) == name)
		{
			found = true;
			br.setMap_num(i);
			br.get_ghosts_vec().clear();
			br.loadNew_map();
			Engine();
			ResetGame();
		}
	}

	if(!found) cout << "Map named '" << name << "' was not found.";
}

void Game::printlegend(Point pt, short hp)
{
	setTextColor(Color::WHITE);
	if (br.getLegend_flag()) {

		gotoxy(pt.getX(), pt.getY() + 1);

		if (colored)
			setTextColor(Color::LIGHTBLUE);
		cout << "SCORE: ";

		if (colored)
			setTextColor(Color::LIGHTRED);
		cout << score;

		if (colored)
			setTextColor(Color::LIGHTBLUE);
		cout << "  LIVES:";

		if (colored)
			setTextColor(Color::YELLOW);
		for (int i = 0; i < hp; i++)
		{
			cout << "C";
		}
	}
}

void Game::NewRound(){         // when pac meets ghost  need to make the ghosts print the previus char in the location of collision
	cout << "\a"; // SOUND FOR COLLISON!
	br.get_pac().HitByGhost();// -1 hp
	
	if (br.get_pac().getHP() != 0)
	{
		printlegend(br.getlegend(), br.get_pac().getHP());   // update remaining lives on screen 
		br.get_pac().clearMe();
		br.get_pac().resetMe();
		br.get_pac().printMe(colored);

		for (auto G : br.get_ghosts_vec())
		{
			G.clearMe(colored, br.getPlay_map()[G.getPos().getY()][G.getPos().getX()]);
			G.resetMe();
			G.printMe(colored);
		}
		pause = true;
	}
}

void Game::setDif()
{ 	
	char ch=-1;
	while (ch != 1 && ch != 2 && ch != 3)
	{
		system("cls");
		cout << "Select your difficulty" << endl << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "1 = \"Novice\"" << endl << "2 = \"Good\"" << endl << "3 = \"Best\"" << endl;
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
	if (colored)
		setTextColor(Color::BROWN);
	else
		setTextColor(Color::WHITE);
	system("cls");
	cout << "#############################################" << endl << endl;
	cout << " Welcome to Gal & Omri's version of PACMAN !" << endl;
	cout << " Please select one of the following options :" << endl;
	cout << " 1) Start a new game" << endl << " 2) Choose a map" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;
	cout << "#############################################" << endl;
}

void  Game::setChoice()
{
	choice = _getch() - 48;
	

	while(choice != 1 && choice != 2 && choice != 8 && choice != 9 )    //  makes sure that the player chose one of the given options
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

void Game::level_progress()
{
	Direction cur_dic = Direction::DEF, next_dic = Direction::DEF, last_dic = Direction::DEF; // initialzing for the switch 
	br.printMap(colored);
	printlegend(br.getlegend(), br.get_pac().getHP());

	br.get_pac().printMe(colored);   // PRINTING

	if (!(br.get_ghosts_vec().empty())) {
		for (auto g : br.get_ghosts_vec())
			g.printMe(colored);
	}

	updateDics(cur_dic);//game is frozen until first hit1
	do
	{
		if (_kbhit())
			updateDics(next_dic);// in case user ended PAUSE with the new move
	PAUSE:
		if (pause)// if P / p /Esc was hit
			pauseGAME();
		if (_kbhit())
			updateDics(next_dic);// in case user ended PAUSE with the new move
		if (next_dic == Direction::QUIT)
			return;
	
		//if outside of board dont go in, just update move
		pacmanMoves_Dispatcher(next_dic,cur_dic,last_dic);
		
		Sleep(300);
		if (br.Collision())
		{
			NewRound();
			goto PAUSE;
		}

		ghostsMoves_Dispatcher();

		if (br.Collision())//if one of the ghosts and pacman share the same cell
		{
			NewRound();//update necessary info and reset avatars to default positions
			goto PAUSE;
		}
		if (br.getLegend_flag())
			printScore(br.getlegend());

		++moves_made_this_level;
	} while (!Over());
}

void Game::Engine()
{
	short level = 0;
	setDif(); // sets the difficulty of the ghosts
	
	// while(level<br.levels() && !Over())
	{
		br.resetCharacters();
		moves_made_this_level = 0;
		level_progress();
		level++;
	}
	if (win == true)
		Winner();// cout message
	else
		Loser();// kanal
}

void Game::pacmanMoves_Dispatcher(Direction& next_dic, Direction& cur_dic, Direction& last_dic)
{
	if (next_dic == Direction::STAY)// pac is now frozen on the current cell until next input is recieved
		cur_dic = Direction::STAY;

	else if (br.isOnBorder(br.get_pac().getPos()))  // this method works partcailly
	{
		br.get_pac().updateMove(next_dic, colored);
		last_dic = cur_dic = next_dic;// remember the new direction
		next_dic = Direction::DEF; // default the next direction
	}

	else
	{
		if (br.portals(cur_dic, (Point&)br.get_pac().getPos()))
			br.get_pac().printMe(colored);

		else if (int(Content::WALL) != br.nextCellCont(br.get_pac().getPos(), next_dic))  //advance to next direction if its not a wall
		{
			br.movePac(next_dic, colored, score);
			last_dic = cur_dic = next_dic;// remember the new direction
			next_dic = Direction::DEF; // default the next direction
		}
		else if (int(Content::WALL) != br.nextCellCont(br.get_pac().getPos(), cur_dic)) // advance in current direction if the 
		{																	       // requested next isnt possible
			br.movePac(cur_dic, colored, score);
			last_dic = cur_dic;
		}
	}
}


void Game::ghostsMoves_Dispatcher()
{
	if (everyothermove)//ghost movement manager that makes ghost move everyother move that pacman makes
	{
		br.moveGhost(colored,moves_made_this_level);
		everyothermove = false;// switch off
	}
	else
		everyothermove = true;// switch on
}

void Game::printScore(Point legend)
{
	 gotoxy(legend.getX()+7,legend.getY()+1);//6 is a magic number represents the length of "SCORE:"
	 if(colored)
		 setTextColor(Color::LIGHTRED);
	 cout  << score;
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
	gotoxy(11, 2);
	if (colored)
		setTextColor(Color::LIGHTCYAN);
	cout <<"CONGRATULATIONS! You've beaten all the stages (Rewards will be sent upon request)." << endl;
	gotoxy(16, 2);
	cout << "press any key to continue, champ...";
}

void Game::Loser()
{
	system("cls");
	gotoxy(11, 5);
	if(colored) 
		setTextColor(Color::LIGHTRED);
	cout <<  "Yikes! better luck next time..." << endl;
	gotoxy(17, 5);
	cout << "press any key to continue, loser...";
}

void Game::pauseGAME()
{
	gotoxy(br.getlegend().getX(), br.getlegend().getY()+1);
	cout << "hit key to continue";
	_getch();
	pause = false;
	gotoxy(br.getlegend().getX(), br.getlegend().getY());
	printlegend(br.getlegend(), br.get_pac().getHP());
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



