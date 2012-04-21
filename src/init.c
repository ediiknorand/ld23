#include "engine.h"
#include "scene.h"
#include "test.h" /* test */


/* Init Scene */
void scene_load_init()
{
  engine_load_sprite("resource/sprite.bmp");
  player.x = engine_screen.width /2;
  player.y = engine_screen.height /2;
  player.sx = 1;
  player.sy = 1;
}

int scene_logic_init(Uint32 delta)
{
  if(engine_input.up)
    player.y -= player.sy*delta/15;
  if(engine_input.down)
    player.y += player.sy*delta/15;
  if(engine_input.left)
    player.x -= player.sx*delta/15;
  if(engine_input.right)
    player.x += player.sx*delta/15;
  return 1;
}

void scene_render_init(Uint32 delta)
{
  engine_draw_sprite(engine_sprites, 0, 0, 43, 43, player.x, player.y);
}
