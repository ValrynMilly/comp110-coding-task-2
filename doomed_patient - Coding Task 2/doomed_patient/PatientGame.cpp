#include "stdafx.h"
#include "PatientGame.h"
#include "InitialisationError.h"
#include "Guard.h"
#include "Doctor.h"
#include "Player.h"
#include "Exit.h"

PatientGame::PatientGame()
	//Guard Texture
	: guardSpriteNorth("Sprites\\Guard_North.png"),
	guardSpriteEast("Sprites\\Guard_East.png"),
	guardSpriteSouth("Sprites\\Guard_South.png"),
	guardSpriteWest("Sprites\\Guard_West.png"),
	//Doctor Texture
	doctorSpriteNorth("Sprites\\Doctor_North.png"),
	doctorSpriteEast("Sprites\\Doctor_East.png"),
	doctorSpriteSouth("Sprites\\Doctor_South.png"),
	doctorSpriteWest("Sprites\\Doctor_West.png"),
	creatureSprite("Sprites\\Creature.png"),
	//Player Texture
	playerSpriteNorth("Sprites\\Player_North.png"),
	playerSpriteEast("Sprites\\Player_East.png"),
	playerSpriteSouth("Sprites\\Player_South.png"),
	playerSpriteWest("Sprites\\Player_West.png"),
	//Other Textures
	floorSprite("Sprites\\small\\floor.png"),
	verticalWallSprite("Sprites\\small\\ver_wall.png"),
	horizontalWallSprite("Sprites\\small\\horiz_wall.png"),
	verticalDoorSprite("Sprites\\small\\ver_door.png"),
	verticalDoorOpenSprite("Sprites\\small\\ver_doorOpen.png"),
	horizontalDoorSprite("Sprites\\small\\horiz_door.png"),
	horizontalDoorOpenSprite("Sprites\\small\\horiz_doorOpen.png"),
	exitSprite("Sprites\\small\\exit.png"),
	verticalLockedDoorSprite("Sprites\\small\\ver_locked.png"),
	horizontalLockedDoorSprite("Sprites\\small\\horiz_locked.png"),
	corridorSprite("Sprites\\small\\corridor.png"),
	level(this)

{

	// Initialise SDL video system
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}

	// Create window for the game
	window = SDL_CreateWindow("The Doomed Patient", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	// Check if window was successfully created
	if (window == nullptr)
	{
		throw InitialisationError("SDL_CreateWindow failed");
	}

	// Create renderer for the game
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	// Check if renderer was successfully created
	if (renderer == nullptr)
	{
		throw InitialisationError("SDL_CreateRenderer failed");
	}
}


PatientGame::~PatientGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void PatientGame::run()
{
	running = true;
	generateLevel();

	// Main game loop
	while (running)
	{
		handleEvents();
		update();
		render();
	}
}


void PatientGame::generateLevel()
{
	level.generateMaze();
	player = level.getPlayer();
	exit = level.getExit();
}


// Handle events such as quitting and player input here
void PatientGame::handleEvents()
{
	SDL_Event ev;
	if (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		// Close the game when user quits
		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
		}
	} 

	// Check keyboard state

	// Consider an update delay here to prevent fast keying in

	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	if (keyboardState[SDL_SCANCODE_UP])
		player->move(Directions::Direction::NORTH);
	if (keyboardState[SDL_SCANCODE_DOWN])
		player->move(Directions::Direction::SOUTH);
	if (keyboardState[SDL_SCANCODE_LEFT])
		player->move(Directions::Direction::WEST);
	if (keyboardState[SDL_SCANCODE_RIGHT])
		player->move(Directions::Direction::EAST);
}


// Game updates that need to happen every frame go here
void PatientGame::update()
{
	for each (std::shared_ptr<Character> npc in level.getCharacters())
	{
		npc->update();
	}
	
	// Go to next level
	if (player->getCentre() == exit->getCentre())
	{
		generateLevel();
	}
}


// Render objects and draw them to the screen here
void PatientGame::render()
{
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Render game objects here
	level.render(renderer);

	// Present the newly rendered screen
	SDL_RenderPresent(renderer);
}

