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
void Fruit::Toggle(const Point& np)
{
	if (move_counter == 5)
	{
		appearing = false;
		move_counter = 0;
		clearMe();
		stealPositionFromGhosts(np);
		
	}
}
bool Fruit::ExposeMe(const Point& pacpos)
{
	if (pacpos == pos) return false;
	return (rand()%12 == 1);
}

void Fruit::setPos(const Point& p) { pos = p; }