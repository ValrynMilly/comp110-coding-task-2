//! Abstract class for the cells edges.
/*!
  This is an abstract class to represent the edges of the
  cells. Different edge types, such as passages and walls 
  should inherit from this class.
*/

#pragma once
#include "Directions.h"
#include "Texture.h"

class LevelCell;
class PatientGame;

class CellEdge
{
public:

	Texture* sprite;
	//! Constructor for the CellEdges.
	/*!
	  This is the constructor for the cell edges. It initialises the 
	  edge's direction and sets up the weak pointer to its containing
	  cell.
	*/
	CellEdge(Directions::Direction direction, std::shared_ptr<LevelCell> cell);

	//! Render the edge.
	/*!
	  This method renders the edge if it has a sprite.
	*/
	void render(SDL_Renderer* renderer);

	//! Return the direction of the side of the cell the edge is on.
	/*!
	  This method returns the direction of the side of the cell that
	  the edge is on.
	*/
	Directions::Direction getDirection() { return direction; }

	//! Pure virtual method for indicating if edge is wall.
	/*!
	  This pure virtual method should be implemented in the subclasses.
	  It should return a bool that indicates whether the edge is a wall.
	*/
	virtual bool isWall() = 0;

	//! Pure virtual method for indicating if edge is door.
	/*!
	This pure virtual method should be implemented in the subclasses.
	It should return a bool that indicates whether the edge is a door.
	*/
	virtual bool isDoor() = 0;

	virtual bool isPassage() = 0;

protected:
	//! Direction the egde is on.
	/*!
	  This field represents the side of the cell that
	  the edge is on.
	*/
	Directions::Direction direction;

	//! The centre  of the edge.
	/*!
	  This is the position that the centre of the
	  edge is located at. It is used when rendering.
	*/
	VectorXY centre;

	//! Pointer to the texture.
	/*!
	This member stores a pointer to the edge's texture.
	*/
	

	//! Set the position of the edge on the window
	/*!
	This method sets the position of the edge on the window, for
	rendering purposes. It should be called after the sprite has
	been initialised, as it uses the sprite's size.
	to the edge.
	*/
	void initialisePosition();

private:
	//! Pure virtual method for initialising sprites.
	/*!
	  This pure virtual method must be implemented in the subclasses.
	  It should set the sprite to the appropriate one for that edge.
	*/
	virtual void initialiseSprite(PatientGame* game) = 0;

	//! A pointer to the cell the edge is in.
	/*!
	  This is a weak pointer to the cell that contains the
	  edge.
	*/
	std::weak_ptr<LevelCell> containingCell;
};

