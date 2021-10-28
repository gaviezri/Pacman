#include "Cell.h"


cellcontent Cell::getMyContent()
{
	return myContent;
}

void Cell::setMyContent(cellcontent cont)
{
	myContent = cont;
}

void Cell::setMyCoord(unsigned short x, unsigned short y)
{
	myCoord.setCoord(x, y);
}

const unsigned short* Cell::getMyCoord()
{
	return myCoord.getCoord();
}