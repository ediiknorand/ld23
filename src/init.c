#include "engine.h"
#include "scene.h"
#include "background.h"


/* Init Scene */
void scene_load_init()
{
  background_load("resource/init.bmp");
  scene_wait = 0;
}

int scene_logic_init(Uint32 delta)
{
  scene_wait += delta;
  if(engine_input.fire && scene_wait > 1200)
  {
    background_unload();
    engine_load_scene(SCENE_GAME);
    scene_wait = 0;
  }
  return 1;
}

void scene_render_init(Uint32 delta)
{
  background_draw(0, delta);
}
