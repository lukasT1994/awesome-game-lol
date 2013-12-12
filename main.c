#include "main.h"


// #ifdef main
// #  undef main
// #endif

typedef struct{
    int x;
    int y;
} Position;

void movePlayer(Position* player, int x, int y, int tileSize, int* xMazeOffset, int* yMazeOffset, char** level, int row, int col)
{
    int vBlocked, hBlocked;
    
    if(((player->y - y - *yMazeOffset)/tileSize > 1)&&
       ((player->y - y - *yMazeOffset)/tileSize < row-1)&&
       ((player->x - x - *xMazeOffset)/tileSize > 0)&&
       ((player->x - x - *xMazeOffset)/tileSize < col))
    {
        if((level[(player->y - y - *yMazeOffset)/tileSize][((player->x - *xMazeOffset)/tileSize)] != ' ')||//topleft
           (level[(player->y - y - *yMazeOffset)/tileSize][((player->x - *xMazeOffset + 35)/tileSize)] != ' ')||//topright
           (level[(player->y - y - *yMazeOffset + 35)/tileSize][((player->x - *xMazeOffset)/tileSize)] != ' ')||//botleft
           (level[(player->y - y - *yMazeOffset + 35)/tileSize][((player->x - *xMazeOffset + 35)/tileSize)] != ' '))//botright
        {
            vBlocked = 1;
        }
        else
        {
            vBlocked = 0;
        }
        
        if((level[((player->y - *yMazeOffset)/tileSize)][((player->x - x - *xMazeOffset)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset)/tileSize)][((player->x - x - *xMazeOffset + 35)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset + 35)/tileSize)][((player->x - x - *xMazeOffset)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset + 35)/tileSize)][((player->x - x - *xMazeOffset + 35)/tileSize)] != ' '))
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

SDL_Surface* renderMaze(int tileSize, char** level, int row, int col, SDL_Surface *base, SDL_Surface *top,SDL_Surface *topLeft,SDL_Surface *topRight,SDL_Surface *bot,SDL_Surface *botLeft,SDL_Surface *botRight)
{
    int i, j;
    
    SDL_Surface* maze;
    
    maze = SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCALPHA, col*tileSize, row*tileSize, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(level[i][j] == '0') drawImage(maze, base, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == 't') drawImage(maze, top, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '1') drawImage(maze, topLeft, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '2') drawImage(maze, topRight, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == 'b') drawImage(maze, bot, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '3') drawImage(maze, botLeft, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '4') drawImage(maze, botRight, j*tileSize, i*tileSize, 1, 1);
        }
    }   
    return maze;
}


int main(int argc, char *argv[])
{
	int input = 0;
    int i, j;
    int x = 0;
    int y = 0;
    int xMazeOffset;
    int yMazeOffset;
    int row = 80;
    int col = 144;
    int tileSize = 10;
    int chanceToStartAlive = 40;
    int birthLimit = 6;
    int deathLimit = 2;
    int numberOfSteps = 10;
    int xAxeRange = 0;
    int yAxeRange = 0;
    int lives = 3;
    int fuel = fuelMAX;
    int drillPower = drillMAX;
    int menuQuit = 0;
    int levelDisplayed = 1;
    int levelNumber = 0;
    int levelFinished = 0;
    char** level = NULL;
    
    char *name;
	int score; 
	FILE *scorestream;
	scorestream = fopen("highscores.txt","a+");
	char *readfile;
	
	fgets(readfile,5000,scorestream);
    
    
    TTF_Init();
    
    SDL_Color textcolor = {255,255,255};
    TTF_Font *font;
	font = TTF_OpenFont("gfx/MonospaceTypewriter.ttf",10);
	if(font == NULL){
        printf("Cannot open font\n");
        return 0;
	}

    Position player;
    
    Uint8 *keystate;
	
	SDL_Surface *screen;  /* screen surface */
    SDL_Surface *maze = NULL;
    
    SDL_Surface *playerSprite;
    SDL_Surface *playerRight;
    SDL_Surface *playerLeft;
    SDL_Surface *playerCenter;
    
    SDL_Surface *base;
    SDL_Surface *top;
    SDL_Surface *topLeft;
    SDL_Surface *topRight;
    SDL_Surface *bot;
    SDL_Surface *botLeft;
    SDL_Surface *botRight;
    
    SDL_Surface *heart;
    
    SDL_Surface *fuelText;
    SDL_Surface *fuelSprite;
    
    SDL_Surface *drillText;
    SDL_Surface *drillLevel;
    
    SDL_Rect digRect;
    
    digRect.x = 0;
    digRect.y = 0;
    
    digRect.w = 40;
    digRect.h = 40;
    

	/* Start up SDL */
	screen = initScreen("JetBear");
    
    menuQuit = title(screen);
    if(menuQuit)
    {
        SDL_Quit();
        return 0;
    }
    
    playerRight = loadImage("gfx/player_right.png");
    playerLeft = loadImage("gfx/player_left.png");
    playerCenter = loadImage("gfx/player.png");
    
    base = loadImage("gfx/base.png");
    top = loadImage("gfx/top.png");
    topLeft = loadImage("gfx/topleft.png");
    topRight = loadImage("gfx/topright.png");
    bot = loadImage("gfx/bot.png");
    botLeft = loadImage("gfx/botleft.png");
    botRight = loadImage("gfx/botright.png");
    
    SDL_SetAlpha(base, 0, 255);
    SDL_SetAlpha(top, 0, 255);
    SDL_SetAlpha(topLeft, 0, 255);
    SDL_SetAlpha(topRight, 0, 255);
    SDL_SetAlpha(bot, 0, 255);
    SDL_SetAlpha(botLeft, 0, 255);
    SDL_SetAlpha(botRight, 0, 255);
    
    heart = loadImage("gfx/heart.png");
    
    fuelText = TTF_RenderText_Solid(font, "Fuel", textcolor);
    fuelSprite = loadImage("gfx/fuel.png");
    
    drillText = TTF_RenderText_Solid(font, "Drill Power", textcolor);
    drillLevel = loadImage("gfx/drill.png");

	if(screen != NULL){  /* if we created a screen then wait for user to ask to exit */
		while(!menuQuit)
        {
            levelFinished = 0;
            levelNumber++;
            if(levelNumber<=3)
            {
                row *= levelNumber;
                col *= levelNumber;
            } else {
                row += 50;
                col += 10;
            }
            
            level = createLevel(row, col, chanceToStartAlive, birthLimit, deathLimit, numberOfSteps);
            
            maze = renderMaze(tileSize,level, row, col, base, top, topLeft, topRight, bot, botLeft, botRight);
            if(maze == NULL)
            {
                printf("Couldn't render maze\n");
                menuQuit = 1;
            }
            
            player.y = 800 - (32 * tileSize);
            player.x = 40 * tileSize;
            
            yMazeOffset = - (row*tileSize - 800);
            xMazeOffset = 0;
            
            /* make background black */
            SDL_FillRect(screen, NULL, 0x00000000);
            
            SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
            

            /* Loop indefinitely for messages */
            while (!menuQuit&&!levelFinished)
            {
                /* get input from user */
                input = getInput();
                
                keystate = SDL_GetKeyState(NULL);
                
                x = 0;
                y = 0;
                
                if ( keystate[SDLK_RIGHT] ) x-=10;
                if ( keystate[SDLK_LEFT] ) x+=10;
                if ( keystate[SDLK_UP] ){
                    if(fuel>0){
                        y+=20;
                        fuel-=10;
                    }
                } else {
                    if(fuel<fuelMAX) fuel+=5;
                }
                
                y-=10;
                
                if(x<0){
                    playerSprite = playerRight;
                    xAxeRange = 40;
                    yAxeRange = 0;
                } else if(x>0) {
                    playerSprite = playerLeft;
                    xAxeRange = -30;
                    yAxeRange = 0;
                } else {
                    playerSprite = playerCenter;
                    xAxeRange = 0;
                    yAxeRange = 0;
                }
                if ( keystate[SDLK_DOWN] ){
                    yAxeRange = 40;
                    xAxeRange = 0;
                }
                
                if ( keystate[SDLK_z] ){
                    x = 0;
                    y = 0;
                    if(drillPower>200)
                    {
                        drillPower -= 200;
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
                        digRect.x = player.x-xMazeOffset+xAxeRange;
                        digRect.y = player.y-yMazeOffset+yAxeRange;
                        SDL_FillRect(maze, &digRect, 0x000000FF);
                    }
                } else if(drillPower<drillMAX) drillPower += 5;
                
                movePlayer(&player, x, y, tileSize, &xMazeOffset, &yMazeOffset, level, row, col);
                
                SDL_FillRect(screen, NULL, 0x0000000);

                /* put loaded image on screen at x, y coords */
                drawImage(screen, maze, xMazeOffset, yMazeOffset, 1, 1);
                
                drawImage(screen, playerSprite, player.x, player.y, 1, 1);
                
                for(i=0; i<lives; i++)
                {
                    drawImage(screen, heart, 30 + 50*i, 30, 1, 1);
                }
                
                drawImage(screen, fuelText, 30, 80, 1, 1);
                
                for(i=0; i<fuel/10; i++)
                {
                    drawImage(screen, fuelSprite, 30 + i, 100, 1, 1);
                }
                
                drawImage(screen, drillText, 30, 120, 1, 1);
                
                for(i=0; i<drillPower/10; i++)
                {
                    drawImage(screen, drillLevel, 30 + i, 140, 1, 1);
                }
                
                if(levelDisplayed)
                {
                    displayLevel(screen, levelNumber);
                    levelDisplayed = 0;
                }

                SDL_Flip(screen);
                
                /* Sleep briefly to stop sucking up all the CPU time */
                SDL_Delay(3);
                
                if(input == SDLK_ESCAPE)
                {
                    menuQuit = askToQuit(screen);
                }
                
                if(input == SDLK_f)
                {
                    levelFinished = 1;
                    levelDisplayed = 1;
                }

            }
            
            deleteLevel(level, row);
        }
	}
	/* Exit the program */
	SDL_Quit();
	
	return 0;
}
