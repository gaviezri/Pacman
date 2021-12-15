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
    char getAvatar() { return avatar; }
    void Appear();
    void updateMove(Direction dic, bool colored)
    {
        if (appearing)
            clearMe(colored, content_underme);
        pos.updateCoord(dic);
        if (appearing)
            printMe(colored);
    }
    void Toggle(const Point&);
    bool ExposeMe(const Point&);
    short int Eaten(const Point&);
    void Dissappear() { appearing = false; }
};

