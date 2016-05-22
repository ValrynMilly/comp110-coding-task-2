//! Class for representing compass directions.
/*!
  This class stores an enum for representing the four
  compass directions, as well as static methods for
  manipulating and getting information about the four 
  directions.
*/

#pragma once
#include "VectorXY.h"

class Directions
{
public:
	//! Enum class for the four directions.
	/*!
	  This enum class is used to represent the
	  four directions, north, south, east and west.
	*/
	enum class Direction
	{
		NORTH,
		EAST,
		SOUTH,
		WEST,
		STOP
	};

	Directions();
	~Directions();

	//! Return the vector representative of the given direction
	/*!
	  This method returns the unit vector representative of the
	  given Direction as a GridCoordinate.
	*/
	static VectorXY getDirectionVector(Direction direction);

	static Direction getDirectionFromVector(VectorXY vector);

	//! Return the opposite direction to the given direction
	/*!
	  This method returns the direction that is opposite to
	  the given direction as a Direction.
	*/
	static Direction getOpposite(Direction direction);
};

