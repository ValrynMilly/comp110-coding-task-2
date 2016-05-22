#pragma once
#include "CellEdge.h"

class CellDoor :
	public CellEdge
{
public:
	CellDoor(Directions::Direction direction, std::shared_ptr<LevelCell> cell, PatientGame* game);
	~CellDoor();

	//! This method returns whether the edge is a wall.
	/*!
	This method returns a bool indicating whether the edge is a wall.
	CellDoor is not a wall, so should return false.
	*/
	bool isWall() { return false; }

	//! This method returns whether the edge is a door.
	/*!
	This method returns a bool indicating whether the edge is a door.
	CellDoor is not a door, so should return true.
	*/
	bool isDoor() { return true; }
	bool isPassage() { return false; }
	void initialiseSprite(PatientGame* game);
};

