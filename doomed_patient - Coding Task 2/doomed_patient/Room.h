//! Class for managing rooms.
/*!
  This class manages the rooms of the level, including
  storing what type of room it is, how many doors it has, 
  and which cells are contained within it.
*/


#pragma once
#include "LevelCell.h"


class Room
{
public:
	//! Constructor for the room.
	/*!
	  The constructor for the room ensures that a pointer
	  to the game is stored in the class's game field.
	*/
	Room(PatientGame* game);

	//! Whether the room is a corridor or not.
	/*!
	  This bool indicates whether the room is a corridor 
	  or not. If it is true, the room is a corridor.
	*/
	bool corridor;

	//! Return the list of contained cells.
	/*!
	  This getter returns the vector of pointers to
	  cells contained in the room.
	*/
	std::vector<std::shared_ptr<LevelCell>> getCells() { return containedCells; }

	//! Adds the cell to the list of contained cells
	/*!
	  Thie method adds the given pointer to a cell to the
	  containedCells.
	*/
	void addCell(std::shared_ptr<LevelCell> cell);

	//! Check whether the room contains enough cells with doors
	/*!
	  This method checks whether the room contains enough cells
	  with doors, according to MIN_DOORS.
	  If it doesn't then it will add extra doors to the room,
	  provided its size is greater than MIN_DOORS.
	*/
	void checkContainedCells();


private:
	//! Add additional doors to a random cell.
	/*!
	This method replaces a random wall of a random cell
	that doesn't already contain a door with a door.
	*/
	void addExtraDoors();

	//! A vector of all cells contained in the room.
	/*!
	  This is a vector of shared pointers to all cells that
	  are contained in this room.
	*/
	std::vector<std::shared_ptr<LevelCell>> containedCells;

	//! How many doors the room has.
	/*!
	  This field keeps track of how many doors the room has.
	*/
	int doorCount;

	//! List of cells which have walls
	/*!
	  This vector of pointers to cells contains all cells in
	  the room that have at least one wall, and no doors.
	  Used when adding extra doors to the room.
	*/
	std::vector<std::shared_ptr<LevelCell>> walledCells;

	//! Pointer to the game
	/*!
	  This is a pointer to the game, so that the room can have 
	  access to the level.
	*/
	PatientGame* game;

	//! Minimum amount of doors that a room is allowed to have
	/*!
	  This constant represents the minimum number of doors that a
	  room must have leading from/into it, provided that the
	  room is more than MIN_DOORS big.
	*/
	const int MIN_DOORS = 3;
};

