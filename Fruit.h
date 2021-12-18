#pragma once
#include "NPC.h"

class Fruit : public NPC
{
    bool appearing = false;
    short move_counter = 0;
  
public:
    void stealPositionFromGhosts(const Point& p) { pos = p; }
    void step() { move_counter++; }
    bool isAppearing() { return appearing; }
    void setAvatar() { avatar = 5 + (rand() % 5)+ IntToChar;}
    void Appear();
    void updateMove(Direction dic )
    {
        if (appearing)
            clearMe( content_underme);
        pos.updateCoord(dic);
        if (appearing)
            printMe();
    }
    void Toggle(const Point&);
    bool ExposeMe(const Point&);
    short int Eaten(const Point&);
    void Dissappear() { appearing = false; }
};