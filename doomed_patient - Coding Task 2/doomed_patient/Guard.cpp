#include "stdafx.h"
#include "Guard.h"
#include "PatientGame.h"
#include "LevelCell.h"

Guard::Guard(PatientGame* game, VectorXY startCoordinates)
	: NPC(game, startCoordinates, game->getGuardSpriteEast())
{

}

void Guard::changeSpriteDirection()
{
	switch (movementDirection)
	{
	case Directions::Direction::NORTH:
		updateSprite(game->getGuardSpriteNorth());
		break;
	case Directions::Direction::EAST:
		updateSprite(game->getGuardSpriteEast());
		break;
	case Directions::Direction::SOUTH:
		updateSprite(game->getGuardSpriteSouth());
		break;
	case Directions::Direction::WEST:
		updateSprite(game->getGuardSpriteWest());
		break;
	}
}