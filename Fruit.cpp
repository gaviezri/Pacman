#include "Fruit.h"

short int Fruit::Eaten(const Point& np)
{
	appearing = false;
	move_counter = 0;
	setPos(np);
	return static_cast<int>(avatar);

}
void Fruit::Appear()
{
	appearing = true;
	setAvatar();
}

bool Fruit::Toggle(const Point& np)
{
	if (move_counter == 5)
	{
		appearing = false;
		move_counter = 0;
		clearMe();
		setPos(np);
		return true;
	}
	return false;
}
bool Fruit::ExposeMe(const Point& pacpos)
{
	if (pacpos == pos) return false;
	return (rand() % 12 == 1);
}
