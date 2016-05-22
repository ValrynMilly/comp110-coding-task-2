#pragma once
#include "Directions.h"
#include "LevelCell.h"
#include "Room.h"


class MazeGenerationManager
{
public:
	//! A vector of the active cells.
	/*!
	  This is a vector of pointers to the active cells used in
	  the Growing Tree Algorithm.
	  It contains cells that have been explored but have not yet
	  been fully initialised.
	*/
	std::vector<std::shared_ptr<LevelCell>> activeCells;

	//! A pointer to the cell in nextDirection.
	/*!
	  This field contains a pointer to the cell located in
	  nextDirection relative to the current cell.
	*/
	std::shared_ptr<LevelCell> nextCell;

	//! The direction to be explored next.
	/*!
	  This field contains the direction that the algorithm is
	  going to explore next.
	*/
	Directions::Direction nextDirection;

	//! The index of the current cell in activeCells
	/*!
	  The index of the cell in activeCells currently being 
	  explored.
	  This index is used to access the current cell.
	*/
	int currentIndex;

	//! Returns the coordinates of the next cell.
	/*!
	  This method returns the coordinates of the next
	  cell to be explored, based on the direction of
	  nextDirection.
	*/
	VectorXY getNextCellCoordinates();

	//! Returns a pointer to the previous cell.
	/*!
	  This method returns a pointer to the cell that was explored
	  before the current cell.
	*/
	std::shared_ptr<LevelCell> getPreviousCell();

	//! Returns a pointer to the current cell
	/*!
	  This method returns a pointer to the cell that
	  the algorithm is currently exploring from.
	*/
	std::shared_ptr<LevelCell> getCurrentCell();

	//! Return a pointer to the current room.
	/*!
	  This method returns a pointer to the the room that the
	  current cell belongs to.
	*/
	std::shared_ptr<Room> getCurrentRoom();
};

