//! Class for the Creature.
/*!
This is a class for handling the Creature
and storing any unique data.
It inherits from th GameObject class
for any general data.
*/
#pragma once

#include "GameObject.h"

class Creature : public GameObject
{
public:
	//!Constructor for the Creature
	/*!
	*/
	Creature(PatientGame* game);

	//!Destuctor for the Creature
	/*!
	*/
	~Creature();
};