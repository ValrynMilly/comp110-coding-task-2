//! Class for the NPC's.
/*!
This is a class for handling the NPC's
and storing any unique data.
It inherits from the Character class
for any general data.
*/
#pragma once
#include "Character.h"
#include "VectorXY.h"
#include "Directions.h"
#include "LevelCell.h"
#include "Player.h"

class LevelCell;

class NPC : public Character
{

	public:
	
		//!Constructor for the Guard
		/*!
		The constructor takes a pointer to the game and its
		starting grid coordinates.
		It calls through to the constructor for the base class,
		Character, and passes its sprite in.
		*/
		NPC(PatientGame* game, VectorXY startCoordinates, Texture* sprite);
	
		//!Moves the NPC's.
		/*!
		This method moves the NPC's in the specified
		direction at the NPC's speed.
		*/
		void move(Directions::Direction direction);
	
		//!Updates the NPC's.
		/*!
		This method updates the NPC's using the specified
		functions.
		*/
		virtual void update();
	
		//!Changes the Sprite.
		/*!
		This method changes the sprite depending
		on the direction the NPC's are moving.
		*/
		virtual void changeSpriteDirection() = 0;
	
		//!Calculate the euclidean distance.
		/*!
		Calculate the euclidean distance
		between the NPC's and Player.
		*/
		double euclideanDistance();
	
		//!Calculate the euclidean distance.
		/*!
		Calculate the euclidean distance between
		the NPC's and Player and returning a Vector.
		*/
		double euclideanDistanceDirection(VectorXY cellcoords);
	
		//!Follow the Player
		/*!
		Function to allow the NPC's to calculate the shortest
		distance between the NPC anf the Player.
		Then changes the movement direction to follow
		the Player.
		*/
		void followPlayer();
	
		//!Detects the proximity of the Player.
		/*!
		If the Player is too close to the NPC
		the NPC will follow.
		*/
		void npcPlayerDetection();
	
		//!Detects the proximity of the Player as a bool.
		/*!
		Returns a true/false depending on the Player
		proximity to the NPC.
		*/
		bool closeToPlayer();
	
	protected:
	
		//!Movement direction of the NPC.
		/*!
		This will change the direction of
		esch NPC.
		*/
		Directions::Direction movementDirection;
	
		//!Stores the next direction of the NPC.
		/*!
		Stores the next direction that the NPC
		will move depending on the shortest distance.
		*/
		Directions::Direction nextDirection;
	
	private:
	
		//!Constant for collision detection
		/*!
		This method sets the didtance that the NPC needs
		to be to casue the Player to restart.
		*/
		int const COLLISION_DISTANCE = 35;

		//!Constant for detection
		/*!
		This method sets the didtance that the 
		NPC needs to be to follow the Player.
		*/
		int const DETECTION_DISTANCE = 200;

		//!The cell the NPC is currently occupying.
		/*!
		This method updates the NPCs currentCell pointer to the
		cell that the game considers the NPC to be occupying.
		*/
		std::shared_ptr<LevelCell> currentCell;
	
		//!The room that the NPC is assigned.
		/*!
		This method ensures that the NPC's will not spawn in
		a room that is too small or a room that is occupied
		by the Player.
		*/
		std::shared_ptr<Room> assignedRoom;
	
		//!Change the direction of the NPC.
		/*!
		  This method changes the direction of the NPC.
		*/
		void changeDirection();
	
		//!Check if the NPC is in a position to change direction and change if so
		/*!
		  This method ensures that the NPC has passed the centre of the cell that
		  he is currently occupying before changing direction.
		  It calls changeDirection() if the NPC is past the centre and the edge is
		  a wall.
		*/
		void updateDirection();
	
		//!Update the pointer to the cell the NPC is occupying
		/*!
		  This method updates the NPCs currentCell pointer to the
		  cell that the game considers the NPC to be occupying.
		  This method should be called before any other methods that
		  rely on cell position are called (i.e. movement/behaviour)
		*/
		void updateCurrentCell();
	
		//!Set the next direction of the NPC.
		/*!
		This method will set the next direction that the
		NPC	will move depending on the shortest distance.
		*/
		void setNextDirection();
};
