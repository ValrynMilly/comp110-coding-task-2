//! Class for the level's cells.
/*!
  This class manages the individual cells of a level.
  Each cell is responsible for creating its edges, and
  holds pointers to its edges. The cells also store their
  position in the grid and the room they are in
*/

#pragma once
#include "GameObject.h"
#include "CellEdge.h"
#include "VectorXY.h"
#include "CellWall.h"
#include "CellPassage.h"
#include "CellDoor.h"
#include "Room.h"

class Room;

class LevelCell : public GameObject, public std::enable_shared_from_this<LevelCell>		// So that this can be passed as a shared pointer
{

public:
	//! Constructor for the level cell.
	/*!
	  This is the constructor for the level cells.
	  It takes a pointer to the game and an x and y
	  position. The constructor sets up the cell's 
	  window position based on its xy grid coordinates.
	  It also initialises the edges to nullptr.
	*/
	LevelCell(PatientGame* game, VectorXY coordinates);

	//! Render the cell.
	/*!
	This method renders the cell and all of its edges.
	*/
	void render(SDL_Renderer* renderer);

	//! Check if all edges are initialised.
	/*!
	  This method returns true if all edges have been instantiated,
	  that is, none of them are nullptr.
	*/
	bool allEdgesInitialised();

	//! Return a direction without an edge.
	/*!
	  This method returns a direction where an edge has not yet
	  been created.
	*/
	Directions::Direction getRandomUninitialisedDirection();

	//! Return a direction without an edge biased to the given direction
	/*!
	  If the supplied direction is not initialised, this method will always
	  return that direction. Otherwise, it will return a random uninitialised
	  direction.
	*/
	Directions::Direction getBiasedUninitialisedDirection(Directions::Direction direction);

	//! Return the cell's coordinates.
	/*!
	  This getter returns the cell's grid coordinates.
	*/
	VectorXY getCoordinates() { return gridPosition; }

	//! Pointer to the room the cell is in.
	/*!
	  This field holds a weak pointer to the room
	  that contains the cell.
	*/
	std::weak_ptr<Room> room;

	//! Returns a pointer to the edge in the given direction.
	/*!
	  This method returns a pointer to the cell's edge that's 
	  in the given Directions::Direction.
	*/ 
	std::shared_ptr<CellEdge> getEdge(Directions::Direction direction) { return edges[direction]; }

	//! Return whether the cell has a door
	/*!
	  This method returns true if the cell has at least
	  one door.
	*/
	bool hasDoor();


	//! Return a random wall
	/*!
	  This method returns a shared pointer to a 
	  random edge that is a wall.
	*/
	std::shared_ptr<CellEdge> getRandomWall();

	//! Return the number of walls.
	/*!
	  This method returns the number of walls
	  the cell has.
	*/
	int getWallCount();

	//! The number of sides the cell has.
	/*!
	  This constant represents how many edges the 
	  cell has.
	*/
	static const int NUMBER_OF_SIDES = 4;

	//! Assign the cell to a room.
	/*!
	  This method adds a weak pointer to LevelCell pointing to
	  the room the cell is in, as well as adding a shared pointer
	  to the room it is in that points to this LevelCell.
	  It takes its assigned room as an argument.
	*/
	void assignRoom(std::shared_ptr<Room> assignedRoom);

	void OpenDoor();

	//! Template method to initialise edges.
	/*!
	  Initialise the edge to the type supplied into the template method.
	  The type should be a subclass of CellEdge.
	  Note: Needs to be defined in header file as other classes call this function, 
	  because of behaviour of template methods.
	*/
	template<typename EdgeType> void initialiseEdge(Directions::Direction direction)
	{
		edges[direction] = std::make_shared<EdgeType>(direction, shared_from_this(), game);
	}

	std::vector<std::shared_ptr<CellEdge>> getPassages();

	std::vector<Directions::Direction> getPassageDirections();


private:
	//! Cell's position on the grid.
	/*!
	This integer represents the cell's
	coordinates on the level grid.
	*/
	VectorXY gridPosition;

	//! A map containing the cell's edges.
	/*!
	  This map stores each of the cell's four edges.
	  The keys are the direction of the edge, and the values are
	  shared pointers to CellEdge.
	  The values for the four directions are initialised to nullptr
	  in the constructor.
	*/
	std::map<Directions::Direction, std::shared_ptr<CellEdge>> edges;
};

