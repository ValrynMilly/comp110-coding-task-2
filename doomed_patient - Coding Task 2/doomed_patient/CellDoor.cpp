#include "stdafx.h"
#include "CellDoor.h"
#include "PatientGame.h"


CellDoor::CellDoor(Directions::Direction direction, std::shared_ptr<LevelCell> cell, PatientGame* game)
	: CellEdge(direction, cell)
{
	initialiseSprite(game);
	initialisePosition();
}


CellDoor::~CellDoor()
{
}


void CellDoor::initialiseSprite(PatientGame* game)
{
	if (direction == Directions::Direction::NORTH || direction == Directions::Direction::SOUTH)
	{
			sprite = game->getHorizontalDoorSprite();
	}

	else if (direction == Directions::Direction::EAST || direction == Directions::Direction::WEST)
	{
			sprite = game->getVerticalDoorSprite();
	}
}


