#include "stdafx.h"
#include "VectorXY.h"
#include "Level.h"


VectorXY::VectorXY()
{
}

VectorXY::VectorXY(int x, int y)
	:x(x), y(y)
{
}

VectorXY VectorXY::operator+(const VectorXY& otherVector)
{
	VectorXY newVector(x + otherVector.x, y + otherVector.y);
	return newVector;
}

VectorXY VectorXY::operator-(const VectorXY& otherVector)
{
	VectorXY newVector(x - otherVector.x, y - otherVector.y);
	return newVector;
}

VectorXY VectorXY::operator*(const int& scalar)
{
	VectorXY newVector(x * scalar, y * scalar);
	return newVector;
}

VectorXY VectorXY::operator/(const int& scalar)
{
	VectorXY newVector(x / scalar, y / scalar);
	return newVector;
}

bool VectorXY::operator==(const VectorXY& otherVector)
{
	return (x == otherVector.x && y == otherVector.y);
}

VectorXY& VectorXY::operator+=(const VectorXY& otherVector)
{
	x += otherVector.x;
	y += otherVector.y;
	return *this;
}

VectorXY VectorXY::convertGridToWindow()
{
	// Grid is based on the size of the cells
	int cellSize = Level::CELL_SIZE;
	int windowX = x * cellSize + cellSize / 2;
	int windowY = y * cellSize + cellSize / 2;
	return VectorXY(windowX, windowY);
}


VectorXY VectorXY::convertWindowToGrid()
{
	// Grid is based on the size of the cells
	int cellSize = Level::CELL_SIZE;
	int gridX = (x - cellSize / 2) / cellSize;
	int gridY = (y - cellSize / 2) / cellSize;
	return VectorXY(gridX, gridY);
}