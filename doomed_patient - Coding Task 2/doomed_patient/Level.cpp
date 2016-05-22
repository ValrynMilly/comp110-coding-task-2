#include "stdafx.h"
#include "Level.h"
#include "Character.h"
#include "Exit.h"
#include "Guard.h"
#include "Doctor.h"

// Start in bottom left corner
const VectorXY Level::PLAYER_START(0, Level::GRID_SIZE_Y - 1);

Level::Level(PatientGame* game)	
	:game(game)
{
}


template<typename CharacterType>
std::shared_ptr<CharacterType> Level::createCharacter(VectorXY startCoordinates)
{
	std::shared_ptr<CharacterType> character = std::make_shared<CharacterType>(game, startCoordinates);
	characters.push_back(character);
	return character;
}


void Level::placeExit()
{
	// Get random 0 or 1. Edge is on right if not on top
	bool exitOnTopEdge = rand() % 2;

	VectorXY exitCoords;
    
	if (exitOnTopEdge)
	{
		exitCoords.x = rand() % GRID_SIZE_X;
		exitCoords.y = 0;
	}
	else
	{
		exitCoords.x = GRID_SIZE_X - 1;
		exitCoords.y = rand() % GRID_SIZE_Y;
	}

	exit = std::make_shared<Exit>(game, exitCoords);
}


void Level::clearLevel()
{
	// Old maze will automatically get destoyed as level no longer points to it
	maze = std::make_unique<Maze>(game);
	characters.clear();
}


void Level::generateMaze()
{
	// Ensure level is empty
	clearLevel();
	maze->generate();
	placeExit();
	player = createCharacter<Player>(PLAYER_START);

	for (std::shared_ptr<Room> room : maze->getRooms())
	{
		room->checkContainedCells();

		// No NPCs to start in same room as player
		if (room != maze->getCell(PLAYER_START)->room.lock())
		{
			// Guards in corridors
			if (room->corridor)
			{
				// There will never be more than 1/NPC_SPACING cells of the room occupied by NPCs
				// This also means that no NPCs will spawn in rooms NPC_SPACING cells large or smaller
				for (int i = 0; i < (rand() % room->getCells().size()) / NPC_SPACING; i++)
				{
					createCharacter<Guard>(getRandomCoordinatesInRoom(room));
				}	
			}
			else
			{
				// Doctors in rooms
				for (int i = 0; i < (rand() % room->getCells().size()) / NPC_SPACING; i++)
				{
					createCharacter<Doctor>(getRandomCoordinatesInRoom(room));
				}
			}
		}	
	}
}


void Level::render(SDL_Renderer* renderer)
{
	maze->render(renderer);
	exit->render(renderer);

	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->render(renderer);
	}
}


VectorXY Level::getRandomCoordinatesInRoom(std::shared_ptr<Room> room)
{
	int randomIndex = rand() % (room->getCells().size());
	return room->getCells()[randomIndex]->getCoordinates();
}