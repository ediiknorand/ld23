#include <SDL/SDL.h>
#include "engine.h"

int main(int argc, char *argv[])
{
  engine_init_sdl();
  engine_init_screen(640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
  engine_init_input();
  engine_scene = 0;
  engine_load_scene(engine_scene);
  engine_run();

  return 42;
}
