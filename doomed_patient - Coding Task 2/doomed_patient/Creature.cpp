#include "stdafx.h"
#include "Creature.h"
#include "PatientGame.h"

Creature::Creature(PatientGame* game)
//!This is to get the texture for the Guard
/*!It inherits this from PatientGame.cpp
which then inherits from textures.h
*/
	: GameObject(game, game->getCreatureSprite())
{
}


Creature::~Creature()
{
}
