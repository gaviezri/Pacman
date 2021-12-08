#pragma once
#include "primary_creatures.h"
#include <vector>


 enum class Difficulty {
 
	NOVICE = 0, GOOD = 1, BEST = 2
};

class Ghost:public primary_creatures {

	Direction cur_move = Direction::UP;
	static Difficulty diffic;

public:
	//-----------positioning&movement---------------------------
	Direction getcurDic() { return cur_move; }
	Direction setcurDic(Direction dic) { cur_move = dic; return cur_move; }
	//----------------behavior relative to difficulty
	static void setDif(int );
	static Difficulty getDif();
	//----------------ctor--------------------------
	Ghost(Point _pos) { pos = def_pos = _pos; avatar = 'G'; }

};

