#pragma once
#include "Board.h"
#include "Board_2.0.h"  // might rise errors (infinite mutual includings.

constexpr enum  Difficulty {
	NOVICE = 0, GOOD = 1, BEST = 2
};

class Ghost {
private:
	Point cur_pos;
	Point def_pos;

	Direction first_move;
	static short def_moves_count;

	Direction cur_move = DEF;
	static Difficulty diffic;
	friend class Game;
public:
	static void setDif(int );
	static Difficulty getDif();

	Point getPos() { return cur_pos; }
	
	
	Ghost(Point _pos, Direction first) { cur_pos = def_pos = _pos; first_move=first; }

	void resetMe(short cont, bool colored)
	{
		gotoxy(2 * cur_pos.coord[0], cur_pos.coord[1]);
		cout << (colored == true ? "\033[34m" : "\033[37m") << (cont == PATH ? " " : ".");
		cur_pos = def_pos;
		def_moves_count = 0;
	}

	void Movement(const _Board& br);

	void updateMove(Direction dic, bool colored, short cont);

};