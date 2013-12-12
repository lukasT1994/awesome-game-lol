#include "defs.h"
#include "mapGenerator.h"
#include "title.h"

extern SDL_Surface *initScreen(char *);
extern int getInput(void);
extern void drawImage(SDL_Surface *screen, SDL_Surface *image, int x, int y, int xRatio, int yRatio);
extern SDL_Surface *loadImage(char *name);
extern int title(SDL_Surface *screen);
extern int askToQuit(SDL_Surface *screen);
extern void displayLevel(SDL_Surface *screen, int level);
