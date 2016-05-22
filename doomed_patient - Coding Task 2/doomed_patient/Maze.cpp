#include "stdafx.h"
#include "Maze.h"
#include "LevelCell.h"
#include "PatientGame.h"
#include "MazeGenerationManager.h"


Maze::Maze(PatientGame* game)
	:cells(Level::GRID_SIZE_X, std::vector<std::shared_ptr<LevelCell>>(Level::GRID_SIZE_Y, nullptr)),		// Initialise vector to correct size
	game(game)
{
}


void Maze::generateCells(MazeGenerationManager& generationManager)
{
	// Last index. Can be changed (first, middle, or random) to give different results
	generationManager.currentIndex = generationManager.activeCells.size() - 1;

	// Delete the cell from the list of active cell if all edges have been set
	if (generationManager.getCurrentCell()->allEdgesInitialised())
	{
		generationManager.activeCells.erase(generationManager.activeCells.begin() + generationManager.currentIndex);
		return;
	}

	// Get a random direction that doesn't yet have an edge set
	generationManager.nextDirection = generationManager.getCurrentCell()->getRandomUninitialisedDirection();

	if (generationManager.activeCells.size() > 1)
	{
		// Make corridors be more likely to be straight
		if (generationManager.getCurrentRoom()->corridor)
		{
			VectorXY currentExplorationDirection = generationManager.getCurrentCell()->getCoordinates() - generationManager.getPreviousCell()->getCoordinates();
			generationManager.nextDirection = generationManager.getCurrentCell()->getBiasedUninitialisedDirection(Directions::getDirectionFromVector(currentExplorationDirection));
		}
	}
	

	if (containsCoordinates(generationManager.getNextCellCoordinates()))
	{
		generationManager.nextCell = getCell(generationManager.getNextCellCoordinates());

		// If there isn't a cell in the visted coordinates, create the cell and a passage
		if (!generationManager.nextCell)
		{
			bool isDoor = assignDoor(generationManager);

			if (generationManager.getCurrentRoom()->getCells().size() < MIN_ROOM_SIZE)
			{
				isDoor = false;
			}
			else if (generationManager.getCurrentRoom()->getCells().size() >= MAX_ROOM_SIZE)
			{
				isDoor = true;
			}

			// nextCell is in a new room if there is a door, otherwise it's in the same room
			if (isDoor)
			{
				createCellInNewRoom(generationManager);
			}
			else
			{
				createCellInSameRoom(generationManager);
			}

			// Add new cell to list of active cells
			generationManager.activeCells.push_back(generationManager.nextCell);
		}

		else if (generationManager.nextCell)
		{
			std::shared_ptr<Room> nextCellRoom = generationManager.nextCell->room.lock();

			// If a cell already exists and it's in the same room, create a passage
			if (generationManager.getCurrentRoom() == nextCellRoom)
			{
				createPassage(generationManager);
			}
			// If a cell already exists and isn't in the same room, create a wall
			else
			{
				createWall(generationManager);
			}
		}
	}

	// If the current cell is at the edge of the level, create a wall
	else
	{
		createWall(generationManager);
	}
}


bool Maze::assignDoor(MazeGenerationManager& generationManager)
{
	// Decide if the passage will be a door by picking random number between 0 and 1
	double randomNumber = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	bool isDoor = (randomNumber < DOOR_PROBABILITY) ? true : false;
	
	// If it's going into a Cell that's perpendicular to current direction, its a door
	if (generationManager.getPreviousCell())
	{
		std::shared_ptr<Room> prevCellRoom = generationManager.getPreviousCell()->room.lock();

		if (generationManager.getCurrentRoom()->corridor && prevCellRoom->corridor)
		{
			if (generationManager.getCurrentCell()->getCoordinates().x == generationManager.getPreviousCell()->getCoordinates().x)
			{
				if (generationManager.getNextCellCoordinates().x != generationManager.getCurrentCell()->getCoordinates().x)
				{
					isDoor = true;
				}
			}
			else if (generationManager.getCurrentCell()->getCoordinates().y == generationManager.getPreviousCell()->getCoordinates().y)
			{
				if (generationManager.getNextCellCoordinates().y != generationManager.getCurrentCell()->getCoordinates().y)
				{
					isDoor = true;
				}
			}
		}
	}

	return isDoor;
}


void Maze::generate()
{
	// Randomly choose position to start from and add it to activeCells
	std::vector<std::shared_ptr<LevelCell>> activeCells;
	std::shared_ptr<Room> room = createRoom();
	VectorXY firstCellCoordinates = getRandomCoordinates();
	std::shared_ptr<LevelCell> firstCell = createCell(firstCellCoordinates, room);

	MazeGenerationManager generationManager;
	generationManager.activeCells.push_back(firstCell);

	while (generationManager.activeCells.size() > 0)
	{
		generateCells(generationManager);
	}
}

void Maze::createCellInNewRoom(MazeGenerationManager& generationManager)
{
	generationManager.getCurrentCell()->initialiseEdge<CellDoor>(generationManager.nextDirection);
	generationManager.nextCell = createCell(generationManager.getNextCellCoordinates(), createRoom(generationManager.getCurrentRoom()));
	generationManager.nextCell->initialiseEdge<CellDoor>(Directions::getOpposite(generationManager.nextDirection));
}


void Maze::createCellInSameRoom(MazeGenerationManager& generationManager)
{
	generationManager.getCurrentCell()->initialiseEdge<CellPassage>(generationManager.nextDirection);
	generationManager.nextCell = createCell(generationManager.getNextCellCoordinates(), generationManager.getCurrentRoom());
	generationManager.nextCell->initialiseEdge<CellPassage>(Directions::getOpposite(generationManager.nextDirection));
}


void Maze::createWall(MazeGenerationManager& generationManager)
{
	generationManager.getCurrentCell()->initialiseEdge<CellWall>(generationManager.nextDirection);

	// Opposite cell's wall should not be created if currentCell is at the edge
	if (containsCoordinates(generationManager.getNextCellCoordinates()))
	{
		generationManager.nextCell->initialiseEdge<CellWall>(Directions::getOpposite(generationManager.nextDirection));
	}
}


void Maze::createPassage(MazeGenerationManager& generationManager)
{
	generationManager.getCurrentCell()->initialiseEdge<CellPassage>(generationManager.nextDirection);
	generationManager.nextCell->initialiseEdge<CellPassage>(Directions::getOpposite(generationManager.nextDirection));
}


std::shared_ptr<Room> Maze::createRoom(std::shared_ptr<Room> cameFrom)
{
	std::shared_ptr<Room> room = createRoom();
	if (cameFrom->corridor)
	{
		room->corridor = false;
	}
	return room;
}


std::shared_ptr<Room> Maze::createRoom()
{
	// Create a room and add a pointer to it to the vector of rooms
	std::shared_ptr<Room> room = std::make_shared<Room>(game);
	rooms.push_back(room);
	return room;
}


std::shared_ptr<LevelCell> Maze::createCell(VectorXY coordinates, std::shared_ptr<Room> room)
{
	cells[coordinates.x][coordinates.y] = std::make_shared<LevelCell>(game, coordinates);
	cells[coordinates.x][coordinates.y]->assignRoom(room);
	return cells[coordinates.x][coordinates.y];
}


std::shared_ptr<LevelCell> Maze::getCell(VectorXY coordinates)
{
	return cells[coordinates.x][coordinates.y];
}


VectorXY Maze::getRandomCoordinates()
{
	VectorXY coordinates;
	coordinates.x = rand() % Level::GRID_SIZE_X;
	coordinates.y = rand() % Level::GRID_SIZE_Y;
	return coordinates;
}


bool Maze::containsCoordinates(VectorXY coordinates)
{
	// Check if given coordinates are within the level size
	return (0 <= coordinates.x && coordinates.x < Level::GRID_SIZE_X && 0 <= coordinates.y && coordinates.y < Level::GRID_SIZE_Y);
}


void Maze::render(SDL_Renderer* renderer)
{
	for (int x = 0; x < Level::GRID_SIZE_X; x++)
	{
		for (int y = 0; y < Level::GRID_SIZE_Y; y++)
		{
			// Render each cell
			if (cells[x][y])
			{
				cells[x][y]->render(renderer);
			}
		}
	}
}
