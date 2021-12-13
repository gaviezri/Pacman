#pragma once
#include "NPC.h"
class Fruit : public NPC
{
    bool appearing = false;
    short move_counter = 0;
public:
    bool isAppearing() { if (appearing)move_counter++; return appearing; }
    void setAvatar(char av) { avatar = av; }
    char getAvatar() { return avatar; }
    void Appear();
    void Disappear();
    int  myPrizeandLooks();
    bool ExposeMe();
    int Eaten();
};

