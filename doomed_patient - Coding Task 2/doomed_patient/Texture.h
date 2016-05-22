//! Class for managing textures.
/*! 
  This class contains methods for loading and 
  rendering textures.
*/
#pragma once
#include "VectorXY.h"

class Texture
{
public:
	//! Constructor for the texture.
	/*!
	  This is the constructor for textures. It initialises
	  fileName to the given path and the texture to a null
	  pointer.
	*/
	Texture(const std::string& fileName);

	//! Destructor for the texture.
	/*!
	  This is the destructor for textures. It destroys the 
	  SDL texture if one exists.
	*/
	~Texture();

	//! Getter for the texture.
	/*!
	  This is a getter for the SDL texture, which is null until 
	  render is called.
	  The texture will be created from the sprite at the given path.
	*/
	SDL_Texture* getTexture() { return texture; }

	//! Returns the filename as a string.
	/*!
	  This getter returns the image file name as a string.
	*/
	std::string getImageFileName() { return imageFilename; }

	//! Render the texture.
	/*!
	  This method copies the texture to the renderer.
	*/
	void render(SDL_Renderer* renderer, VectorXY position);

	//! Return the size of the sprite.
	/*!
	  This getter returns the size of the sprite in pixels as a VectorXY.
	*/
	VectorXY getSpriteSize() { return spriteSize; }


private:
	//! Load the texture.
	/*!
	  This private method is called when render is called, and loads the
	  image into an SDL texture.
	*/
	void loadTexture(SDL_Renderer* renderer);

	//! Private variable to store file path.
	/*!
	  This variable stores the path to the file as a string.
	  It is defined in the constructor.
	*/
	std::string imageFilename;

	//! Private pointer to SDL texture.
	/*!
	  This is a pointer to the SDL texture. The texture is null
	  until render is called.
	  The texture will be created from the sprite at the given path.
	*/
	SDL_Texture* texture;

	//! The size of the sprite.
	/*!
	  This is the size of the sprite in pixels, as a VectorXY. 
	  It is set in the constructor.
	*/
	VectorXY spriteSize;
};
