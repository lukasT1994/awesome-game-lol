/* This is a very basic tutorial. It will open a
** 640 x 480 screen and wait for the user to either close
** the window or press escape
*/

#include "main.h"


// #ifdef main
// #  undef main
// #endif


int main(int argc, char *argv[])
{
	int input = 0;
    int i, j;
    int row = 40;
    int col = 72;
    int tileSize = 20;
    int chanceToStartAlive = 30;
    int birthLimit = 4;
    int deathLimit = 1;
    int numberOfSteps = 10;
    char** level;
	
	SDL_Surface *screen;  /* screen surface */ 
	SDL_Surface *base;
    SDL_Surface *top;
    SDL_Surface *bottom;


	/* Start up SDL */
	screen = initScreen("Randomly Generated Map");

	base = loadImage("gfx/base.png");
    top = loadImage("gfx/top.png");
    bottom = loadImage("gfx/bot.png");
    
    level = createLevel(row, col, chanceToStartAlive, birthLimit, deathLimit, numberOfSteps);

	if(screen != NULL){  /* if we created a screen then wait for user to ask to exit */
		
		/* make background white */
		SDL_FillRect(screen, NULL, 0x00000000);

		/* Loop indefinitely for messages */
		while (input != SDLK_ESCAPE)
		{
			/* get input from user */
			input = getInput();

			/* put loaded image on screen at x, y coords */
            for(i=0;i<row;i++)
            {
                for(j=0;j<col;j++)
                {
                    if(level[i][j] == '0') drawImage(screen, base, (j*tileSize), (i*tileSize), 1, 1);
                    if(level[i][j] == 't') drawImage(screen, top, (j*tileSize), (i*tileSize), 1, 1);
                    if(level[i][j] == 'b') drawImage(screen, bottom, (j*tileSize), (i*tileSize), 1, 1);
                }
            }

			SDL_Flip(screen);
			
			/* Sleep briefly to stop sucking up all the CPU time */
			SDL_Delay(16);

		}
	}
    deleteLevel(level, row);
	/* Exit the program */
	SDL_Quit();
	
	return 0;
}
