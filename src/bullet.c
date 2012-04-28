#include "engine.h"
#include "game.h"
#include "collision.h"

void game_create_bullet(int x, int y, int sx, int sy, unsigned char type)
{
  Bullet *b;
  unsigned int i = 0;

  if(game_data.valid_bullet >= game_data.n_bullet)
    return;
  for(i = 0; i < game_data.n_bullet && game_data.bullet_array[i].type; i++);
  if(i > game_data.valid_bullet && i < game_data.n_bullet)
    game_data.valid_bullet = i;
  if(i >= game_data.n_bullet)
    return;
  b = &(game_data.bullet_array[i]);
  b->x = x;
  b->y = y;
  b->sx = sx;
  b->sy = sy;
  b->type = type;
}

void game_destroy_bullet(unsigned int b)
{
  unsigned int i;

  if(b >= game_data.n_bullet || b > game_data.valid_bullet)
    return;
  game_data.bullet_array[b].type = 0;
  for(i = game_data.valid_bullet; i >= 0 && !(game_data.bullet_array[i].type); i--)
    game_data.valid_bullet = i;
}

void game_bullet_process(Uint32 delta)
{
  unsigned int i,j;
  for(i = 0; i <= game_data.valid_bullet; i++)
    if(game_data.bullet_array[i].type)
    {
      game_data.bullet_array[i].x += game_data.bullet_array[i].sx*(int)delta/30;
      game_data.bullet_array[i].y += game_data.bullet_array[i].sy*(int)delta/30;
      if(is_outside(game_data.bullet_array[i].x, game_data.bullet_array[i].y))
        game_destroy_bullet(i);
      if(!power_is_invencible())
      {
        if(collision_bullet_player(i) && game_data.bullet_array[i].type > 1)
        {
          power_set_invencible();
	  power_health_player(-1);
          game_destroy_bullet(i);
        }
        if(collision_bullet_world(i) && game_data.bullet_array[i].type > 1)
        {
	  if(game_data.world.joined)
	  {
            power_set_invencible();
	    power_health_player(-1);
	  }
	  power_health_world(-10);
          game_destroy_bullet(i);
        }
      }
      if(game_data.bullet_array[i].type == 1)
        for(j = 0; j <= game_data.valid_enemy; j++)
	  if(game_data.enemies[j].life && collision_bullet_enemy(i, j))
          {
            game_data.enemies[j].life -= 1;
	    if(!(game_data.enemies[j].life))
	    {
	      if(game_data.enemies[j].drop)
	      {
	        game_create_item(game_data.enemies[j].x, game_data.enemies[j].y, -4, 0, game_data.enemies[j].drop);
              }
	      game_destroy_enemy(j);
	    }
	    game_destroy_bullet(i);
	  }
    }
}
