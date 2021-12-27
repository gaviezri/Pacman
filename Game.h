#pragma once
#include "Board.h"



class Game
{
	Board br;

	
	char choice=0;
	bool win=false;
	bool round_lost = false;
	bool quit = false;
	bool pause;
	bool silent;

	vector<string> results, steps;

	unsigned short score=0;
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
			cout << "EROR 9345: Please make sure you have a valid map in your working directory before entring!";
			Sleep(3000);
			system("cls");
			return false;
		}
		return true;
	}
	void play(int,char*[]);
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
	void LOADED_pacmanMoves_Dispatcher(Direction);
	void LOADED_NewRound(short, std::string::iterator&);
	void ValidityCheckCollision(std::string::iterator& res, short level);
	//-------------utilities------------
	void load_specific_Map();
	string getMapName() {
		cout << " enter map name(case sensitive, without extension):  ";
		string name;
		cin >> name;
		return name;
	}
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
};

