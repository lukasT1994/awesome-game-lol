#include "title.h"

void runCredits(SDL_Surface *screen)
{
    int input = 0;
    
    TTF_Font *font;
    
    SDL_Surface *background = NULL;
    
    SDL_Surface *title = NULL;
    SDL_Surface *titleShadow = NULL;
    SDL_Surface *text = NULL;
    SDL_Surface *desName = NULL;
    SDL_Surface *nikilName = NULL;
    SDL_Surface *jayantName = NULL;
    SDL_Surface *lukeName = NULL;
    SDL_Surface *music = NULL;
    
    SDL_Color yellowColor = {251,202,15};
	SDL_Color redColor = {255,00,00};
	SDL_Color whiteColor = {255,255,255};
    
    background = IMG_Load("gfx/bg.png");
    
    font = TTF_OpenFont("gfx/PokemonSolid.ttf",30);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
	titleShadow = TTF_RenderText_Solid( font, "JetBEAR", redColor );
    
    //Title
	font = TTF_OpenFont("gfx/PokemonSolid.ttf",28);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    title = TTF_RenderText_Solid( font, "JetBEAR", yellowColor );
    
    //Instructions
    font = TTF_OpenFont("gfx/MonospaceTypewriter.ttf",20);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    text = TTF_RenderText_Solid( font, "is brought to you by:", whiteColor );
    
    desName = TTF_RenderText_Solid( font, "Desislav Hristov", whiteColor );
    nikilName = TTF_RenderText_Solid( font, "Nikil Menon", whiteColor );
    jayantName = TTF_RenderText_Solid( font, "Jayant Solanki", whiteColor );
    lukeName = TTF_RenderText_Solid( font, "Luke Thompson", whiteColor );
    music = TTF_RenderText_Solid( font, "music by Kevin MacLeod", whiteColor );
    
    while(!input)
    {
        input = getInput();
        
        SDL_FillRect(screen, NULL, 0x00000000);
        
        drawImage(screen, background, NULL, 0, 0, 1, 1);
        
        drawImage(screen,titleShadow,NULL,490,295,1,1);
        drawImage(screen,title,NULL,490,295,1,1);
        
        drawImage(screen,text,NULL,625,300,1,1);
        drawImage(screen,desName,NULL,590,350,1,1);
        drawImage(screen,nikilName,NULL,590,380,1,1);
        drawImage(screen,jayantName,NULL,590,410,1,1);
        drawImage(screen,lukeName,NULL,590,440,1,1);
        drawImage(screen,music,NULL,590,470,1,1);
        
        SDL_Flip(screen);
    }
    
    SDL_FreeSurface(title);
    SDL_FreeSurface(titleShadow);
    
    SDL_FreeSurface(text);
    SDL_FreeSurface(desName);
    SDL_FreeSurface(nikilName);
    SDL_FreeSurface(jayantName);
    SDL_FreeSurface(lukeName);
}

int askToQuit(SDL_Surface *screen)
{
    int menuCounter = 1;
    int quit = 0;
    int input = 0;

    TTF_Font *font;
    
    SDL_Color redColor = {255,00,00};
	SDL_Color whiteColor = {255,255,255};
    
    font = TTF_OpenFont("gfx/MonospaceTypewriter.ttf",20);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    
    SDL_Surface *question = NULL;
    SDL_Surface *yes = NULL;
    SDL_Surface *no = NULL;
    SDL_Surface *fader = NULL;
    
    question = TTF_RenderText_Solid(font, "Are you sure you want to quit?", whiteColor);
    
    fader = SDL_CreateRGBSurface(SDL_SRCALPHA, 1440, 800, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_FillRect(fader, NULL, 0x000000C0);
    drawImage(screen,fader,NULL,0,0,1,1);
    
    while(!quit)
    {
        input = getInput();
        
        switch (input) {
            case SDLK_LEFT:
                if(menuCounter>0) menuCounter--;
                break;
            case SDLK_RIGHT:
                if(menuCounter<1) menuCounter++;
                break;
            case SDLK_RETURN:
                switch (menuCounter) {
                    case 0:
                    	printScores(screen,font,whiteColor);
                        return 1;
                        break;
                    case 1:
                        quit = 1;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        
        switch (menuCounter) {
            case 0:
                yes = TTF_RenderText_Solid(font, "YES", redColor);
                no = TTF_RenderText_Solid(font, "NO", whiteColor);
                break;
            case 1:
                yes = TTF_RenderText_Solid(font, "YES", whiteColor);
                no = TTF_RenderText_Solid(font, "NO", redColor);
                break;
            default:
                break;
        }
        
        drawImage(screen,question,NULL,540,500,1,1);
        drawImage(screen,yes,NULL,590,530,1,1);
        drawImage(screen,no,NULL,790,530,1,1);
        
        SDL_Flip(screen);
        
    }
    SDL_FreeSurface(yes);
    SDL_FreeSurface(no);
    SDL_FreeSurface(question);
    SDL_FreeSurface(fader);
    
    return 0;
}

void displayGameOver(SDL_Surface *screen)
{
    
    TTF_Font *font;
    
    SDL_Color redColor = {255,00,00};
    SDL_Color yellowColor = {251,202,15};
    
    SDL_Surface *title = NULL;
    SDL_Surface *titleShadow = NULL;
    SDL_Surface *fader = NULL;
    
    
    fader = SDL_CreateRGBSurface(SDL_SRCALPHA, 1440, 800, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_FillRect(fader, NULL, 0x000000C0);
    
    font = TTF_OpenFont("gfx/PokemonSolid.ttf",68);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    titleShadow = TTF_RenderText_Solid( font, "Game Over", redColor );
    font = TTF_OpenFont("gfx/PokemonSolid.ttf",66);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    title = TTF_RenderText_Solid( font, "Game Over", yellowColor );
    
    drawImage(screen,fader,NULL,0,0,1,1);
    drawImage(screen,titleShadow,NULL,580,300,1,1);
    drawImage(screen,title,NULL,580,300,1,1);
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    SDL_FreeSurface(title);
    SDL_FreeSurface(titleShadow);
    SDL_FreeSurface(fader);
}

void displayLevel(SDL_Surface *screen, int level)
{
    //int input = 0;
    
    TTF_Font *font;
    
    SDL_Color redColor = {255,00,00};
    SDL_Color yellowColor = {251,202,15};
    
    SDL_Surface *title = NULL;
    SDL_Surface *titleShadow = NULL;
    SDL_Surface *fader = NULL;
    
    char str[30];
    sprintf(str, "Level %d", level);
    
    
    fader = SDL_CreateRGBSurface(SDL_SRCALPHA, 1440, 800, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_FillRect(fader, NULL, 0x000000C0);
    
    font = TTF_OpenFont("gfx/PokemonSolid.ttf",68);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    titleShadow = TTF_RenderText_Solid( font, str, redColor );
    font = TTF_OpenFont("gfx/PokemonSolid.ttf",66);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    title = TTF_RenderText_Solid( font, str, yellowColor );
    
    drawImage(screen,fader,NULL,0,0,1,1);
    drawImage(screen,titleShadow,NULL,580,300,1,1);
    drawImage(screen,title,NULL,580,300,1,1);
    SDL_Flip(screen);
    
    SDL_Delay(1000);
    SDL_FreeSurface(title);
    SDL_FreeSurface(titleShadow);
    SDL_FreeSurface(fader);
}

int title(SDL_Surface *screen){
    
    int startGame = 0;
    int menuCounter = 0;
    int input = 0;
    int check = 0;
    
    FILE *highscores;
    int score;
    
	SDL_Surface *background = NULL;
	SDL_Surface *title = NULL;
    SDL_Surface *titleShadow = NULL;
    SDL_Surface *instructions = NULL;
    
    SDL_Surface *start = NULL;
    SDL_Surface *scores = NULL;
    SDL_Surface *credits = NULL;
    SDL_Surface *quit = NULL;
    
	TTF_Font *font;
    
	background = IMG_Load("gfx/bg.png");
    
	//Define Colors
	SDL_Color yellowColor = {251,202,15};
	SDL_Color redColor = {255,00,00};
	SDL_Color whiteColor = {255,255,255};
    
    //Shadow
	font = TTF_OpenFont("gfx/PokemonSolid.ttf",70);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
	titleShadow = TTF_RenderText_Solid( font, "JetBEAR", redColor );
    
    //Title
	font = TTF_OpenFont("gfx/PokemonSolid.ttf",68);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    title = TTF_RenderText_Solid( font, "JetBEAR", yellowColor );
    
    //Instructions
    font = TTF_OpenFont("gfx/MonospaceTypewriter.ttf",20);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    instructions = TTF_RenderText_Solid( font, "Press the arrow keys to move, press the UP key to fly and press Z to dig.", whiteColor );
    
    
    //Menu Loop
    while(!startGame)
    {
        input = getInput();
        
        switch (input) {
            case SDLK_UP:
                if(menuCounter>0) menuCounter--;
                break;
            case SDLK_DOWN:
                if(menuCounter<3) menuCounter++;
                break;
            case SDLK_RETURN:
                switch (menuCounter) {
                    case 0:
                        startGame = 1;
                        break;
                    case 1:
                        highscores = fopen("scores", "rb");
                        fread(&score, sizeof(score), 1 , highscores);
                        fclose(highscores);
                        printf("%d\n", score);
                        break;
                    case 2:
                        runCredits(screen);
                        break;
                    case 3:
                        return 1;
                        break;
                    default:
                        break;
                }
                break;
            case SDLK_ESCAPE:
                check = askToQuit(screen);
                if(check) return 1;
                break;
            default:
                break;
        }
        
        switch (menuCounter) {
            case 0:
                start = TTF_RenderText_Solid(font, "Start", redColor);
                scores = TTF_RenderText_Solid(font, "High Scores", whiteColor);
                credits = TTF_RenderText_Solid(font, "Credits", whiteColor);
                quit = TTF_RenderText_Solid(font, "Quit", whiteColor);
                break;
            case 1:
                start = TTF_RenderText_Solid(font, "Start", whiteColor);
                scores = TTF_RenderText_Solid(font, "High Scores", redColor);
                credits = TTF_RenderText_Solid(font, "Credits", whiteColor);
                quit = TTF_RenderText_Solid(font, "Quit", whiteColor);
                break;
            case 2:
                start = TTF_RenderText_Solid(font, "Start", whiteColor);
                scores = TTF_RenderText_Solid(font, "High Scores", whiteColor);
                credits = TTF_RenderText_Solid(font, "Credits", redColor);
                quit = TTF_RenderText_Solid(font, "Quit", whiteColor);
                break;
            case 3:
                start = TTF_RenderText_Solid(font, "Start", whiteColor);
                scores = TTF_RenderText_Solid(font, "High Scores", whiteColor);
                credits = TTF_RenderText_Solid(font, "Credits", whiteColor);
                quit = TTF_RenderText_Solid(font, "Quit", redColor);
                break;
            default:
                break;
        }
        
        SDL_FillRect(screen, NULL, 0x00000000);
        
        drawImage(screen, background, NULL, 0, 0, 1, 1);
        
        drawImage(screen,titleShadow,NULL,580,200,1,1);
        drawImage(screen,title,NULL,580,200,1,1);
        drawImage(screen,instructions,NULL,300,400,1,1);
        
        drawImage(screen,start,NULL,690,500,1,1);
        drawImage(screen,scores,NULL,655,530,1,1);
        drawImage(screen,credits,NULL,680,560,1,1);
        drawImage(screen,quit,NULL,695,590,1,1);
        
        SDL_Flip(screen);
        
        
    }
    SDL_FreeSurface(title);
    SDL_FreeSurface(titleShadow);
    SDL_FreeSurface(start);
    SDL_FreeSurface(scores);
    SDL_FreeSurface(credits);
    SDL_FreeSurface(quit);
    
    return 0;
}
