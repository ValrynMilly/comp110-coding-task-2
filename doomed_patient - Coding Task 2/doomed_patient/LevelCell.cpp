#include "stdafx.h"
#include "LevelCell.h"
#include "PatientGame.h"
#include "Directions.h"
#include "CellWall.h"
#include "CellPassage.h"
#include "Room.h"


LevelCell::LevelCell(PatientGame* game, VectorXY coordinates)
	: GameObject(game, game->getFloorSprite()),				// Call base class constructor
	gridPosition(coordinates)
{
	// Calculate the window position from the grid position
	centre = gridPosition.convertGridToWindow();

	// Set up empty edges
	edges[Directions::Direction::NORTH] = nullptr;
	edges[Directions::Direction::EAST] = nullptr;
	edges[Directions::Direction::WEST] = nullptr;
	edges[Directions::Direction::SOUTH] = nullptr;
}


void LevelCell::render(SDL_Renderer* renderer)
{
	// Render the cell
	GameObject::render(renderer);

	// Iterate through all map elements and render each edge
	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge)
			edge->render(renderer);
	}
}


bool LevelCell::allEdgesInitialised()
{
	// Iterate through all map elements and check if edge exists
	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (!edge)
		{
			return false;
		}
	}
	return true;
}


Directions::Direction LevelCell::getRandomUninitialisedDirection()
{
	std::vector<Directions::Direction> uncheckedDirections = {Directions::Direction::NORTH, Directions::Direction::EAST, 
															  Directions::Direction::WEST, Directions::Direction::SOUTH};

	// Loop through all directions and remove after it's been checked
	while (uncheckedDirections.size() > 0)
	{
		int index = rand() % (uncheckedDirections.size());

		if (!edges[uncheckedDirections[index]])
		{
			return uncheckedDirections[index];
		}
		else
		{
			uncheckedDirections.erase(uncheckedDirections.begin() + index);
		}
	}
}


Directions::Direction LevelCell::getBiasedUninitialisedDirection(Directions::Direction direction)
{
	// Given direction is returned if it's uninitialised, otherwise random
	if (!edges[direction])
	{
		return direction;
	}
	else
	{
		return getRandomUninitialisedDirection();
	}
}


void LevelCell::assignRoom(std::shared_ptr<Room> assignedRoom)
{
	room = assignedRoom;
	std::shared_ptr<Room> cellRoom = room.lock();
	cellRoom->addCell(shared_from_this());
}


bool LevelCell::hasDoor()
{
	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge->isDoor())
		{
			return true;
		}
	}
	return false;
}

void LevelCell::OpenDoor()
{
	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge->isDoor())
		{
			edge->sprite = game->getHorizontalDoorOpenSprite();
		}
	}
}


std::shared_ptr<CellEdge> LevelCell::getRandomWall()
{
	std::vector<Directions::Direction> uncheckedDirections = { Directions::Direction::NORTH, Directions::Direction::EAST,
															   Directions::Direction::WEST, Directions::Direction::SOUTH };

	while (uncheckedDirections.size() > 0)
	{
		int index = rand() % (uncheckedDirections.size());

		if (edges[uncheckedDirections[index]]->isWall())
		{
			return edges[uncheckedDirections[index]];
		}
		else
		{
			uncheckedDirections.erase(uncheckedDirections.begin() + index);
		}
	}
}


int LevelCell::getWallCount()
{
	int wallCount = 0;

	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge->isWall())
		{
			wallCount++;
		}
	}
	return wallCount;
}

std::vector<std::shared_ptr<CellEdge>> LevelCell::getPassages()
{
	std::vector<std::shared_ptr<CellEdge>> passages;

	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge->isPassage())
		{
			passages.push_back(edge);
		}
	}

	return passages;
}


std::vector<Directions::Direction> LevelCell::getPassageDirections()
{
	std::vector<Directions::Direction> passages;

	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge->isPassage())
		{
			passages.push_back(edge->getDirection());
		}
	}

	return passages;
}