#include "stdafx.h"
#include "Exit.h"
#include "PatientGame.h"
#include "LevelCell.h"


Exit::Exit(PatientGame* game, VectorXY gridCoordinates)
	: GameObject(game, game->getExitSprite())
{
	// Calculate the window position from the grid position
	centre = gridCoordinates.convertGridToWindow();
}


Exit::~Exit()
{
}
