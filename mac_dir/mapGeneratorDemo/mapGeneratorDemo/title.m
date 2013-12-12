#include "title.h"

void title(){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	TTF_Init();

	SDL_Surface *background = NULL;
	SDL_Surface *title = NULL;
    SDL_Surface *titleShadow = NULL;
    SDL_Surface *instructions = NULL;
	SDL_Surface *screen = NULL;

	TTF_Font *font;

	SDL_Color shadowColor = {255,00,00};
	
	screen = SDL_SetVideoMode( 1440, 800, 32, SDL_SWSURFACE );
		
	background = IMG_Load("gfx/Terraria");
	font = TTF_OpenFont("gfx/PokemonSolid.ttf",70);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
	titleShadow = TTF_RenderText_Solid( font, "JetBEAR", shadowColor );
    
    
	font = TTF_OpenFont("gfx/PokemonSolid.ttf",68);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    
    SDL_Color titleColor = {251,202,15};
    title = TTF_RenderText_Solid( font, "JetBEAR", titleColor );
    
    font = TTF_OpenFont("gfx/MonospaceTypewriter.ttf",20);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
    
    SDL_Color instColor = {255,255,255};
    instructions = TTF_RenderText_Solid( font, "Press the arrow keys to move, press the UP key to fly and press Z to dig.", instColor );
//	drawImage(screen,background,0,0,1,1);
    drawImage(screen,titleShadow,550,200,1,1);
	drawImage(screen,title,550,200,1,1);
    drawImage(screen,instructions,300,400,1,1);
	SDL_Flip(screen);

	SDL_Delay(5000);
	
	SDL_FreeSurface(background);
	SDL_FreeSurface(title);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}
