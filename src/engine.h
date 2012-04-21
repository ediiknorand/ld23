#include <SDL/SDL.h>

#ifndef H_GAME_ENGINE_H
#define H_GAME_ENGINE_H

typedef struct
{
  int width, height, bpp;
  Uint32 flags;
  SDL_Surface *screen;
} Screen;

typedef struct
{
  unsigned char up, down, left, right, quit;
} Input;

/* Global Vars */
Screen engine_screen;
Input engine_input;
int engine_scene;

/* Init Functions */
void engine_init_sdl();
void engine_init_screen(int width, int height, int bpp, Uint32 flags);
void engine_init_input();

/* Input process */
void engine_input_process();

/* Game run */
void engine_run();

/* Blit Images */
void engine_draw_sprite(SDL_Surface *sprite_sheet,
                        Sint16 src_x, Sint16 src_y, 
			Uint16 src_w, Uint16 src_h, 
			Sint16 dest_x, Sint16 dest_y);

/* Load scene */
void engine_load_scene(int scene);

#endif
