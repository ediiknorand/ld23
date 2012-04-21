#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "scene.h"

/* Initialization functions */
void engine_init_sdl()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
}

void engine_init_screen(int width, int height, int bpp, Uint32 flags)
{
  engine_screen.width = width;
  engine_screen.height = height;
  engine_screen.bpp = bpp;
  engine_screen.flags = flags;

  engine_screen.screen = SDL_SetVideoMode(width, height, bpp, flags);
  if(!(engine_screen.screen))
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }
}

void engine_init_input()
{
  engine_input.up = 0;
  engine_input.down = 0;
  engine_input.left = 0;
  engine_input.right = 0;
  engine_input.quit = 0;
}



/* Input Process */
void set_key(SDLKey k, unsigned char status)
{
  switch(k)
  {
  case SDLK_UP: engine_input.up = status; break;
  case SDLK_DOWN: engine_input.down = status; break;
  case SDLK_LEFT: engine_input.left = status; break;
  case SDLK_RIGHT: engine_input.right = status; break;
  case SDLK_q: engine_input.quit = status; break;
  }
}

void engine_input_process()
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
    case SDL_KEYDOWN: set_key(event.key.keysym.sym, 1); break;
    case SDL_KEYUP: set_key(event.key.keysym.sym, 0); break;
    case SDL_QUIT: engine_input.quit = 1; break;
    }
  }
}

/* Game runs */
int logic_refresh(Uint32 delta)
{
  engine_input_process();
  if(engine_input.quit)
    return 0;
  switch(engine_scene)
  {
  case SCENE_INIT: return scene_logic_init(delta); break;
  case SCENE_GAME: return scene_logic_game(delta); break;
  }
  return 1;
}

void render_refresh(Uint32 delta)
{
  switch(engine_scene)
  {
  case SCENE_INIT: scene_render_init(delta); break;
  case SCENE_GAME: scene_render_game(delta); break;
  }
  SDL_Flip(engine_screen.screen);
  SDL_FillRect(engine_screen.screen, NULL, 0);
}

void engine_run()
{
  int running;
  Uint32 now, before;

  running = 1;
  before = SDL_GetTicks();
  while(running)
  {
    now = SDL_GetTicks();
    running = logic_refresh(now - before);
    render_refresh(now - before);
    SDL_Delay(30); /* <- why not Vsynced? */
    before = now;
  }
}

/* Blit Images */
void engine_draw_sprite(SDL_Surface *sprite_sheet, Sint16 src_x, Sint16 src_y, Uint16 src_w, Uint16 src_h, Sint16 dest_x, Sint16 dest_y)
{
  SDL_Rect src, dest;
  src.x = src_x;
  src.y = src_y;
  src.w = src_w;
  src.h = src_h;
  dest.x = dest_x;
  dest.y = dest_y;

  SDL_BlitSurface( sprite_sheet, &src, engine_screen.screen, &dest);
}

/* Load - useless function, actually */
void engine_load_scene(int scene)
{
  switch(scene)
  {
  case SCENE_INIT: scene_load_init(); break;
  case SCENE_GAME: scene_load_game(); break;
  }
}

/* Sprite */
void engine_load_sprite(char *filename)
{
  SDL_Surface *aux = SDL_LoadBMP(filename);
  SDL_SetColorKey(aux, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(aux->format, 255, 0, 255));
  engine_sprites = SDL_DisplayFormat(aux);
  SDL_FreeSurface(aux);
}
