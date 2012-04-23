#include "engine.h"
#include "game.h"
#include "world.h"
#include "collision.h"

void world_init()
{
  game_data.world.x = game_data.player.x;
  game_data.world.y = game_data.player.y;
  game_data.world.sx = 5;
  game_data.world.sy = 5;

  game_data.world.join = 1;
  game_data.world.joined = 1;

  game_data.world.cooldown = 0;

  game_data.world.powerup_type = 0;
  game_data.world.invencible = 0;
  game_data.world.life = 100;
}

void world_join()
{
  game_data.world.join = 1;
}

void world_leave()
{
  game_data.world.join = 0;
  game_data.world.joined = 0;
}

void world_update(Uint32 delta)
{
  if(game_data.world.joined)
  {
    game_data.world.x = game_data.player.x - 100;
    game_data.world.y = game_data.player.y - 50;
    return;
  }
  if(game_data.world.x < 0)
    game_data.world.x = 0;
  if(game_data.world. y < 0)
    game_data.world.y = 0;
  if(game_data.world.x + 119 > engine_screen.width)
    game_data.world.x = engine_screen.width - 119;
  if(game_data.world.y + 119 > engine_screen.height)
    game_data.world.y = engine_screen.height - 119;

  if(!(game_data.world.join))
    return;

  game_data.world.sx = (game_data.player.x - game_data.world.x)/(engine_screen.width/32);
  game_data.world.sy = (game_data.player.y - game_data.world.y)/(engine_screen.height/32);

  game_data.world.x += game_data.world.sx*(int)delta/30;
  game_data.world.y += game_data.world.sy*(int)delta/30;

  if(collision_detect_world())
    game_data.world.joined = 1;
}
