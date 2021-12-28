#pragma once
#include "NPC.h"

class Fruit : public NPC
{
    bool appearing ;
    short move_counter ;
  
public:
    Fruit() { avatar = '5'; appearing = false; move_counter = 0; }
    void stealPositionFromGhosts(const Point& p) { pos = p; }
    void step() { move_counter++; }
    bool isAppearing() { return appearing; }
    void setAvatar() { avatar = 5 + (rand() % 5)+ IntToChar;}
    void setAvatar(char ch) { avatar = ch; }
    void LOADED_Appear(char ch) { ch == '+' ? appearing = true : appearing = false;}
    void Appear();
    void updateMove(Direction dic,bool silent )
    {
        if (appearing && !silent)
            clearMe( content_underme);
        pos.updateCoord(dic);
        if (appearing && !silent)
            printMe();
    }
    void updateMove(Direction dic)
    {
        if (appearing)
            clearMe(content_underme);
        pos.updateCoord(dic);
        if (appearing)
            printMe();
    }
    void Toggle(const Point&);
    bool ExposeMe(const Point&);
    short int Eaten(const Point&);
    void Dissappear() { appearing = false; }
   void setPos(const Point& p );
};