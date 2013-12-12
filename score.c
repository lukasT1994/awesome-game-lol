#include "defs.h"

void writeScore(char* name,int score, FILE* stream){

	fputs(name,stream);
	fputc(' ',stream);
	fputc((char)score,stream);
	fputc('\n',stream);

return;
}

void printScores(SDL_Surface *screen,TTF_Font *font,SDL_Color Color){

	SDL_Surface *scoreboard = NULL;
	FILE *scoreptr = fopen("scoreboard.txt","a+");	
	
	char *scorestring;
	fgets(scorestring,5000,scoreptr);
	
	SDL_FillRect(screen,NULL,0x000000);

	scoreboard = TTF_RenderText_Solid(font,scorestring,Color);
	
	if(scoreboard != NULL){
		 drawImage(screen,scoreboard,600,100,1,1);
	}
	
	SDL_Flip(screen);
	SDL_FreeSurface(scoreboard);

	fclose(scoreptr);
	title(screen);
}
