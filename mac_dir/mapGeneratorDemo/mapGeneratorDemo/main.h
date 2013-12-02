#include "defs.h"
#include "mapGenerator.h"

extern SDL_Surface *initScreen(char *);
extern int getInput(void);
extern void drawImage(SDL_Surface *screen, SDL_Surface *image, int x, int y, int xRatio, int yRatio);
extern SDL_Surface *loadImage(char *name);
