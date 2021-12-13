#pragma once
#include "Board.h"



class Game
{
	bool colored;
	char choice=0;
	bool win=false;
	short score=0;
	short fruitscore = 0;
	bool pause;
	Board br;

	void pacmanMoves_Dispatcher(Direction& next_dic, Direction& cur_dic, Direction& last_dic);
	void NPCMoves_Dispatcher();

public:
	static int moves_made_this_level;
	//-----------------UI (settings)----------------
	void setDif();
	void Color() {
		system("cls");
		short cho;
		setTextColor(Color::WHITE);
		cout << "for color mode enter 1, for B&W enter anything else : ";
		cin >> cho;
		cho == 1 ? colored = true : colored = false;
	}
	void printMenu();
	void setChoice();
	void printInstructions();
	//-----------------UI (announcements)----------------
	void Loser();
	void Winner();
	//-----------game-engine-------------------
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
	void play();
	void Engine();
	void level_progress();
	void NewRound();
	void ResetGame();
	void pauseGAME();
	void updateDics(Direction& cur);

	//-------------utilities------------

	void load_specific_Map();
	string getMapName() {
		string name;
		cin >> name;
		return name;
	}
	void printlegend(Point pt, short hp);
	bool Over()//indicator to end game loop
	{
		if (br.get_pac().getHP() == 0)
		{
			win = false;
			return true;
		}
		if (score == br.getCrumbs())
		{
			win = true;
			return true;
		}
		else
			return false;
	}
	void printScore(Point);
};

