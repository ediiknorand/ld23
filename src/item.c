#include "engine.h"
#include "game.h"
#include "collision.h"

void game_create_item(int x, int y, int sx, int sy, unsigned char type)
{
  Bullet *t;
  unsigned int i = 0;

  if(game_data.valid_item >= game_data.n_item)
    return;
  for(i = 0; i < game_data.n_item && game_data.items[i].type; i++);
  if(i > game_data.valid_item && i < game_data.n_item)
    game_data.valid_item = i;
  if(i >= game_data.n_item)
    return;
  t = &(game_data.items[i]);
  t->x = x;
  t->y = y;
  t->sx = sx;
  t->sy = sy;
  t->type = type;
}

void game_destroy_item(unsigned int t)
{
  unsigned int i;

  if(t >= game_data.n_item || t > game_data.valid_item)
    return;
  game_data.items[t].type = 0;
  for(i = game_data.valid_item; i >= 0 && !(game_data.items[i].type); i--)
    game_data.valid_item = i;
}

void game_item_process(Uint32 delta)
{
  unsigned int i,j;
  for(i = 0; i <= game_data.valid_item; i++)
    if(game_data.items[i].type)
    {
      game_data.items[i].x += game_data.items[i].sx*(int)delta/30;
      game_data.items[i].y += game_data.items[i].sy*(int)delta/30;
      if(is_outside(game_data.items[i].x, game_data.items[i].y))
        game_destroy_item(i);
      if(collision_item_player(i))
      {
        power_powerup_player(game_data.items[i].type);
	game_destroy_item(i);
      }
      if(collision_item_world(i) && (game_data.items[i].type == 2 || game_data.world.joined))
      {
        if(game_data.items[i].type == 2 && !(game_data.world.joined))
          power_health_world(1);
	else
	  power_powerup_player(game_data.items[i].type);
	game_destroy_item(i);
      }
    }
}
