#include "stdafx.h"
#include "GridCoordinate.h"
#include "GameObject.h"


GridCoordinate::GridCoordinate()
{
}

GridCoordinate::GridCoordinate(int x, int y)
	: VectorXY(x, y)
{
}


GridCoordinate::~GridCoordinate()
{
}

GridCoordinate GridCoordinate::operator+(const GridCoordinate& otherCoord)
{
	GridCoordinate newCoordinates(x + otherCoord.x, y + otherCoord.y);
	return newCoordinates;
}

bool GridCoordinate::operator==(const GridCoordinate& otherCoord)
{
	return (x == otherCoord.x && y == otherCoord.y);
}

VectorXY GridCoordinate::convertToWindowPoint(std::shared_ptr<GameObject> object)
{
	int windowX = x * object->getSpriteSizeX() + object->getSpriteSizeX() / 2;
	int windowY = y * object->getSpriteSizeY() + object->getSpriteSizeY() / 2;

	return VectorXY(windowX, windowY);
}