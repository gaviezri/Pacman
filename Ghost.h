#pragma once
#include "NPC.h"
#include <vector>


 enum class Difficulty {
 
	NOVICE = 0, GOOD = 1, BEST = 2
};

class Ghost:public NPC {

	Direction cur_move = Direction::UP;
	static Difficulty diffic;

public:
	
	//----------------ctor--------------------------
	Ghost(Point _pos) { pos = def_pos = _pos; avatar = 'G'; }
	//----------------movement
	void updateMove(Direction dic)//ghosts
	{
		clearMe( content_underme);
		pos.updateCoord(dic);
		printMe();
	}
	static void setDif(int);
	static Difficulty getDif();
};

