#pragma once
#include "Board.h"




class Game
{
	Board br;
	string result;

	char choice = 0;
	bool win = false;
	bool round_lost = false;
	bool quit = false;
	bool pause;
	bool silent;

	vector<string> steps, results;

	unsigned short score = 0;
	unsigned short fruitscore = 0;

	void pacmanMoves_Dispatcher(Direction& next_dic, Direction& cur_dic, Direction& last_dic);
	void NPCMoves_Dispatcher();
public:

	//-----------------UI (settings)----------------
	void setDif();
	void printMenu();
	void setChoice();
	void printInstructions();
	//-----------------UI (announcements)----------------
	void PacmanLogo();
	void Loser();
	void Winner();
	void level_completed();
	//-----------game-engine-------------------
	static int moves_made_this_level;
	bool Validmap();
	bool maps_available() {
		if (br.getScreen_files().size() == 0)
		{
			system("cls");
			cout << "ERROR 9345: Please make sure you have a valid map in your working directory before entring!";
			Sleep(3000);
			system("cls");
			return false;
		}
		return true;
	}
	void play(int, char* []);
	void Engine();
	void level_progress();
	void NewRound();
	void ResetGame();
	void pauseGAME();
	void updateDics(Direction& cur);
	//-------------Exercise 3 ----------
	void LOADED_level_progress(short level);
	void LoadMode();
	void RegularMode(); 
	void getStepsAndResult();
	void readSteps();
	void readResult();
	void LOADED_pacmanMoves_Dispatcher(std::string::iterator&,const  std::string::iterator&);
	void result_template(const string& x, const string& y, string& result)   // creates a custom template for writing data to result file
	{
		result.push_back('(');
		result += x;
		result.push_back(',');
		result += y;
		result.push_back(')');
	}
	const string& getResult() { return result; }
	void report_result_file(const int& time, const Point& pac, string& res);
	bool LOADED_NewRound(short, std::string::iterator&, std::string::iterator);
	bool ValidityCheckCollision(std::string::iterator& res, short level, std::string::iterator);
	void ValidityCheckEndGame(std::string::iterator& res, short level, std::string::iterator);
	//-------------utilities------------
	void load_specific_Map();
	string getMapName() {
		cout << " enter map name(case sensitive, without extension):  ";
		string name;
		cin >> name;
		return name;
	}
	void initPrint();
	void printlegend(Point pt, short hp);
	bool Over()//indicator to end game loop
	{
		if (round_lost)	return true;
		if (br.get_pac().getHP() == 0)
		{
			win = false;
			round_lost = true;
			return true;
		}
		if (score == br.getCrumbs())
		{
			win = true;
			round_lost = false;
			return true;
		}
		else
			return quit;
	}
	void printScore(Point);

	void saveTo_steps_file();

};

