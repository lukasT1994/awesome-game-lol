

#include "main.h"


// #ifdef main
// #  undef main
// #endif


int main(int argc, char *argv[])
{
	int input = 0;
    int i, j;
    int row = 80;
    int col = 144;
    int tileSize = 10;
    int chanceToStartAlive = 40;
    int birthLimit = 6;
    int deathLimit = 2;
    int numberOfSteps = 10;
    char** level;
	
	SDL_Surface *screen;  /* screen surface */ 
	SDL_Surface *base;
    SDL_Surface *top;
    SDL_Surface *topLeft;
    SDL_Surface *topRight;
    SDL_Surface *bot;
    SDL_Surface *botLeft;
    SDL_Surface *botRight;


	/* Start up SDL */
	screen = initScreen("Randomly Generated Map");

	base = loadImage("gfx/base.png");
    top = loadImage("gfx/top.png");
    topLeft = loadImage("gfx/topleft.png");
    topRight = loadImage("gfx/topright.png");
    bot = loadImage("gfx/bot.png");
    botLeft = loadImage("gfx/botleft.png");
    botRight = loadImage("gfx/botright.png");
    
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
                    if(level[i][j] == '1') drawImage(screen, topLeft, (j*tileSize), (i*tileSize), 1, 1);
                    if(level[i][j] == '2') drawImage(screen, topRight, (j*tileSize), (i*tileSize), 1, 1);
                    if(level[i][j] == 'b') drawImage(screen, bot, (j*tileSize), (i*tileSize), 1, 1);
                    if(level[i][j] == '3') drawImage(screen, botLeft, (j*tileSize), (i*tileSize), 1, 1);
                    if(level[i][j] == '4') drawImage(screen, botRight, (j*tileSize), (i*tileSize), 1, 1);
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
