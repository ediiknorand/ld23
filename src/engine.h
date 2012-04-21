#include <SDL/SDL.h>

#ifndef H_GAME_ENGINE_H
#define H_GAME_ENGINE_H

typedef struct
{
  int width, height, bpp;
  Uint32 flags;
} Screen;

typedef struct
{
  unsigned char up, down, left, right;
} Input;

/* Global Vars */
Screen engine_screen;
Input engine_input;

/* Init Functions */
void engine_init_sdl();
void engine_init_screen(int width, int height, int bpp, Uint32 flags);
void engine_init_input();

/* Input process */
void engine_input_process();

/* Game run */
void engine_run();

#endif
