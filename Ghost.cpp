#include "Ghost.h"

void Ghost::Movement(Cell dest,Cell loc)
{
	const unsigned short int* currpos;
	currpos = loc.getMyCoord();
	cur_pos = Point()

}
void Ghost::Reset()
{
	cur_pos = def_pos;
}
