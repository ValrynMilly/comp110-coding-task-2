#include "stdafx.h"
#include "Character.h"
#include "PatientGame.h"
#include "LevelCell.h"

Character::Character(PatientGame* game, VectorXY startCoordinates, Texture* sprite)
	: GameObject(game, sprite),
	startCoordinates(startCoordinates)
{
	// Calculate the window position from the grid position
	centre = startCoordinates.convertGridToWindow();
}


void Character::move(Directions::Direction direction)
{
	centre += Directions::getDirectionVector(direction) * speed;
}


void Character::update()
{

}