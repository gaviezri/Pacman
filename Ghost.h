#pragma once

#include "Board.h"




constexpr enum  Difficulty {
	NOVICE = 0, GOOD = 1, BEST = 2
};

class Ghost {



private:
	const char avatar = 'G';
	Point cur_pos;
	Point def_pos;
	Direction first_move;
	Direction cur_move = DEF;
	static short def_moves_count;
	static Difficulty diffic;
	friend class Game;
public:
	static void setDif(int );
	static Difficulty getDif();
	const unsigned short* getPos() { return cur_pos.getCoord(); }
	
	void PrintME() { cout << avatar; }
	
	Ghost(Point _pos, Direction first) { cur_pos = def_pos = _pos; first_move=first; } // (13,7) (14,7) 
	
	void Movement(const Board& br);
	void updateMove(Direction dic, bool colored, short cont);
	void printMe(bool colored) { cout << (colored == true ? "\033[31m" : "\033[37m") << avatar; }
	void resetMe(short cont,bool colored) { gotoxy(2*cur_pos.coord[0], cur_pos.coord[1]); cout << (colored == true ? "\033[34m" : "\033[37m")<< (cont == PATH ? " " : "."); cur_pos = def_pos; def_moves_count = 0; }
};