#include "input.h"

/***********************************************************************

getInput

Polls SDL event handler to see if any new events have happened

If there is a new event, check to see if it is the "window close" button,
if so return an SDLK_ESCAPE value. Otherwise, return the SDL key value from 
the keyboard.

*************************************************************************/


int getInput()
{
	int output = 0;
	SDL_Event event;

	/* Loop through waiting events and process them */
	while (SDL_PollEvent(&event))
	{
		switch (event.type) /* check the type of event */
		{
			/* Closing the Window (SDL_QUIT) or pressing Escape (SDL_KEYDOWN and key SDLK_ESCAPE) will return a 1 */
			case SDL_QUIT: output = SDLK_ESCAPE;
			break;
			
			case SDL_KEYDOWN:	output = event.key.keysym.sym;
			break;

			default: break;
		}
	}
	return output;
}

