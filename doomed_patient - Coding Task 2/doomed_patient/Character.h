//! Class for characters.
/*!
  This class is for characters. It should not be 
  instantiated directly, but characters such as the player
  and doctors should inherit from it.
*/

#pragma once
#include "GameObject.h"
#include "VectorXY.h"
#include "LevelCell.h"

class Character :
	public GameObject
{
public:
	//! Constructor for the Character.
	/*!
	  This is the constructor for the Character
	  It takes a pointer to the game, starting grid coordinates, and 
	  sprite, then calls through to the base class
	  GameObject as well as setting the centreX and centreY
	  according to the start position.
	*/
	Character(PatientGame* game, VectorXY startCoordinates, Texture* sprite);

	//! Return the starting position of the character.
	/*!
	  This getter returns the starting position of the
	  character as a VectorXY.
	*/
	VectorXY getStartCoordinates() { return startCoordinates; }

	//! Speed of the characters.
	/*!
	This field holds the speed that the character
	moves.
	*/
	int speed = 1;

	//! Moves the character.
	/*!
	This method moves the character in the specified
	direction at the character's speed.
	*/
	void move(Directions::Direction direction);

	virtual void update();


private:
	//! Starting position for the Character
	/*!
	  This is the coordinates of the cell in the grid the character
	  will start in as a VectorXY.
	*/
	VectorXY startCoordinates;


};

