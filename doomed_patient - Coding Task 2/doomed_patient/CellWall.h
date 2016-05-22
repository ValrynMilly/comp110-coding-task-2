#pragma once
#include "CellEdge.h"
#include "Directions.h"

class PatientGame;

class CellWall :
	public CellEdge
{
public:
	//! Constructor for the CellWall.
	/*!
	This is the constructor for the cell walls. It calls back to the
	CellEdge constructor and also sets up the sprite and its window
	position for rendering.
	*/
	CellWall(Directions::Direction direction, std::shared_ptr<LevelCell> cell, PatientGame* game);

	//! This method returns whether the edge is a wall.
	/*!
	  This method returns a bool indicating whether the edge is a wall.
	  CellWall is a wall, so should return true.
	*/
	bool isWall() { return true; }

	//! This method returns whether the edge is a door.
	/*!
	This method returns a bool indicating whether the edge is a door.
	CellWall is not a door, so should return false.
	*/
	bool isDoor() { return false; }

	bool isPassage() { return false; }

private:
	//! Initialises the sprite.
	/*!
	  This method sets the sprite to the wall sprite of
	  the appropriate orientation.
	*/
	void initialiseSprite(PatientGame* game);
};

