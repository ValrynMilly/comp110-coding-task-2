#include "stdafx.h"
#include "InitialisationError.h"


InitialisationError::InitialisationError(const std::string& message)
{
	// Append SDL's error message to the message passed in
	errorMessage = message + "\n" + SDL_GetError();
}

