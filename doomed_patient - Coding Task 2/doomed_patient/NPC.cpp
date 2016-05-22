#include "stdafx.h"
#include "NPC.h"
#include "PatientGame.h"
#include "LevelCell.h"

NPC::NPC(PatientGame* game, VectorXY startCoordinates, Texture * sprite)
	: Character(game, startCoordinates, sprite)
{
	int random = rand() % 4;

	// Set the NPC's movement direction to random at
	// the start of the game.
	movementDirection = static_cast<Directions::Direction>(random);

	nextDirection = movementDirection;

	updateCurrentCell();

	// Prevent the NPC from spawning in a
	// room thats too small.
	assignedRoom = currentCell->room.lock();

}

void NPC::move(Directions::Direction direction)
{
	centre += Directions::getDirectionVector(direction) * speed;
}

void NPC::update()
{
	// Makes sure NPC's grid position is up to date.
	updateCurrentCell();

	setNextDirection();

	updateDirection();

	// Updates the NPC's movement Direction.
	move(movementDirection);

	// Changes the direction the sprite is facing.
	changeSpriteDirection();

	// If the NPC distance is less than the tolerated amount
	// the Player is sent back to the begining.
	double distance = euclideanDistance();
	if (distance < COLLISION_DISTANCE)
	{
		game->player->resetPosition();
	}
}

// Change the NPC's direction to the next direction
// to follow the Player.
void NPC::changeDirection()
{
	movementDirection = nextDirection;
}

void NPC::setNextDirection()
{
	std::shared_ptr<CellEdge> currentEdge = currentCell->getEdge(movementDirection);

	// Keeping the NPC's on patrol while not close to the Player.
	if (!closeToPlayer())
	{
		while (currentEdge->isWall() || currentEdge->isDoor())
		{
			int random = rand() % 4;
			nextDirection = static_cast<Directions::Direction>(random);
			currentEdge = currentCell->getEdge(nextDirection);
		}
	}
	else
	{
		// Detect if the Player is too close.
		npcPlayerDetection();
	}
}

void NPC::updateDirection()
{
	if (nextDirection != movementDirection)
	{
		std::shared_ptr<LevelCell> nextCell = game->level.getCell(currentCell->getCoordinates() + Directions::getDirectionVector(nextDirection));
		VectorXY currentCellCentre = currentCell->getCentre();
		// Pointer because of polymorphism
		std::shared_ptr<CellEdge> currentEdge = currentCell->getEdge(nextDirection);

		if (currentEdge->isPassage())
		{
			// Check that the NPC is past the centre of its cell, relative
			// to its movement direction
			switch (movementDirection)
			{
			case Directions::Direction::NORTH:
				if (centre.y <= currentCellCentre.y)
				{
					centre.y = currentCellCentre.y;
					changeDirection();
				}
				break;

			case Directions::Direction::EAST:
				if (centre.x >= currentCellCentre.x)
				{
					centre.x = currentCellCentre.x;
					changeDirection();
				}
				break;

			case Directions::Direction::SOUTH:
				if (centre.y >= currentCellCentre.y)
				{
					centre.y = currentCellCentre.y;
					changeDirection();
				}
				break;

			case Directions::Direction::WEST:
				if (centre.x <= currentCellCentre.x)
				{
					centre.x = currentCellCentre.x;
					changeDirection();
				}
				break;
			}
		}
	}		
}

void NPC::npcPlayerDetection()
{
	if (closeToPlayer())
	{
		followPlayer();
	}
}

bool NPC::closeToPlayer()
{
	return (euclideanDistance() < DETECTION_DISTANCE);
}

void NPC::followPlayer()
{
	std::vector<Directions::Direction> clearDirections = currentCell->getPassageDirections();

	double shortest = MAXINT;
	Directions::Direction shortestDirection;

	for each (Directions::Direction clearDirection in clearDirections)
	{
		std::shared_ptr<LevelCell> adjacentCell = game->level.getCell(currentCell->getCoordinates() + Directions::getDirectionVector(clearDirection));

		if (adjacentCell)
		{
			double distance = euclideanDistanceDirection(adjacentCell->getCoordinates());

			// If first is true, other one won't be checked
			if ((distance <= shortest) || shortest == MAXINT)
			{
				shortest = distance;
				shortestDirection = clearDirection;
			}
		}
	}

	nextDirection = shortestDirection;
}

// Calculate the distance between the
// Player and NPC's.
double NPC::euclideanDistance()
{
	VectorXY playerPosition = game->player->getCentre();
	double dx = playerPosition.x - centre.x;
	double dy = playerPosition.y - centre.y;
	return sqrt(dx*dx + dy*dy);
}

// Calculate the distance between the
// Player and NPC's returning a Vector.
double NPC::euclideanDistanceDirection(VectorXY cellcoords)
{
	VectorXY playerPosition = game->player->currentCell->getCoordinates();
	double dx = playerPosition.x - cellcoords.x;
	double dy = playerPosition.y - cellcoords.y;
	return sqrt(dx*dx + dy*dy);
}

void NPC::updateCurrentCell()
{
	currentCell = game->level.getCell(centre.convertWindowToGrid());
}