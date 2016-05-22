//! Class for 2 dimensional vectors.
/*!
  This is a class for representing 2 dimensional vectors.
  Its uses include grid positions, window positions and
  relative movement, along with calculations relating to
  these.
*/

#pragma once
class VectorXY
{
public:
	//! Parameterless constructor.
	/*!
	  The parameterless constructor can be
	  used if the x and y coordinates are not
	  initially known.
	*/
	VectorXY();

	//! Constructor that takes x and y coordinates.
	/*!
	  This constructor sets the x and y coordinates
	  when the vector is instantiated.
	*/
	VectorXY(int x, int y);

	//! Interger representing the x coordinate.
	/*!
	  This represents the x value of the vector.
	*/
	int x;

	//! Interger representing the y coordinate.
	/*!
	This represents the y value of the vector.
	*/
	int y;

	//! Operator overload for adding 2 VectorXY
	/*!
	  This operator overload allows two VectorXY
	  instances to be added together, as per the
	  usual rules of vector addition.
	*/
	VectorXY operator+(const VectorXY& otherVector);

	//! Operator overload for subtracting 2 VectorXY
	/*!
	  This operator overload allows two VectorXY
 	  instances to be subtracted as per the
      usual rules of vector subtraction.
	*/
	VectorXY operator-(const VectorXY& otherVector);

	//! Operator overload for multiplying by a scalar.
	/*!
	  This operator overload allows a VectorXY to be
	  multiplied by an integer scalar.
	*/
	VectorXY operator*(const int& scalar);

	//! Operator overload for dividing by a scalar.
	/*!
	  This operator overload allows a VectorXY to be
	  divided by an integer scalar.
	*/
	VectorXY operator/(const int& scalar);

	VectorXY& operator+=(const VectorXY& otherVector);

	//! Operator overload for equality comparison.
	/*!
	  This is the operator overload for equality comparison.
	  It returns true if the x and y coordinates of the
	  two vectors are the same.
	*/
	bool operator==(const VectorXY& otherVector);

	//! Convert grid coordinates to window coordinates.
	/*!
	  This method converts grid coordinates (this) into
	  window coordinates, using the size of the level cells, 
	  and returns it as a VectorXY.
	*/
	VectorXY convertGridToWindow();

	//! Convert window coordinates to grid coordinates.
	/*!
	This method converts window coordinates (this) into
	grid coordinates, using the size of the level cells,
	and returns it as a VectorXY.
	*/
	VectorXY convertWindowToGrid();
};

