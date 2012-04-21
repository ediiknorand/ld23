#include "engine.h"
#include "scene.h"
#include "test.h" /* test */


/* Init Scene */
void scene_load_init()
{
  engine_load_sprite("resource/sprite.bmp");
  player.x = engine_screen.width /2;
  player.y = engine_screen.height /2;
  player.sx = 3;
  player.sy = 3;
  player.hitbox_w = 43;
  player.hitbox_h = 43;
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
  if(player.x < 0)
    player.x = 0;
  if(player.y < 0)
    player.y = 0;
  if(player.x + player.hitbox_w > engine_screen.width)
    player.x = engine_screen.width - player.hitbox_w;
  if(player.y + player.hitbox_h > engine_screen.height)
    player.y = engine_screen.height - player.hitbox_h; /* just testing */
  return 1;
}

void scene_render_init(Uint32 delta)
{
  engine_draw_sprite(engine_sprites, 0, 0, 43, 43, player.x, player.y);
}
