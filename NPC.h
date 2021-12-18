#pragma once
#include "primary_creatures.h"
class NPC :// Non-player-characters
    public primary_creatures
{
protected:
    Direction cur_move = Direction::UP;
    char content_underme;
public:
    virtual void updateMove(Direction dic) = 0; // ghosts + fruit

    void setCont_under(char ch) { content_underme = ch; }
    char getCont_under() { return content_underme; }

    Direction getcurDic() { return cur_move; }
    Direction setcurDic(Direction dic) { cur_move = dic; return cur_move; }
};

