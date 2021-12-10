#include "Fruit.h"
const int IntToChar = 48;
int Fruit::Eaten()
{
	appearing = false;
	move_counter = 0;
	return static_cast<int>(avatar);
}
void Fruit::Appear()
{
	appearing = true;
	avatar =   myPrizeandLooks() + IntToChar;
}
void Fruit::Disappear()
{
	if (move_counter == 5)
	{
		appearing = false;
		move_counter = 0;
	}
}
bool Fruit::ExposeMe()
{
	return (rand()%3 == 1);
}
int  Fruit::myPrizeandLooks()
{
	return 5 + (rand() % 5);
}