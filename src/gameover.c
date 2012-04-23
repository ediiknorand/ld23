#include <SDL/SDL.h>
#include "engine.h"
#include "scene.h"
#include "background.h"


/* Init Scene */
void scene_load_gameover()
{
  SDL_FreeSurface(engine_sprites);
  engine_load_sprite("resource/gameover.bmp");
  scene_wait = 0;
}

int scene_logic_gameover(Uint32 delta)
{
  scene_wait += delta;
  if(engine_input.fire && scene_wait >= 1200)
  {
    SDL_FreeSurface(engine_sprites);
    engine_load_scene(SCENE_INIT);
    scene_wait = 700;
  }
  if(engine_input.quit)
    return 0;
  return 1;
}

void scene_render_gameover(Uint32 delta)
{
  engine_draw_sprite(engine_sprites, 0, 0, 300, 150, engine_screen.width/2-150, engine_screen.height/2-75);
}
