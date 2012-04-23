#include "game.h"
#include "engine.h"
#include "collision.h"

int collision_enemy_x_offset(unsigned char type)
{
  switch(type)
  {
  case 1: return 20; break;
  case 2: return 32; break;
  case 3: return 58; break;
  }
}

int collision_enemy_y_offset(unsigned char type)
{
  switch(type)
  {
  case 1: return 20; break;
  case 2: return 27; break;
  case 3: return 58; break;
  }
}

int collision_enemy_radius_2(unsigned char type)
{
  switch(type)
  {
  case 1: return 40*40; break;
  case 2: return 40*40; break;
  case 3: return 80*80; break;
  }
}

int collision_detect_world()
{
  int dx = game_data.player.x+30 - game_data.world.x-60;
  int dy = game_data.player.y+15 - game_data.world.y-60;

  if(dx*dx + dy*dy <= 55*55)
    return 1;
  return 0;
}

int collision_bullet_player(unsigned int b)
{
  int dx = game_data.player.x+30 - game_data.bullet_array[b].x;
  int dy = game_data.player.y+15 - game_data.bullet_array[b].y;

  if(dx*dx + dy*dy <= 30*30)
    return 1;
  return 0;
}

int collision_enemy_player(unsigned int e)
{
  unsigned char type = game_data.enemies[e].type;
  int dx = game_data.player.x+30 - game_data.enemies[e].x - collision_enemy_x_offset(type);
  int dy = game_data.player.y+15 - game_data.enemies[e].y - collision_enemy_y_offset(type);

  if(dx*dx + dy*dy <= collision_enemy_radius_2(type))
    return 1;
  return 0;
}

int collision_bullet_world(unsigned int b)
{
  int dx = game_data.world.x+45 - game_data.bullet_array[b].x -5;
  int dy = game_data.world.y+45 - game_data.bullet_array[b].y -5;

  if(dx*dx + dy*dy <= 55*55)
    return 1;
  return 0;
}

int collision_enemy_world(unsigned int e)
{
  unsigned char type = game_data.enemies[e].type;
  int dx = game_data.world.x+45 - game_data.enemies[e].x - collision_enemy_x_offset(type);
  int dy = game_data.world.y+45 - game_data.enemies[e].y - collision_enemy_y_offset(type);

  if(type == 3)
  {
    if(dx*dx + dy*dy <= collision_enemy_radius_2(type))
      return 1;
  }
  else if(dx*dx + dy*dy <= 90*90)
    return 1;
  return 0;
}

int collision_bullet_enemy(unsigned int b, unsigned int e)
{
  unsigned char type = game_data.enemies[e].type;
  int dx = game_data.bullet_array[b].x - game_data.enemies[e].x - collision_enemy_x_offset(type);
  int dy = game_data.bullet_array[b].y - game_data.enemies[e].y - collision_enemy_y_offset(type);

  if(dx*dx + dy*dy <= collision_enemy_radius_2(type))
    return 1;
  return 0;
}

int collision_item_player(unsigned int t)
{
  int dx = game_data.player.x+30 - game_data.items[t].x;
  int dy = game_data.player.y+15 - game_data.items[t].y;

  if(dx*dx + dy*dy <= 40*40)
    return 1;
  return 0;
}

int collision_item_world(unsigned int t)
{
  int dx = game_data.world.x+45 - game_data.items[t].x;
  int dy = game_data.world.y+45 - game_data.items[t].y;

  if(dx*dx + dy*dy <= 55*55)
    return 1;
  return 0;
}
