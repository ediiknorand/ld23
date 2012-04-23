#include <SDL/SDL.h>

#ifndef H_BACKGROUND_H
#define H_BACKGROUND_H

typedef struct
{
  SDL_Surface *img;
  int src_x;
} Background;

/* Global vars  */
Background background;

/* Functions */
void background_load(char *filename);
void background_unload();
void background_draw(int x, Uint32 delta);


#endif
