#include "init.h"

/***********************************************************************

initScreen

initialise a surface for the screen, returns a negative value on failure 

*************************************************************************/

SDL_Surface * initScreen(char *title)
{
	int test = 1; /* assume success */
	SDL_Surface *screen = NULL;

	/* Initialise SDL Video, returns a negative value if it fails */
	test = SDL_Init(SDL_INIT_VIDEO);

	if (test < 0) /* if it failed, print an error message */
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
	}
	else
	{
		/* Open a 1440 x 800 screen */
		screen = SDL_SetVideoMode(1440, 800, 32, SDL_HWPALETTE|SDL_HWSURFACE);//SDL_FULLSCREEN|
		if (screen == NULL) /* if that failed, print an error message */
		{
			printf("Couldn't set screen mode to 1440 x 800: %s\n", SDL_GetError());
			test = -1;
		}
		else
		{
			/* Set the screen title */
			SDL_WM_SetCaption(title, NULL);
		}
	}

	return screen;
}


