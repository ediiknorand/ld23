#include <stdlib.h>
#include "engine.h"
#include "scene.h"
#include "game.h"
#include "world.h"
#include "power.h"
#include "background.h"
#include "stage.h"

/* Game scene */

/* Aux functions */
int is_outside(int x, int y)
{
  if(x < 0 || x > engine_screen.width)
    return 1;
  if(y < (-engine_screen.height/3) || y > engine_screen.height)
    return 1;
  return 0;
}

/* Game Functions */
void game_init(unsigned int n_bullet, unsigned int n_enemy, unsigned int n_item)
{
  unsigned int i;
  game_data.player.x = engine_screen.width /3;
  game_data.player.y = engine_screen.height /2;
  game_data.player.sx = 5;
  game_data.player.sy = 5;
  game_data.player.cooldown = 0;
  game_data.world.x = game_data.world.y = -1;
  game_data.player.life = 5;

  game_data.n_bullet = n_bullet;
  game_data.bullet_array = malloc(sizeof(Bullet)*n_bullet);
  if(!(game_data.bullet_array))
    exit(1);
  game_data.valid_bullet = n_bullet - 1;

  game_data.n_enemy = n_enemy;
  game_data.enemies = malloc(sizeof(Spaceship)*n_enemy);
  if(!(game_data.enemies))
    exit(2);
  game_data.valid_enemy = n_enemy -1;

  game_data.n_item = n_item;
  game_data.items = malloc(sizeof(Bullet)*n_item);
  if(!(game_data.items))
    exit(3);
  game_data.valid_item = n_item -1;

  for(i = 0; i < game_data.n_bullet; i++)
    game_data.bullet_array[i].type = 0;
  for(i = 0; i < game_data.n_enemy; i++)
    game_data.enemies[i].life = 0;
  for(i = 0; i < game_data.n_item; i++)
    game_data.items[i].type = 0;

  engine_load_sprite("resource/sprite.bmp");
  stage_1_load();

  world_init();
}

void game_finish()
{
  free(game_data.bullet_array);
  free(game_data.enemies);
  SDL_FreeSurface(engine_sprites);
  background_unload();
}

void game_player_process(Uint32 delta)
{
  unsigned int i;

  if(game_data.player.cooldown <= 80 && !power_is_invencible())
    game_data.player.cooldown += delta;
  if(power_is_invencible())
    power_refresh_invencible(delta);
  if(game_data.world.cooldown <= 1000)
    game_data.world.cooldown += delta;

  if(engine_input.fire && game_data.player.cooldown > 80 && !power_is_invencible())
  {
    power_process_powerup();
    game_data.player.cooldown = 0;
  }

  if(game_data.world.joined)
    game_data.player.sx = game_data.player.sy = 5;
  else
    game_data.player.sx = game_data.player.sy = 15;

  if(engine_input.up)
    game_data.player.y -= game_data.player.sy*delta/30;
  if(engine_input.down)
    game_data.player.y += game_data.player.sy*delta/30;
  if(engine_input.left)
    game_data.player.x -= game_data.player.sx*delta/30;
  if(engine_input.right)
    game_data.player.x += game_data.player.sx*delta/30;

  if(game_data.player.x < 0)
    game_data.player.x = 0;
  if(game_data.player.y < 0)
    game_data.player.y = 0;
  if(game_data.player.x + 43 > engine_screen.width)
    game_data.player.x  = engine_screen.width - 43;
  if(game_data.player.y + 27> engine_screen.height)
    game_data.player.y = engine_screen.height - 27;

  if(engine_input.world && game_data.world.cooldown > 1000)
  {
    if(game_data.world.joined)
      world_leave();
    else if(!(game_data.world.join))
    {
      world_join();
    }
    game_data.world.cooldown = 0;
  }
}

/* Load Scene */
void scene_load_game()
{
  game_init(64, 16, 4);
}

/* Game logic */
int scene_logic_game(Uint32 delta)
{
  stage_process(delta);
  world_update(delta); /* <--------------------- */
  game_player_process(delta);
  game_item_process(delta);
  game_bullet_process(delta);
  game_enemy_process(delta);
  return 1;
}

/* Game render */
void bullet_draw()
{
  unsigned int i;
  for(i = 0; i <= game_data.valid_bullet; i++)
    switch(game_data.bullet_array[i].type)
    {
    case 1: engine_draw_sprite(engine_sprites, 44, 0, 15, 16, game_data.bullet_array[i].x, game_data.bullet_array[i].y); break;
    case 2: engine_draw_sprite(engine_sprites, 59, 0, 15, 16, game_data.bullet_array[i].x, game_data.bullet_array[i].y); break;
    }
}

void enemy_draw()
{
  unsigned int i;
  for(i = 0; i <= game_data.valid_enemy; i++)
    if(game_data.enemies[i].life)
      switch(game_data.enemies[i].type)
      {
      case 1: engine_draw_sprite(engine_sprites, 222, 4, 50, 41, game_data.enemies[i].x, game_data.enemies[i].y); break;
      case 2: engine_draw_sprite(engine_sprites, 273, 0, 64, 58, game_data.enemies[i].x, game_data.enemies[i].y); break;
      case 3: engine_draw_sprite(engine_sprites, 340, 0, 177, 177, game_data.enemies[i].x, game_data.enemies[i].y); break;
      }
}

void player_draw(Uint32 delta)
{
  if(power_is_invencible() && !(delta%2))
    return;
  engine_draw_sprite(engine_sprites, 0, 0, 43, 30, game_data.player.x, game_data.player.y);
}

void world_draw(Uint32 delta)
{
  if(power_is_invencible() && !(delta%2))
    return;
  engine_draw_sprite(engine_sprites, 102, 0, 118, 119, game_data.world.x, game_data.world.y);
}

void player_life_draw()
{
  int i;
  for(i = 1; i < game_data.player.life; i++)
    engine_draw_sprite(engine_sprites, 44, 16, 34, 31, 10+(i-1)*38, 2);
}

void world_life_draw()
{
  int i;
  for(i = 0; i < game_data.world.life; i+= 2)
    engine_draw_sprite(engine_sprites, 79, 16, 2, 13, 10+2*i, engine_screen.height - 15);
}

void item_draw()
{
  int i;
  for(i = 0; i <= game_data.valid_item; i++)
    if(game_data.items[i].type)
      engine_draw_sprite(engine_sprites, 44, 48+(game_data.items[i].type-1)*27, 34, 27, game_data.items[i].x, game_data.items[i].y);
}

void scene_render_game(Uint32 delta)
{
  background_draw(3, delta);
  world_draw(delta);
  player_draw(delta);
  enemy_draw();
  item_draw();
  bullet_draw();
  player_life_draw();
  world_life_draw();
}
