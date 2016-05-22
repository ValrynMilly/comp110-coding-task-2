#include "stdafx.h"
#include "GameObject.h"
#include "PatientGame.h"
#include "InitialisationError.h"

GameObject::GameObject(PatientGame* game, Texture* sprite)
	: game(game), objectSprite(sprite)
{
}

GameObject::~GameObject()
{
}

void GameObject::render(SDL_Renderer* renderer)
{
	if (objectSprite)
	{
		// Render the game object
		objectSprite->render(renderer, centre);
	}
}

void GameObject::updateSprite(Texture* sprite)
{
	objectSprite = sprite;
}