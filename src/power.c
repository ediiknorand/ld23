#include "engine.h"
#include "game.h"
#include "collision.h"
#include "power.h"
#include "scene.h"

/* Health */
void power_health_player(int h)
{
  if(game_data.player.life + h > 10)
    return;
  if(game_data.player.life + h <= 0)
    power_death_player();
  game_data.player.life += h;
}

void power_health_world(int h)
{
  if(game_data.world.life + h > 200)
    return;
  game_data.world.life += h;
  if(game_data.world.life + h <= 0)
    power_death_player();
  game_data.world.life += h;
}

/* Death */
void power_death_player()
{
  game_data.player.life = 0;
  engine_load_scene(SCENE_GAMEOVER);
}

/* Powerup effects */
void power_powerup_player(unsigned char type)
{
  switch(type)
  {
  case 0:
  case 1: game_data.world.powerup_type = type; break;
  case 2: power_health_player(1); break;
  case 3: power_set_invencible();
  }
}

void power_process_powerup()
{
  switch(game_data.world.powerup_type)
  {
  case 1: game_create_bullet(game_data.player.x + 30, game_data.player.y + 10, 30, 10, 1);
          game_create_bullet(game_data.player.x + 30, game_data.player.y - 10, 30, -10, 1);
  case 0: game_create_bullet(game_data.player.x + 30, game_data.player.y, 30, 0, 1);
  }
}

/* Invencible status */
void power_set_invencible()
{
  game_data.world.invencible = 1;
  game_data.player.cooldown = 0;
}

int power_is_invencible()
{
  return game_data.world.invencible;
}

void power_refresh_invencible(Uint32 delta)
{
  if(game_data.player.cooldown + delta > 2000)
  {
    game_data.world.invencible = 0;
    game_data.player.cooldown = 0;
  }
  game_data.player.cooldown += delta;
}
