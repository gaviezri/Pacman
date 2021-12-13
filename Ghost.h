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
	//-----------positioning&movement---------------------------
	
	//----------------behavior relative to difficulty
	static void setDif(int );
	static Difficulty getDif();
	//----------------ctor--------------------------
	Ghost(Point _pos) { pos = def_pos = _pos; avatar = 'G'; }
	void updateMove(Direction dic, bool colored)//ghosts
	{
		clearMe(colored, content_underme);
		pos.updateCoord(dic);
		printMe(colored);
	}

};

