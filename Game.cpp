#include "Game.h"


constexpr int INVALIDARGS = 10;


int Game::moves_made_this_level=0;

void Game::PacmanLogo()
{
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

void QuickExplanation()
{
	cout << "command line arguments are invalid! - please notice:"
		<< endl << "enter: '-save' to record the current game (only last game will be saved)."
		<< endl << "enter: '-load' to play a recorded game taken from working directory. game will be shown sped up and a comparison between the steps taken and events in game will take place."
		<< endl << "enter: '-load -silent to play a recorded game and compare it without being shown (comparison will happen at lightspeed)"
		<< endl << endl << "anyway...  if you want to preform special operations please restart the game with valid (or none) arguments."
		<< endl << endl << "press any key to Continue";
	_getch();
}

void Game::initPrint() {
	br.printMap();
	printlegend(br.getlegend(), br.get_pac().getHP());
	if (!(br.get_ghosts_vec().empty())) {
		for (auto g : br.get_ghosts_vec())
			g.printMe();
	}
	br.get_pac().printMe();
}

void Game::play(int argc, char* argv[])  //  this is where the magic happens (!)
{
	string* actions = new  string[argc];
	for (int i = 1; i < argc; i++) actions[i] = argv[i];
	switch (argc)
	{
	case 1:
		RegularMode();
		break;
	case 2:
		if (actions[1] == "-load") { silent = false; LoadMode(); }

		else if (actions[1] == "-save") {
			br.setSave_mode(true);
			RegularMode();
		}
		else goto SWdefault;
	case 3:
		if (actions[1] == "-load" && actions[2] == "-silent") { silent = true; LoadMode(); }
		else goto SWdefault;

	
	default:
SWdefault:
		QuickExplanation();
		exit(INVALIDARGS);
		break;
	}
	delete[] actions;
}

void Game::RegularMode()
{
	srand(time(NULL));
	ShowConsoleCursor(false);
menu:

	system("cls");
	PacmanLogo();
	printMenu();
	setChoice();
	switch (choice)
	{
	case 1:
		if (maps_available())
		{
			Engine();
			ResetGame();
		}
		break;
	case 2:
		system("cls");
		load_specific_Map();
		br.setActive_map(0);
		break;
	case 8:
		system("cls");
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

void Game::printlegend(Point pt, short hp)
{
	gotoxy(pt.getX(), pt.getY() + 1);
	cout << "                   ";
	if (br.getLegend_flag()) {
		gotoxy(pt.getX(), pt.getY());
		cout << "####################";
		gotoxy(pt.getX(), pt.getY() + 1);
		cout << "                    ";
		gotoxy(pt.getX(), pt.getY() + 1);
		cout << "SCORE:";
		cout << score;
		cout << "   LIVES:";
		for (int i = 0; i < hp; i++) cout << "C";
		gotoxy(pt.getX(), pt.getY() + 2);
		cout << "####################";
	}
}

void Game::load_specific_Map()
{

	int i = 0;
	string name = getMapName();
	vector<string> screen_files = br.getScreen_files();
	bool found = false;
	for (; i < screen_files.size(); ++i)
	{
		if (screen_files[i].substr(2, screen_files[i].length() - 9) == name)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		br.setActive_map(i);
		br.get_ghosts_vec().clear();
		br.loadNew_map();
		if (Validmap())
		{
			setDif(); // sets the difficulty of the ghosts
			br.resetCharacters();
			level_progress();
			ResetGame();
		}
	}
	else
	{
		cout << "Map named '" << name << "' was not found.";
		Sleep(3500);
	}
}

void Game::NewRound() {         // when pac meets ghost  need to make the ghosts print the previus char in the location of collision
	cout << "\a"; // SOUND FOR COLLISON!
	br.get_pac().HitByGhost();// -1 hp

	if (br.get_pac().getHP() != 0)
	{
		printlegend(br.getlegend(), br.get_pac().getHP());   // update remaining lives on screen 
		br.get_pac().clearMe();
		br.get_pac().resetMe();
		br.get_pac().printMe();

		for (auto& G : br.get_ghosts_vec())
		{
			G.clearMe(br.getPlay_map()[G.getPos().getY()][G.getPos().getX()]);
			G.resetMe();
			G.printMe();
		}
		auto Fr = br.getFruit();
		Fr.clearMe();

		Fr.setPos(br.get_ghosts_vec()[rand() % br.get_ghosts_vec().size()].getPos());
		if (br.record_game())
		{
			if (*(br.getSteps_record().end() - 1) != ')')
				br.writePosition(Fr);
		}
		pause = true;
	}
}

void Game::setDif()
{
	char ch = -1;
	while (ch != 1 && ch != 2 && ch != 3)
	{
		system("cls");
		cout << "Select your difficulty" << endl << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "1 = \"Easy\"" << endl << "2 = \"Medium\"" << endl << "3 = \"Expert\"" << endl;
		cout << "selection: ";
		ch = _getch() - 48;
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
	cout << "#############################################" << endl << endl;
	cout << " Welcome to Gal & Omri's version of PACMAN !" << endl;
	cout << " Please select one of the following options :" << endl;
	cout << " 1) Start a new game" << endl << " 2) Choose a map" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;
	cout << "#############################################" << endl;
}

void  Game::setChoice()
{
	choice = _getch() - 48;


	while (choice != 1 && choice != 2 && choice != 8 && choice != 9)    //  makes sure that the player chose one of the given options
	{
		system("cls");
		cout << "Invalid choice!" << endl;

		cout << "Please select one of the following options." << endl;
		cout << " 1) Start a new game" << endl << " 2) Choose a map" << endl << " 8) Present instructions and keys" << endl << " 9) EXIT" << endl << endl;

		choice = _getch() - 48;
	}
}

void  Game::printInstructions()
{
	cout << "The Pacman must eat all the breadcrumbs shown on screen." << endl << "The Pacman can walk freely as long as no wall is hit" << endl << " every breadcrumb is worth one point" << endl;
	cout << "Each round the Pacman starts with 3 lifes." << endl << "The Pacman must avoid contact with the ghost at all cost! if not one life will be removed." << endl;
	cout << "The player will win the game if all breadcrumbs on board are eaten and lose if all lifes are lost." << endl;
	cout << "When one map ends a new one will be loaded and a new round will start, the score and HP will be restarted." << endl << "Every once in a while a 'fruit' will appear on screen in shape of a number (5-9) which will represent" << endl << "the number of points given if the pacman eats the fruit." << endl;
	cout << " To move UP = 'W'" << endl << " To move DOWN = 'X'" << endl << " To move LEFT = 'A'" << endl << " To move RIGHT = 'D'" << endl << "To stay in your place = S" << endl << "To exit game and go to main menu = TAB" << endl << "To Pause game = P or Esc" << endl;
	cout << endl << " Press any key for main menu" << endl;

	while (!_kbhit());  //  the player will let us know that he finished reading and ready to start again
	_getch(); //  "removes" the key used from screen	
}

inline bool isNumber(char ch) { return ch <= '9' && ch >= '0'; }

void Game::level_progress()
{
	bool toSave = br.record_game();
	system("cls");
	Direction cur_dic = Direction::DEF, next_dic = Direction::DEF, last_dic = Direction::DEF; // initialzing for the switch 
	initPrint();
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
		{
			quit = true;
			win = false;
			return;
		}
		if (br.Collision())
		{
			if (toSave)
			{//update position of events in relevant streams
				report_result_file(moves_made_this_level, br.get_pac().getPos(), result);
			}
			NewRound();
			if (br.get_pac().getHP()) goto PAUSE;
		}
		pacmanMoves_Dispatcher(next_dic, cur_dic, last_dic);
		if (br.getLegend_flag())
			printScore(br.getlegend());

		Sleep(170);
		if (br.Collision())
		{
			if (toSave)
			{//update position of events in relevant streams
				report_result_file(moves_made_this_level, br.get_pac().getPos(), result);
			}
			NewRound();
			if (br.get_pac().getHP()) goto PAUSE;
		}

		NPCMoves_Dispatcher(); 

		br.pacEatsfruit(fruitscore, score);

		++moves_made_this_level;
	} while (!Over());
	if (win)
	{
		if (toSave) {
			result += to_string(moves_made_this_level);
			result += 'W';
		}
		level_completed();
	}

	else if (!quit)
	{
		if (toSave) {
			result += to_string(moves_made_this_level);
			result += 'L';
		}
		Loser();
	}
}

void Game::Engine()
{
	short level = 0, totmaps = Board::getTotal_maps();
	br.setActive_map(level);
	br.loadNew_map();
	setDif(); // sets the difficulty of the ghosts

	while (level < totmaps && !Over() && Validmap())
	{

		br.resetCharacters();
		moves_made_this_level = 0;
		level_progress();
		level++;
		if (!quit)
		{
			br.setActive_map(level);
			br.loadNew_map();
			if (br.record_game())
			{
				saveTo_steps_file();
				br.clearSteps_record();
				result.clear();
			}
		}
	}
	if (win && !quit)Winner();
}

void Game::saveTo_steps_file()
{
	string cur_map_name = br.getCur_map_name();

	ofstream steps(cur_map_name + "steps");
	steps << br.getSteps_record();
	steps.close();

	ofstream results(cur_map_name + "result");
	results << result;
	results.close();
}

bool Game::Validmap()
{
	return (!br.getundefinedchars_flag() && br.getPacman_flag());
}

void Game::pacmanMoves_Dispatcher(Direction& next_dic, Direction& cur_dic, Direction& last_dic)
{
	br.move_in_border(next_dic, cur_dic, last_dic, score);
}

void Game::NPCMoves_Dispatcher()
{
	//ghost movement manager that makes ghost move everyother move that pacman makes and moves fruit every 3
	br.NPCmoveGenerator(moves_made_this_level, fruitscore, score);
}

void Game::printScore(Point legend)
{
	if (silent)return;
	gotoxy(legend.getX() + 6, legend.getY() + 1);//6 is a magic number represents the length of "SCORE:"
	cout << score + fruitscore;
}

void Game::ResetGame()
{
	br.resetCharacters();
	score = 0;
	fruitscore = 0;
	round_lost = false;
	quit = false;
	pause = false;
	win = false;
	choice = 0;
}

void Game::Winner()
{
	system("cls");
	gotoxy(11, 2);
	cout << "CONGRATULATIONS! You've beaten all the stages (Rewards will be sent upon request)." << endl;
	Sleep(5000);
}

void Game::Loser()
{
	system("cls");
	gotoxy(11, 5);
	cout << "Yikes! better luck next time..." << endl;
	gotoxy(17, 7);
	cout << "press any key to continue, loser...";
	_getch();
}

void Game::pauseGAME()
{
	br.getLegend_flag() ? gotoxy(br.getlegend().getX(), br.getlegend().getY() + 1) : gotoxy(0, br.getRows() + 1);
	cout << "                    ";
	br.getLegend_flag() ? gotoxy(br.getlegend().getX(), br.getlegend().getY() + 1) : gotoxy(0, br.getRows() + 1);
	cout << "hit key to continue";
	_getch();
	pause = false;

	if (br.getLegend_flag())
	{
		gotoxy(br.getlegend().getX(), br.getlegend().getY());
		printlegend(br.getlegend(), br.get_pac().getHP());
	}
	else
	{
		gotoxy(0, br.getRows() + 1);
		cout << "                   ";
	}
}

void Game::updateDics(Direction& nxt)
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

void Game::LoadMode()
{
	getStepsAndResult(); // get files to move by and to compare to
	short level = 0, totmaps = Board::getTotal_maps();
	br.setActive_map(level);
	br.loadNew_map();
	while (level < totmaps && !Over() && Validmap())
	{
			br.resetCharacters();
			moves_made_this_level = 0;
			try { LOADED_level_progress(level); }
			catch(Error& er)
			{
				system("cls");
				cout << er.msg;
				Sleep(3000);
			}
			level++;
			br.setActive_map(level);
			br.loadNew_map();
	}
	//if(win && pacman still got lives)
}

void Game::getStepsAndResult()
{
	readSteps();
	readResult();
}

void Game::readResult()
{
	string tmp_path;
	ifstream tmp_fptr;
	for (auto const& entry : filesystem::directory_iterator("."))  // goes through all files in the working directory
	{
		tmp_path = entry.path().string();
		if (tmp_path.length() > 9 && tmp_path.substr(tmp_path.find_last_of('.')) == ".result")    // checkes if path ends with ".result
		{
			tmp_fptr.open(tmp_path, std::ifstream::in);
			if (tmp_fptr) {
				std::stringstream buffer;
				buffer << tmp_fptr.rdbuf();
				results.push_back(buffer.str());
				tmp_fptr.close();
			}

		}
	}
}

void Game::readSteps()
{
	string tmp_path;
	ifstream tmp_fptr;
	for (auto const& entry : filesystem::directory_iterator("."))  // goes through all files in the working directory
	{
		tmp_path = entry.path().string();
		if (tmp_path.length() > 9 && tmp_path.substr(tmp_path.find_last_of('.')) == ".steps")    // checkes if path ends with ".steps
		{
			tmp_fptr.open(tmp_path, std::ifstream::in);
			if (tmp_fptr) {
				std::stringstream buffer;
				buffer << tmp_fptr.rdbuf();
				steps.push_back(buffer.str());
				tmp_fptr.close();
			}
		}
	}
	
}

void Game::LOADED_level_progress(short level)
{
	if (level >= steps.size() || level >= results.size()) throw Error("can't find steps or results file for map: " + br.getCur_map_name());
	system("cls");
	score = 0;
	if (!silent) initPrint(); //prints everyone 
	std::string::iterator stepscursor = steps[level].begin(), resultscursor = results[level].begin();
	br.getFruit().setPos(extractPointFromStr(stepscursor, steps[level].end()));//sets fruit initial starting point.
	do
	{
	START:
		if (br.Collision())
		{
			if (ValidityCheckCollision(resultscursor, level, results[level].end()))// comapre to result//if results doesnt match terminate program with a message to the user
			{
				if (LOADED_NewRound(level, stepscursor, steps[level].end()))// reset everyone and -1 hp to pac
					goto START;
			}
		}
		LOADED_pacmanMoves_Dispatcher(stepscursor, steps[level].end());
		printScore(br.getlegend());
		if (br.Collision())
		{
			if (ValidityCheckCollision(resultscursor, level, results[level].end()))// comapre to result//if results doesnt match terminate program with a message to the user
			{
				if (LOADED_NewRound(level, stepscursor, steps[level].end()))
					goto START;
			}
		}
		if (!silent) Sleep(40);
		br.moveNPC(stepscursor, silent, steps[level].end()); // fruit appear and dissappear
		br.pacEatsfruit(fruitscore, score);// if they share a position and fruit is appearing bon appetit
		++moves_made_this_level;

	} while (!Over() && stepscursor != steps[level].end());
	if (stepscursor == steps[level].end())ValidityCheckEndGame(resultscursor, level, results[level].end());
	else throw Error("incoherency between steps and results files.");
	system("cls");
	switch (*resultscursor)
	{
	case 'W':
		if (win) { cout << "TEST SUCCEEDED!" << " level: " << level + 1; Sleep(3000); }
		else throw Error("incoherency between results and steps files.");
		break;
	case 'L':
		if (!win) { cout << "TEST SUCCEEDED!" << " level: " << level + 1; Sleep(3000); }
		else throw Error("incoherency between results and steps files.");
		break;
	}
}

bool Game::LOADED_NewRound(short level,std::string::iterator& currentsteps, std::string::iterator end)
{
	if (currentsteps == end) return false;
	if(!silent) cout << "\a"; // SOUND FOR COLLISON!
	br.get_pac().HitByGhost();// -1 hp

	if (br.get_pac().getHP() == 0) win = false;
	
		if (!silent) {
			printlegend(br.getlegend(), br.get_pac().getHP());   // update remaining lives on screen 
			br.get_pac().clearMe();
		}
		br.get_pac().resetMe();
		if (!silent) br.get_pac().printMe();

		for (auto& G : br.get_ghosts_vec())
		{
			if (!silent)G.clearMe(br.getPlay_map()[G.getPos().getY()][G.getPos().getX()]);
			G.resetMe();
			if (!silent)G.printMe();
		}
		auto Fr = br.getFruit();
		Fr.setCont_under(br.getPlay_map()[Fr.getPos().getY()][Fr.getPos().getX()]);
		if (!silent)Fr.clearMe(br.getPlay_map()[Fr.getPos().getY()][Fr.getPos().getX()]);
		Fr.Dissappear();
		if (*currentsteps == '(') {
			Fr.setPos(extractPointFromStr(currentsteps, end));
		}
		return br.get_pac().getHP() != 0;
}

int stated_point_of_time(std::string::iterator& res)
{
	string tmp;
	while (isNumber(*res)) {tmp.push_back(*(res++));}
	return std::stoi(tmp);
}

bool Game::ValidityCheckCollision(std::string::iterator& res, short level, std::string::iterator end)
{//correctness check during collision
	if (moves_made_this_level != stated_point_of_time(res) || *(res++) != 'C')
			throw Error("incoherency between steps & results");
	if (br.get_pac().getPos() != extractPointFromStr(res,end))
		   throw Error("incoherency between steps & results");
	return (end != res);
}

void Game::ValidityCheckEndGame(std::string::iterator& res, short level,std::string::iterator end)
{
	if (res == end) return;
	if (moves_made_this_level != stated_point_of_time(res))
		throw Error("incoherency between steps & results");
}

void Game::level_completed()
{
	system("cls");
	score = 0;
	cout << "level Completed! good job.";
	Sleep(3000);
}

void Game::LOADED_pacmanMoves_Dispatcher(std::string::iterator& stepscursor, const std::string::iterator& end)
{	
	if (stepscursor == end) return;
	Direction dic = charToDic(*(stepscursor++));
	if (br.portals(dic, Direction::DEF, const_cast<Point&>(br.get_pac().getPos()), score))
	{
		if (!silent) br.get_pac().printMe();
	}
	else 
		br.movePac(dic, score, silent);
}

void Game::report_result_file(const int& time, const Point& creature, string& res)
{
	string creature_X = to_string(creature.getX()), creature_Y = to_string(creature.getY());

	result += to_string(time);
	result += 'C';
	result_template(creature_X, creature_Y, res);
}
