#include "stdafx.h"
#include "Player.h"
#include "PatientGame.h"
#include "LevelCell.h"
#include "Level.h"


Player::Player(PatientGame* game, VectorXY startCoordinates)
	: Character(game, startCoordinates, game->getPlayerSpriteEast())
{
	resetPosition();
}

void Player::resetPosition()
{
	currentCell = game->level.getCell(Level::PLAYER_START);
	centre = currentCell->getCentre();
}

void Player::move(Directions::Direction direction)
{
	
	movementCount++;
	if (movementCount >= movementDelay)
	{

		// Put collision detection here

		if (currentCell->getEdge(direction)->isWall())
		{
			return;
		}
		currentCell = game->level.getCell(currentCell->getCoordinates() + Directions::getDirectionVector(direction));
		centre = currentCell->getCentre();
		
		movementCount = 0;

	}
	changeSpriteDirection(direction);
	//centre += Directions::getDirectionVector(direction) * speed;
}
//Credit to Harriet for Trial and erroring me Through this piece of work
void Player::update()
{
	if (currentCell->hasDoor())
	{
		currentCell->OpenDoor();
	}
}


void Player::changeSpriteDirection(Directions::Direction movementDirection)
{
	switch (movementDirection)
	{
	case Directions::Direction::NORTH:
		updateSprite(game->getPlayerSpriteNorth());
		break;
	case Directions::Direction::EAST:
		updateSprite(game->getPlayerSpriteEast());
		break;
	case Directions::Direction::SOUTH:
		updateSprite(game->getPlayerSpriteSouth());
		break;
	case Directions::Direction::WEST:
		updateSprite(game->getPlayerSpriteWest());
		break;
	}
}