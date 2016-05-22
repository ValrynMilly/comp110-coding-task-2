//! Class for all game objects.
/*!
  This is a class that all game objects should inherit
  from. That is, any objects in the game that will be rendered
  to the screen.
*/

#pragma once
#include "Texture.h"
#include "VectorXY.h"

class PatientGame;

class GameObject
{
public:
	//! Constructor for the class.
	/*!
	  Constructor for the game objects. It initialises
	  the pointer to the main game and the pointer to the
	  texture.
	  It also gets the size of the sprite.
	*/
	GameObject(PatientGame* game, Texture* sprite);

	//! Destructor for the class.
	/*!
	  Things
	*/
	~GameObject();

	//! Renders the game object.
	/*!
	  This function renders the game object to the screen.
	*/
	void render(SDL_Renderer* renderer);

	VectorXY getCentre() { return centre; }

	VectorXY getSpriteSize() { return objectSprite->getSpriteSize(); }



protected:
	//! Pointer to the game.
	/*!
	  This member is a pointer to the main game instance.
	  It is protected so that classes that inherit from GameObject
	  can access it.
	*/
	PatientGame* game;

	//! Stores the position of the game object.
	/*!
	This variable stores the position that the game object
	will be rendered on screen.
	*/
	//int centreX, centreY;

	VectorXY centre;

	void GameObject::updateSprite(Texture* sprite);

private:
	//! Pointer to the texture.
	/*!
	  This member stores a pointer to the game object's texture.
	  It is initialised in the constructor.
	*/
	Texture* objectSprite;
};

