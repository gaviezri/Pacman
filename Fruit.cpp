#include "Fruit.h"

short int Fruit::Eaten(const Point& np)
{
	appearing = false;
	move_counter = 0;
	stealPositionFromGhosts(np);
	return static_cast<int>(avatar);

}
void Fruit::Appear()
{
	appearing = true;
	setAvatar();
}
void Fruit::Disappear(const Point& np)
{
	if (move_counter == 5)
	{
		appearing = false;
		move_counter = 0;
		clearMe();
		stealPositionFromGhosts(np);
		
	}
}
bool Fruit::ExposeMe()
{
	return (rand()%12 == 1);
}