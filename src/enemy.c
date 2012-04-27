#include <math.h>
#include "engine.h"
#include "game.h"
#include "collision.h"

void game_create_enemy(int x, int y, int sx, int sy, unsigned char life, unsigned char type, unsigned char drop)
{
  Spaceship *e;
  unsigned int i = 0;

  if(game_data.valid_enemy >= game_data.n_enemy)
    return;
  for(i = 0; i < game_data.n_enemy && game_data.enemies[i].life; i++);
  if(i > game_data.valid_enemy && i < game_data.n_enemy)
    game_data.valid_enemy = i;
  if(i >= game_data.n_enemy)
    return;
  e = &(game_data.enemies[i]);
  e->x = x;
  e->y = y;
  e->sx = sx;
  e->sy = sy;
  e->life = life;
  e->type = type;
  e->drop = drop;
  e->cooldown = 80;
}

void game_destroy_enemy(unsigned int e)
{
  unsigned int i;

  if(e >= game_data.n_enemy || e >= game_data.valid_enemy)
    return;
  game_data.enemies[e].life = 0;
  for(i = game_data.valid_enemy; i >= 0 && !(game_data.enemies[i].life); i--)
    game_data.valid_enemy = i;
}

/* Process enemy */
void enemy_fire(unsigned int e, int fx, int fy)
{
  float a, ax, ay;

  ax = game_data.enemies[e].x;
  ay = game_data.enemies[e].y;
  a = atanf(((float)fy - ay)/((float)fx - ax));
  game_create_bullet(game_data.enemies[e].x, game_data.enemies[e].y + 14,
                     (int)(-8.0f*cosf(a)), (int)(-8.0f*sinf(a)),
		     2);
}

void game_enemy_process(Uint32 delta)
{
   unsigned int i;

   for(i = 0; i <= game_data.valid_enemy; i++)
   {
     if(game_data.enemies[i].life)
     {
       if(is_outside(game_data.enemies[i].x, game_data.enemies[i].y))
         game_destroy_enemy(i);
       game_data.enemies[i].x += game_data.enemies[i].sx*(int)delta/15;
       game_data.enemies[i].y += game_data.enemies[i].sy*(int)delta/15;
       if(collision_enemy_player(i) && !power_is_invencible())
       {
         power_health_player(-1);
	 power_set_invencible();
	 if(game_data.enemies[i].type == 1)
	   game_destroy_enemy(i);
       }
       if(collision_enemy_world(i) && !power_is_invencible())
       {
         if(game_data.world.joined)
	 {
           power_health_player(-1);
	   power_set_invencible();
	   power_health_world(-10);
	 }
         else
	 {
           if(game_data.enemies[i].type < 3)
	     game_destroy_enemy(i);
	   else
	   {
             power_health_world(-10);
	     power_set_invencible();
	   }
	 }
       }
       if(game_data.enemies[i].cooldown + delta >= 1000 && game_data.enemies[i].type == 1)
       {
         enemy_fire(i, game_data.player.x, game_data.player.y);
         game_data.enemies[i].cooldown = 0;
       }
       game_data.enemies[i].cooldown += delta;
     }
   }
}
