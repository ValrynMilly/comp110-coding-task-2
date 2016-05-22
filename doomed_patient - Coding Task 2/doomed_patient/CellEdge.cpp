#include "stdafx.h"
#include "CellEdge.h"
#include "Directions.h"
#include "LevelCell.h"


CellEdge::CellEdge(Directions::Direction direction, std::shared_ptr<LevelCell> cell)
	: direction(direction),
	containingCell(cell)
{
}


void CellEdge::initialisePosition()
{
	// For rendering purposes so only necessary if object has a sprite
	if (sprite)
	{
		std::shared_ptr<LevelCell> cell = containingCell.lock();

		switch (direction)
		{
		case Directions::Direction::NORTH:
			centre.x = cell->getCentre().x;
			centre.y = cell->getCentre().y - (cell->getSpriteSize().y / 2 - sprite->getSpriteSize().y / 2);
			break;
		case Directions::Direction::SOUTH:
			centre.x = cell->getCentre().x;
			centre.y = cell->getCentre().y + (cell->getSpriteSize().y / 2 - sprite->getSpriteSize().y / 2);
			break;
		case Directions::Direction::EAST:
			centre.x = cell->getCentre().x + (cell->getSpriteSize().x / 2 - sprite->getSpriteSize().x / 2);
			centre.y = cell->getCentre().y;
			break;
		case Directions::Direction::WEST:
			centre.x = cell->getCentre().x - (cell->getSpriteSize().x / 2 - sprite->getSpriteSize().x / 2);
			centre.y = cell->getCentre().y;
			break;
		}
	}

}

void CellEdge::render(SDL_Renderer* renderer)
{
	if (sprite)
	{
		sprite->render(renderer, centre);
	}
}