//! Class for the level.
/*!
  This class stores data about the level and
  initiates the level generation process - that
  includes the maze and characters.
  It also holds pointers to all characters and the
  maze.
*/

#pragma once
#include "VectorXY.h"
#include "Maze.h"

class PatientGame;
class Room;
class Exit;
class Player;
class Character;

class Level
{
public:
	//! Constructor for the level.
	/*!
	  This is the constructor for the level. 
	  It takes a pointer to the game in order to access the sprites.
	*/
	Level(PatientGame* game);

	//! Generates the level.
	/*!
	  This method begins the level generation process and
	  generates the maze and characters.
	*/
	void generateMaze();

	//! Render the level.
	/*!
		This method renders the maze, exit and characters.
	*/
	void render(SDL_Renderer* renderer);

	//! Returns the cell at the given coordinates.
	/*!
	  This method returns a pointer to the cell located
	  at the given coordinates.
	  The coordinates should be supplied as a VectorXY 
	  representing the grid coordinates.
	*/
	std::shared_ptr<LevelCell> getCell(VectorXY coordinates) { return maze->getCell(coordinates); };

	//! Returns a pointer to the player.
	/*!
	  This getter returns the shared pointer to the
	  player.
	*/
	std::shared_ptr<Player> getPlayer() { return player; }
	
	//! Returns a pointer to the exit.
	/*!
	  This getter returns the shared pointer to the
	  exit.
	*/
	std::shared_ptr<Exit> getExit() { return exit; }

	//! Vector of pointers to characters.
	/*!
	This field holds a vector of shared pointers to
	all instances of characters, which includes the
	NPCs and the player. Used for rendering etc.
	*/
	std::vector<std::shared_ptr<Character>> getCharacters()
	{
		return characters;
	}

	//! Check if the given coordinates are in the level.
	/*!
	  This method checks if the given coordinates are contained
	  in the level. If so, it returns true.
	*/
	bool containsCoordinates(VectorXY coordinates) { return maze->containsCoordinates(coordinates); }

	//! Width of the level.
	/*!
	  This static member represents the width of
	  the level in grid squares as an integer.
	*/
	static const int GRID_SIZE_X = 21;

	//! Height of the level.
	/*!
	  This static member represents the height of
	  the level in grid squares as an integer.
	*/
	static const int GRID_SIZE_Y = 12;

	//! Size of each level cell.
	/*!
	  This static member represents the size of each
	  cell of the level, which corresponds to the size of
	  the sprite. Used to convert grid coordinates to
	  window coordinates and vice versa.
	*/
	static const int CELL_SIZE = 64;

	//! Start position of the player.
	/*!
	  This static member represents the position that
	  the player starts in.
	*/
	static const VectorXY PLAYER_START;
	

private:
	//! Add the exit to the level.
	/*!
	  This method creates an instance of the exit and
	  sets its position to a random place on the top or
	  left edge.
	*/
	void placeExit();

	//! Pointer to the game
	/*!
	  This is a pointer to the game, that is used to pass
	  to the generated cells so that they can access their
	  sprite.
	*/
	PatientGame* game;

	//! Pointer to the exit.
	/*!
	  This is a shared pointer to the exit of the level.
	  The exit is created and placed
	  during the level generation process.
	*/
	std::shared_ptr<Exit> exit;

	//! Vector of pointers to characters.
	/*!
	  This field holds a vector of shared pointers to
	  all instances of characters.
	  Used for rendering etc.
	*/
	std::vector<std::shared_ptr<Character>> characters;

	//! Create a character in a random position.
	/*!
	  This template method creates a character in a 
	  random position on the grid. CharaterType can
	  be any class that inherits from Character.
	  There character created corresponds to the type
	  passed in.
	*/
	template<typename CharacterType> std::shared_ptr<CharacterType> createCharacter(VectorXY coordinates);

	//! Pointer to the player.
	/*!
	  This member is a shared pointer to the player.
	*/
	std::shared_ptr<Player> player;

	//! Returns coordinates of a random cell in the given room
	/*!
	  This method returns the coordinates of a randomly selected cell
	  that is contained in the given room.
	*/
	VectorXY getRandomCoordinatesInRoom(std::shared_ptr<Room> room);

	//! Clears all cells and characters from the level.
	/*!
	  This method clears all the cells and characters from the level.
	  It should be called before a new level is generated.
	*/
	void clearLevel();

	//! Pointer to the maze
	/*!
	  This is a pointer to the maze. The maze
	  stores data about the cells and implements the
	  generation algorithm. 
	  It is a unique pointer as only the level should have
	  direct access to the maze.
	*/
	std::unique_ptr<Maze> maze;

	//! The probability that a door will be made.
	/*!
	  This constant defines the probability that a door
	  will be made instead of a passage. This value should
	  be between 0 and 1.
	  0 means that doors will never spawn, 1  means that
	  doors will always spawn.
	*/
	const double DOOR_PROBABILITY = 0.03;

	//! Int defining how sparsely the NPCs will be placed.
	/*!
	  There will never be more than 1/NPC_SPACING of the cells in
	  a room occupied by NPCs.
	*/
	const int NPC_SPACING = 5;
};

