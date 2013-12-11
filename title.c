#include "title.h"

void title(){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	TTF_Init();

	SDL_Surface *background = NULL;
	SDL_Surface *title = NULL;
	SDL_Surface *screen = NULL;

	SDL_Event event;

	TTF_Font *font;

	SDL_Color textcolor = {255,00,00};
	
	screen = SDL_SetVideoMode( 1280, 800, 32, SDL_SWSURFACE ); 
		
	background = IMG_Load("gfx/Terraria");
	font = TTF_OpenFont("gfx/PokemonSolid",70);
	if(font == NULL){
		printf("Couldn't open font\n");
	}
	title = TTF_RenderText_Solid( font, "JetBEAR", textcolor );
	
	drawImage(screen,background,0,0);
	drawImage(screen,title,600,200);
	SDL_Flip(screen);

	SDL_Delay(5000);
	
	SDL_FreeSurface(background);
	SDL_FreeSurface(title);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	}
