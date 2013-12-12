#include "main.h"


// #ifdef main
// #  undef main
// #endif

typedef struct{
    int x;
    int y;
} Position;

typedef struct{
    int x;
    int y;
    int step;
} SlugPosition;

typedef struct{
    int x;
    int y;
    int found;
} CoinPosition;

void animateBear(SDL_Rect* clip)
{
	int i;
	for( i = 0; i < 8; i += 1) {
        
		clip[i].x = 0 + i*55;
		clip[i].y = 0;
		
		clip[i].w = 55;
		clip[i].h = 60;
	}
}

void animateCoin(SDL_Rect* clip)
{
	int i;
	for( i = 0; i < 9; i += 1) {
        
		clip[i].x = 0 + i*20;
		clip[i].y = 0;
		
		clip[i].w = 20;
		clip[i].h = 20;
	}
}

void animateSlug(SDL_Rect* clip)
{
	int i;
	for( i = 0; i < 6; i += 1) {
        
		clip[i].x = 0 + i*59;
		clip[i].y = 0;
		
		clip[i].w = 59;
		clip[i].h = 44;
	}
}

CoinPosition* placeCoins(int numberOfCoins, int row, int col, int tileSize)
{
    srand((unsigned)time(NULL));
    int i;
    CoinPosition* coins = (CoinPosition*)malloc(numberOfCoins * sizeof(CoinPosition));
    for(i=0; i<numberOfCoins; i++)
    {
        coins[i].x = (rand()%((col-16)*tileSize))+8*tileSize;
        coins[i].y = (rand()%((row-16)*tileSize))+8*tileSize;
        coins[i].found = 0;
    }
    return coins;
}

SlugPosition* createSlugs(int numberOfSlugs, char** level, int row, int col, int tileSize)
{
    int i;
    int x, y;
    int found = 0;
    SlugPosition* slugs = (SlugPosition*)malloc(numberOfSlugs * sizeof(SlugPosition));
    for(i=0; i<numberOfSlugs; i++)
    {
        found = 0;
        while(!found)
        {
            x = (rand()%(col-16))+8;
            y = (rand()%(row-16))+8;
            if((level[y][x] == ' ')&&(level[y][x+5] == ' ')&&(level[y+5][x+5] == ' ')&&(level[y+5][x] == ' ')) found = 1;
        }
        slugs[i].x = x*tileSize;
        slugs[i].y = y*tileSize;
        slugs[i].step = -((rand()%1) + 1);
    }
    return slugs;
}

void movePlayer(Position* player, int x, int y, int tileSize, int* xMazeOffset, int* yMazeOffset, int* xBGOffset, int* yBGOffset,char** level, int row, int col)
{
    int vBlocked, hBlocked;
    
    if(((player->y - y - *yMazeOffset)/tileSize > 1)&&
       ((player->y - y - *yMazeOffset)/tileSize < row-1)&&
       ((player->x - x - *xMazeOffset)/tileSize > 0)&&
       ((player->x - x - *xMazeOffset)/tileSize < col))
    {
        if((level[(player->y - y - *yMazeOffset)/tileSize][((player->x - *xMazeOffset)/tileSize)] != ' ')||//topleft
           (level[(player->y - y - *yMazeOffset)/tileSize][((player->x - *xMazeOffset + 55)/tileSize)] != ' ')||//topright
           (level[(player->y - y - *yMazeOffset + 55)/tileSize][((player->x - *xMazeOffset)/tileSize)] != ' ')||//botleft
           (level[(player->y - y - *yMazeOffset + 55)/tileSize][((player->x - *xMazeOffset + 55)/tileSize)] != ' '))//botright
        {
            vBlocked = 1;
        }
        else
        {
            vBlocked = 0;
        }
        
        if((level[((player->y - *yMazeOffset)/tileSize)][((player->x - x - *xMazeOffset)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset)/tileSize)][((player->x - x - *xMazeOffset + 55)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset + 55)/tileSize)][((player->x - x - *xMazeOffset)/tileSize)] != ' ')||
           (level[((player->y - *yMazeOffset + 55)/tileSize)][((player->x - x - *xMazeOffset + 55)/tileSize)] != ' '))
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
            *yBGOffset += 1;
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
            *xBGOffset += 1;
        }
        else
        {
            player->x -= x;
        }

    }
}

void moveSlug(SlugPosition* player, int x, int y, int tileSize, char** level, int row, int col)
{
    int vBlocked, hBlocked;
    
    if(((player->y - y)/tileSize > 1)&&
       ((player->y - y)/tileSize < row-1)&&
       ((player->x - x)/tileSize > 0)&&
       ((player->x - x)/tileSize < col))
    {
        if((level[(player->y - y )/tileSize][((player->x)/tileSize)] != ' ')||//topleft
           (level[(player->y - y )/tileSize][((player->x + 60)/tileSize)] != ' ')||//topright
           (level[(player->y - y + 30)/tileSize][((player->x)/tileSize)] != ' ')||//botleft
           (level[(player->y - y + 30)/tileSize][((player->x + 60)/tileSize)] != ' '))//botright
        {
            vBlocked = 1;
        }
        else
        {
            vBlocked = 0;
        }
        
        if((level[((player->y)/tileSize)][((player->x - x)/tileSize)] != ' ')||
           (level[((player->y)/tileSize)][((player->x - x + 60)/tileSize)] != ' ')||
           (level[((player->y + 30)/tileSize)][((player->x - x)/tileSize)] != ' ')||
           (level[((player->y + 30)/tileSize)][((player->x - x + 60)/tileSize)] != ' '))
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
            player->y -= y;
    }
    if(!hBlocked)
    {
            player->x -= x;
    }
    if(hBlocked) player->step = -player->step;
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
            if(level[i][j] == '0') drawImage(maze, base, NULL, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == 't') drawImage(maze, top, NULL, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '1') drawImage(maze, topLeft, NULL, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '2') drawImage(maze, topRight, NULL, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == 'b') drawImage(maze, bot, NULL, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '3') drawImage(maze, botLeft, NULL, j*tileSize, i*tileSize, 1, 1);
            if(level[i][j] == '4') drawImage(maze, botRight, NULL, j*tileSize, i*tileSize, 1, 1);
        }
    }   
    return maze;
}




int main(int argc, char *argv[])
{
	int input = 0;
    int i, j;
    int e = 0;
    int x = 0;
    int y = 0;
    
    int xMazeOffset;
    int yMazeOffset;
    
    int xBGOffset;
    int yBGOffset;
    
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
    int fuel = 1400;
    int drillPower = 1400;
    int shield = 0;
    int coinsCollected = 0;
    
    int bearFrame = 0;
    int coinFrame = 0;
    int slugFrame = 0;
    
    int menuQuit = 0;
    int levelDisplayed = 1;
    int levelNumber = 0;
    int levelFinished = 0;
    
    char** level = NULL;
    CoinPosition* coins = NULL;
    SlugPosition* slugs = NULL;
    
    char *name;
	int score; 
	FILE *scorestream;
	scorestream = fopen("highscores.txt","a+");
	char nameput;
    
    TTF_Init();
    
    SDL_Color textcolor = {255,255,255};
    TTF_Font *font;
	font = TTF_OpenFont("gfx/MonospaceTypewriter.ttf",10);
	if(font == NULL){
        printf("Cannot open font\n");
        return 0;
	}

    Position player;
    Position portalPosition;
    
    Uint8 *keystate;
    
    FILE *highscores;
	
	SDL_Surface *screen;  /* screen surface */
    SDL_Surface *maze = NULL;
    SDL_Surface *BG = NULL;
    
    SDL_Surface *playerSprite;
    SDL_Surface *playerRight;
    SDL_Surface *playerLeft;
    SDL_Surface *playerFlyRight;
    SDL_Surface *playerFlyLeft;
    
    SDL_Surface *slugLeft;
    SDL_Surface *slugRight;
    
    SDL_Rect bearRect[8];
    SDL_Rect coinRect[9];
    SDL_Rect slugRect[9];
    
    SDL_Surface *base;
    SDL_Surface *top;
    SDL_Surface *topLeft;
    SDL_Surface *topRight;
    SDL_Surface *bot;
    SDL_Surface *botLeft;
    SDL_Surface *botRight;
    
    SDL_Surface *heart;
    SDL_Surface *coin;
    
    SDL_Surface *portal;
    
    SDL_Surface *coinAmount;
    
    SDL_Surface *fuelText;
    SDL_Surface *fuelSprite;
    
    SDL_Surface *drillText;
    SDL_Surface *drillLevel;
    
    SDL_Surface *fader;
    
    SDL_Rect digRect;
    
    digRect.x = 0;
    digRect.y = 0;
    
    digRect.w = 55;
    digRect.h = 60;
    

	/* Start up SDL */
	screen = initScreen("JetBear");
    
    menuQuit = title(screen);
    if(menuQuit)
    {
        SDL_Quit();
        return 0;
    }
    
    BG = loadImage("gfx/bg.png");
    
    playerRight = loadImage("gfx/Bear_walking_right.png");
    playerLeft = loadImage("gfx/Bear_walking_left.png");
    playerFlyRight = loadImage("gfx/Bear_flying_right.png");
    playerFlyLeft = loadImage("gfx/Bear_flying_left.png");
    playerSprite = playerRight;
    
    slugRight = loadImage("gfx/slug_right.png");
    slugLeft = loadImage("gfx/slug_left.png"); //
    
    base = loadImage("gfx/base.png");
    top = loadImage("gfx/top.png");
    topLeft = loadImage("gfx/topleft.png");
    topRight = loadImage("gfx/topright.png");
    bot = loadImage("gfx/bot.png");
    botLeft = loadImage("gfx/botleft.png");
    botRight = loadImage("gfx/botright.png");
    
    fader = SDL_CreateRGBSurface(SDL_SRCALPHA, 1440, 800, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_FillRect(fader, NULL, 0xC00000A0);
    
    SDL_SetAlpha(base, 0, 255);
    SDL_SetAlpha(top, 0, 255);
    SDL_SetAlpha(topLeft, 0, 255);
    SDL_SetAlpha(topRight, 0, 255);
    SDL_SetAlpha(bot, 0, 255);
    SDL_SetAlpha(botLeft, 0, 255);
    SDL_SetAlpha(botRight, 0, 255);
    
    heart = loadImage("gfx/heart.png");
    coin = loadImage("gfx/coin.png");
    
    portal = loadImage("gfx/portal.png");
    
    fuelText = TTF_RenderText_Solid(font, "Fuel", textcolor);
    fuelSprite = loadImage("gfx/fuel.png");
    
    drillText = TTF_RenderText_Solid(font, "Drill Power", textcolor);
    drillLevel = loadImage("gfx/drill.png");
    
    animateBear(bearRect);
    animateCoin(coinRect);
    animateSlug(slugRect);

	if(screen != NULL){  /* if we created a screen then wait for user to ask to exit */
		while(!menuQuit)
        {
            free(coins);
            free(slugs);
            levelFinished = 0;
            levelDisplayed = 1;
            
            levelNumber++;
            if(levelNumber<=3)
            {
                row *= levelNumber;
                col *= levelNumber;
            } else {
                row += 10;
                col += 10;
            }
            
            level = createLevel(row, col, chanceToStartAlive, birthLimit, deathLimit, numberOfSteps);
            
            coins = placeCoins(levelNumber*levelNumber*20, row, col, tileSize);
            slugs = createSlugs(levelNumber*levelNumber*20, level, row, col, tileSize);
            
            
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
            
            xBGOffset = 0;
            yBGOffset = 0;
            
            portalPosition.x = (col - 10)*tileSize;
            portalPosition.y = 20*tileSize;
            
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
                    if(fuel<1400) fuel+=5;
                }
                
                y-=10;
                
                
                if(y>0)
                {
                    if(x<0){
                        playerSprite = playerFlyRight;
                        xAxeRange = 55;
                        yAxeRange = 0;
                        bearFrame ++;
                    } else if(x>0) {
                        playerSprite = playerFlyLeft;
                        xAxeRange = -45;
                        yAxeRange = 0;
                        bearFrame ++;
                    } else {
                        if(playerSprite == playerRight) playerSprite = playerFlyRight;
                        if(playerSprite == playerLeft) playerSprite = playerFlyLeft;
                        xAxeRange = 0;
                        yAxeRange = 0;
                    }
                } else {
                    if(x<0){
                        playerSprite = playerRight;
                        xAxeRange = 55;
                        yAxeRange = 0;
                        bearFrame ++;
                    } else if(x>0) {
                        playerSprite = playerLeft;
                        xAxeRange = -45;
                        yAxeRange = 0;
                        bearFrame ++;
                    } else {
                        if(playerSprite == playerFlyRight) playerSprite = playerRight;
                        if(playerSprite == playerFlyLeft) playerSprite = playerLeft;
                        xAxeRange = 0;
                        yAxeRange = 0;
                    }
                }
                if ( keystate[SDLK_DOWN] ){
                    yAxeRange = 60;
                    xAxeRange = 0;
                }
                
                if(bearFrame==8)
                {
                    bearFrame = 0;
                }
                
                if ( keystate[SDLK_z] ){
                    x = 0;
                    y = 0;
                    if(drillPower>200)
                    {
                        drillPower -= 200;
                        for(i=0;i<6;i++)
                        {
                            for(j=0;j<6;j++)
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
                        SDL_FillRect(maze, &digRect, 0x00000000);
                    }
                } else if(drillPower<1400) drillPower += 5;
                
                movePlayer(&player, x, y, tileSize, &xMazeOffset, &yMazeOffset, &xBGOffset, &yBGOffset, level, row, col);
                
                
                for(i=0; i<levelNumber*levelNumber*20; i++)
                {
                    moveSlug(&slugs[i], slugs[i].step, -10, tileSize, level, row, col);
                }
                
                for(i=0; i<levelNumber*levelNumber*20; i++)
                {
                    if((slugs[i].x + xMazeOffset > player.x)&&
                       (slugs[i].x + xMazeOffset < player.x + 55)&&
                       (slugs[i].y + yMazeOffset > player.y)&&
                       (slugs[i].y + yMazeOffset < player.y + 56))
                    {
                        if(shield == 0)
                        {
                            lives--;
                            shield = 20;
                        }
                        if(lives == 0)
                        {
                            displayGameOver(screen);
                            
                            while(nameput != '\n'){
                            	nameput = getInput();
                            	name[e] = nameput;
                            	e++
                            }
                            
                            writeScore(name,score,scorestream)
                            menuQuit = 1;
                        }
                    }
                }
                
                for(i=0; i<levelNumber*levelNumber*20; i++)
                {
                    if(!coins[i].found)
                    {
                        if((coins[i].x + xMazeOffset >= player.x-10)&&
                           (coins[i].x + xMazeOffset <= player.x + 55)&&
                           (coins[i].y + yMazeOffset >= player.y-10)&&
                           (coins[i].y + yMazeOffset <= player.y + 56))
                        {
                            coins[i].found = 1;
                            coinsCollected++;
                        }
                    }
                }
                
                if((portalPosition.x + xMazeOffset > player.x)&&
                   (portalPosition.x + xMazeOffset < player.x + 55)&&
                   (portalPosition.y + yMazeOffset > player.y)&&
                   (portalPosition.y + yMazeOffset < player.y + 56))
                {
                    levelFinished = 1;
                    levelDisplayed = 1;
                }
                
                //clear screen
                SDL_FillRect(screen, NULL, 0x0000000);
                
                drawImage(screen, BG, NULL, xBGOffset, yBGOffset, 1, 1);

                //place maze
                drawImage(screen, maze, NULL, xMazeOffset, yMazeOffset, 1, 1);
                
                
                //place coins
                for(i=0; i<levelNumber*levelNumber*20; i++)
                {
                    if(!coins[i].found)drawImage(screen, coin, &coinRect[coinFrame], coins[i].x + xMazeOffset, coins[i].y + yMazeOffset, 1, 1);
                }
                
                for(i=0; i<levelNumber*levelNumber*20; i++)
                {
                    if(slugs[i].step>0)
                    {
                        drawImage(screen, slugLeft, &slugRect[slugFrame], slugs[i].x + xMazeOffset, slugs[i].y + yMazeOffset, 1, 1);
                    } else {
                        drawImage(screen, slugRight, &slugRect[slugFrame], slugs[i].x + xMazeOffset, slugs[i].y + yMazeOffset, 1, 1);
                    }
                }
                
                //place exit portal
                drawImage(screen, portal, NULL, portalPosition.x + xMazeOffset, portalPosition.y + yMazeOffset, 1, 1);
                
                //place player
                drawImage(screen, playerSprite, &bearRect[bearFrame], player.x, player.y, 1, 1);
                
                
                //place lives
                for(i=0; i<lives; i++)
                {
                    drawImage(screen, heart, NULL, 30 + 50*i, 30, 1, 1);
                }
                
                //place fuel bar
                drawImage(screen, fuelText, NULL, 30, 80, 1, 1);
                
                for(i=0; i<fuel/10; i++)
                {
                    drawImage(screen, fuelSprite, NULL, 30 + i, 100, 1, 1);
                }
                
                //place drill power bar
                drawImage(screen, drillText, NULL, 30, 120, 1, 1);
                
                for(i=0; i<drillPower/10; i++)
                {
                    drawImage(screen, drillLevel, NULL, 30 + i, 140, 1, 1);
                }
                
                //place coins collected bar
                char str[30];
                sprintf(str, "Coins: %d", coinsCollected);
                coinAmount = TTF_RenderText_Solid(font, str, textcolor);
                drawImage(screen, coinAmount, NULL, 30, 160, 1, 1);
                
                if(levelDisplayed)
                {
                    displayLevel(screen, levelNumber);
                    levelDisplayed = 0;
                }
                
                if(shield>0)
                {
                    if(shield%4) drawImage(screen, fader, NULL, 0, 0, 1, 1);
                    shield--;
                }

                SDL_Flip(screen);
                
                /* Sleep briefly to stop sucking up all the CPU time */
                SDL_Delay(3);
                
                coinFrame++;
                if(coinFrame==9)
                {
                    coinFrame = 0;
                }
                
                slugFrame++;
                if(slugFrame==6)
                {
                    slugFrame = 0;
                }
                    
                
                if(input == SDLK_ESCAPE)
                {
                    
                    menuQuit = askToQuit(screen);
//                    if(menuQuit) menuQuit = title(screen);
                }
                
                if(input == SDLK_f)
                {
                    levelFinished = 1;
                    levelDisplayed = 1;
                }
            }
            
            deleteLevel(level, row);
        }
        highscores = fopen("scores", "wb");
        fwrite(&coinsCollected, sizeof(coinsCollected), 1 , highscores);
        fclose(highscores);
	}
	/* Exit the program */
	SDL_Quit();
	
	return 0;
}
