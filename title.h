#include "defs.h"

extern SDL_Surface *initScreen(char *);
extern int getInput(void);
extern void drawImage(SDL_Surface *screen, SDL_Surface *image, SDL_Rect *clip, int x, int y, float xRatio, float yRatio);
extern SDL_Surface *loadImage(char *name);