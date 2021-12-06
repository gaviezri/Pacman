#pragma once
#include "primary_creatures.h"
#include <vector>
#include "behavior.h"

 enum class Difficulty {
 
	NOVICE = 0, GOOD = 1, BEST = 2
};




class Ghost:public primary_creatures {

	Direction cur_move = Direction::UP;
	static Difficulty diffic;
	//behaviour _behaviour;

	//friend class Game;
public:
	Direction getcurDic() { return cur_move; }
	Direction setcurDic(Direction dic) { cur_move = dic; return cur_move; }
	static void setDif(int );
	static Difficulty getDif();

	Point getPos() { return pos; }
	
	Ghost(Point _pos) { pos = def_pos = _pos;avatar = 'G'; }

	void resetMe(){pos = def_pos;}

	void updateMove(Direction dic, bool colored, short cont);

};

