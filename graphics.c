#include "graphics.h"

void drawImage(SDL_Surface *screen, SDL_Surface *image, int x, int y, float xRatio, float yRatio)
{
	SDL_Rect dest; /* this is an SDL rectangle that can define an area of a surface in terms of x,y coords and width and height */
	
	/* Set the blitting rectangle to the size of the src image */
	dest.x = x;
	dest.y = y;
	dest.w = (image->w)/xRatio;
	dest.h = (image->h)/yRatio;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	SDL_BlitSurface(image, NULL, screen, &dest);
}

SDL_Surface *loadImage(char *name)
{
	/* Load the image using SDL Image */
	
	
	SDL_Surface *image = NULL;
	SDL_Surface *temp = NULL;
	
	temp = IMG_Load(name);
	
	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		
	}
	else
	{	

		/* Convert the image to the screen's native format */
	
		image = SDL_DisplayFormatAlpha(temp);
	
		SDL_FreeSurface(temp);
	
		if (image == NULL)
		{
			printf("Failed to convert image %s to native format\n", name);
		
		}

	}
	/* Return pointer to the processed image or a NULL if failure */
	
	return image;
}

