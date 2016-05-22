#include "stdafx.h"
#include "Doctor.h"
#include "PatientGame.h"
#include "LevelCell.h"

Doctor::Doctor(PatientGame* game, VectorXY startCoordinates)
	:NPC(game, startCoordinates, game->getDoctorSpriteEast())
{

}

void Doctor::changeSpriteDirection()
{
	switch (movementDirection)
	{
	case Directions::Direction::NORTH:
		updateSprite(game->getDoctorSpriteNorth());
		break;
	case Directions::Direction::EAST:
		updateSprite(game->getDoctorSpriteEast());
		break;
	case Directions::Direction::SOUTH:
		updateSprite(game->getDoctorSpriteSouth());
		break;
	case Directions::Direction::WEST:
		updateSprite(game->getDoctorSpriteWest());
		break;
	}
}