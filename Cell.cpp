#include "Cell.h"


cellcontent Cell::getMyContent()
{
	return this->myContent;
}

void Cell::setMyContent(cellcontent cont)
{
	this->myContent = cont;
}

void Cell::setMyCoord(size_t x, size_t y)
{
	this->myCoord.setCoord(x, y);
}

const size_t* Cell::getMyCoord()
{
	return this->myCoord.getCoord();
}