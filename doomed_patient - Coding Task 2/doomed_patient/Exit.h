#pragma once
#include "GameObject.h"

class LevelCell;

class Exit :
	public GameObject
{
public:
	Exit(PatientGame* game, VectorXY gridCoordinates);
	~Exit();
};

