#include "stdafx.h"
#include "MazeGenerationManager.h"


VectorXY MazeGenerationManager::getNextCellCoordinates()
{
	return getCurrentCell()->getCoordinates() + Directions::getDirectionVector(nextDirection);
}

std::shared_ptr<LevelCell>  MazeGenerationManager::getCurrentCell()
{
	return activeCells[currentIndex];
}

std::shared_ptr<LevelCell>  MazeGenerationManager::getPreviousCell()
{
	if (activeCells.size() > 1)
	{
		return activeCells[currentIndex - 1];
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<Room>  MazeGenerationManager::getCurrentRoom()
{
	std::shared_ptr<Room> room = getCurrentCell()->room.lock();
	return room;
}

