#include "main.h"


// #ifdef main
// #  undef main
// #endif

typedef struct{
    int x;
    int y;
} Player;

void movePlayer(Player* player, int x, int y, int tileSize, int* xMazeOffset, int* yMazeOffset, char** level, int row, int col)
{
    int vBlocked, hBlocked;
    
    if(((player->y - y - *yMazeOffset)/tileSize > 1)&&
       ((player->y - y - *yMazeOffset)/tileSize < row-1)&&
       ((player->x - x - *xMazeOffset)/tileSize > 0)&&
       ((player->x - x - *xMazeOffset)/tileSize < col))
    {
        if((level[(player->y - y - *yMazeOffset)/tileSize][((player->x - *xMazeOffset)/tileSize)] != ' ')||
           (level[(player->y - y - *yMazeOffset)/tileSize][((player->x - *xMazeOffset + 35)/tileSize)-1] != ' ')||
           (level[(player->y - y - *yMazeOffset + 35)/tileSize][((player->x - *xMazeOffset)/tileSize)] != ' ')||
           (level[(player->y - y - *yMazeOffset + 35)/tileSize][((player->x - *xMazeOffset + 35)/tileSize)-1] != ' '))
        {
            vBlocked = 1;
        }
        else
        {
            vBlocked = 0;
        }
        
        if((level[((player->y - *yMazeOffset)/tileSize)][((player->x - x - *xMazeOffset)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset)/tileSize)][((player->x - x - *xMazeOffset + 35)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset + 35)/tileSize)-1][((player->x - x - *xMazeOffset)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset + 35)/tileSize)-1][((player->x - x - *xMazeOffset + 35)/tileSize)] != ' '))
        {
            hBlocked = 1;
        }
        else
        {
            hBlocked = 0;
        }
    } else {
        vBlocked = 1;
        hBlocked = 1;
    }
    
    if(!vBlocked)
    {
        if((player->y - y < 32*tileSize)||
           (player->y - y > 800 - (32*tileSize)))
        {
            *yMazeOffset += y;
        }
        else
        {
            player->y -= y;
        }
    }
    if(!hBlocked)
    {
        if((player->x - x < 32*tileSize)||
           (player->x - x > 1440 - (32*tileSize)))
        {
            *xMazeOffset += x;
        }
        else
        {
            player->x -= x;
        }

    }
}


int main(int argc, char *argv[])
{
	int input = 0;
    int i, j;
    int x = 0;
    int y = 0;
    int xMazeOffset;
    int yMazeOffset;
    int row = 160;
    int col = 288;
    int tileSize = 10;
    int chanceToStartAlive = 40;
    int birthLimit = 6;
    int deathLimit = 2;
    int numberOfSteps = 10;
    int xAxeRange = 0;
    int yAxeRange = 0;
    int lives = 3;
    int fuel = 140;
    char** level;
    
    TTF_Init();
    
    SDL_Color textcolor = {255,00,00};
    TTF_Font *font;
	font = TTF_OpenFont("gfx/PokemonSolid.ttf",25);
	if(font == NULL){
        printf("Cannot open font\n");
        return 0;
	}

    Player player;
    
    Uint8 *keystate;
	
	SDL_Surface *screen;  /* screen surface */ 
	SDL_Surface *base;
    SDL_Surface *top;
    SDL_Surface *topLeft;
    SDL_Surface *topRight;
    SDL_Surface *bot;
    SDL_Surface *botLeft;
    SDL_Surface *botRight;
    
    SDL_Surface *playerSprite;
    SDL_Surface *playerRight;
    SDL_Surface *playerLeft;
    SDL_Surface *playerCenter;
    
    SDL_Surface *heart;
    SDL_Surface *fuelSprite;
    
    title();

	/* Start up SDL */
	screen = initScreen("Randomly Generated Map");

	base = loadImage("gfx/base.png");
    top = loadImage("gfx/top.png");
    topLeft = loadImage("gfx/topleft.png");
    topRight = loadImage("gfx/topright.png");
    bot = loadImage("gfx/bot.png");
    botLeft = loadImage("gfx/botleft.png");
    botRight = loadImage("gfx/botright.png");
    
    playerRight = loadImage("gfx/player_right.png");
    playerLeft = loadImage("gfx/player_left.png");
    playerCenter = loadImage("gfx/player.png");
    
    heart = loadImage("gfx/heart.png");
    fuelSprite = loadImage("gfx/fuel.png");
    
    
    level = createLevel(row, col, chanceToStartAlive, birthLimit, deathLimit, numberOfSteps);
    
    player.y = 800 - (32 * tileSize);
    player.x = 40 * tileSize;
    
    yMazeOffset = - (row*tileSize - 800);
    xMazeOffset = 0;

	if(screen != NULL){  /* if we created a screen then wait for user to ask to exit */
		
		/* make background white */
		SDL_FillRect(screen, NULL, 0x00000000);
        
        SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
        

		/* Loop indefinitely for messages */
		while (input != SDLK_ESCAPE)
		{
			/* get input from user */
			input = getInput();
            
            keystate = SDL_GetKeyState(NULL);
            
            x = 0;
            y = 0;
            
            if ( keystate[SDLK_RIGHT] ) x-=5;
            if ( keystate[SDLK_LEFT] ) x+=5;
            if ( keystate[SDLK_UP] ){
                if(fuel>0){
                    y+=15;
                    fuel--;
                    x *= 1.2;
                }
            } else {
                if(fuel<140) fuel++;
            }
            
            y-=10;
            
            if(x<0){
                playerSprite = playerRight;
                xAxeRange = 45;
                yAxeRange = 0;
            } else if(x>0) {
                playerSprite = playerLeft;
                xAxeRange = -35;
                yAxeRange = 0;
            } else {
                playerSprite = playerCenter;
                xAxeRange = 0;
                yAxeRange = 0;
            }
            if ( keystate[SDLK_DOWN] ){
                yAxeRange = 45;
                xAxeRange = 0;
            }
            
            if ( keystate[SDLK_z] ){
                x = 0;
                y = 0;
                for(i=0;i<4;i++)
                {
                    for(j=0;j<4;j++)
                    {
                        if( ((((player.y-yMazeOffset+yAxeRange)/tileSize)+i)>0)&&
                            ((((player.y-yMazeOffset+yAxeRange)/tileSize)+i)<row-1)&&
                            ((((player.x-xMazeOffset+xAxeRange)/tileSize)+j)>0)&&
                            ((((player.x-xMazeOffset+xAxeRange)/tileSize)+j)<col))
                        {
                            level[((player.y-yMazeOffset+yAxeRange)/tileSize)+i][((player.x-xMazeOffset+xAxeRange)/tileSize)+j] = ' ';
                        }
                    }
                }
            }
            
            movePlayer(&player, x, y, tileSize, &xMazeOffset, &yMazeOffset, level, row, col);
            
            SDL_FillRect(screen, NULL, 0x00000000);

			/* put loaded image on screen at x, y coords */
            for(i=0;i<row;i++)
            {
                for(j=0;j<col;j++)
                {
                    if(level[i][j] == '0') drawImage(screen, base, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                    if(level[i][j] == 't') drawImage(screen, top, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                    if(level[i][j] == '1') drawImage(screen, topLeft, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                    if(level[i][j] == '2') drawImage(screen, topRight, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                    if(level[i][j] == 'b') drawImage(screen, bot, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                    if(level[i][j] == '3') drawImage(screen, botLeft, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                    if(level[i][j] == '4') drawImage(screen, botRight, (j*tileSize)+xMazeOffset, yMazeOffset+(i*tileSize), 1, 1);
                }
            }
            
//            printf("%d %d", player.x, player.y);
            drawImage(screen, playerSprite, player.x, player.y, 1, 1);
            
            for(i=0; i<lives; i++)
            {
                drawImage(screen, heart, 30 + 50*i, 30, 1, 1);
            }
            
            for(i=0; i<fuel; i++)
            {
                drawImage(screen, fuelSprite, 30 + i, 80, 1, 1);
            }

			SDL_Flip(screen);
			
			/* Sleep briefly to stop sucking up all the CPU time */
			SDL_Delay(3);

		}
	}
    deleteLevel(level, row);
	/* Exit the program */
	SDL_Quit();
	
	return 0;
}
