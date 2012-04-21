#include <stdlib.h>
#include "engine.h"
#include "scene.h"
#include "game.h"

/* Game scene */

/* Aux functions */
int is_outside(int x, int y)
{
  if(x < 0 || x > engine_screen.width)
    return 1;
  if(y < 0 || y > engine_screen.height)
    return 1;
  return 0;
}

/* Game Functions */
void game_init(unsigned int n_bullet, unsigned int n_enemy)
{
  unsigned int i;
  game_data.player.x = engine_screen.width /3;
  game_data.player.y = engine_screen.height /2;
  game_data.player.sx = 5;
  game_data.player.sy = 5;
  game_data.world.x = game_data.world.y = -1;
  //game_move_world_to_player();

  game_data.n_bullet = n_bullet;
  game_data.bullet_array = malloc(sizeof(Bullet)*n_bullet);
  if(!(game_data.bullet_array))
    exit(1);
  game_data.valid_bullet = 0;
  game_data.direct_bullet = 0;

  game_data.n_enemy = n_enemy;
  game_data.enemies = malloc(sizeof(Spaceship)*n_enemy);
  if(!(game_data.enemies))
    exit(2);
  game_data.valid_enemy = 0;
  game_data.direct_enemy = 0;

  for(i = 0; i < game_data.n_bullet; i++)
    game_data.bullet_array[i].type = 0;
  for(i = 0; i < game_data.n_enemy; i++)
    game_data.enemies[i].life = 0;
  engine_load_sprite("resource/sprite.bmp");
}

void game_finish()
{
  free(game_data.bullet_array);
  free(game_data.enemies);
  SDL_FreeSurface(engine_sprites);
}

void game_player_process(Uint32 delta)
{
  unsigned int i;

  if(engine_input.fire)
    game_create_bullet(game_data.player.x, game_data.player.y, 30, 0, 1);
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
  if(game_data.player.x > engine_screen.width)
    game_data.player.x = engine_screen.width - 43;
  if(game_data.player.y > engine_screen.height)
    game_data.player.y = engine_screen.height - 43;

  if(engine_input.debug) /* ... debug? */
  {
    printf("n_bullet: %u, valid_bullet: %u, direct_bullet: %u\n",game_data.n_bullet, game_data.valid_bullet, game_data.direct_bullet);
    for(i = 0; i < game_data.n_bullet; i++)
      printf("%u: %u\n",i,(unsigned int)game_data.bullet_array[i].type);
  }
}

void game_bullet_process(Uint32 delta)
{
  unsigned int i;
  for(i = 0; i <= game_data.valid_bullet; i++)
    if(game_data.bullet_array[i].type)
    {
      game_data.bullet_array[i].x += game_data.bullet_array[i].sx*delta/30;
      game_data.bullet_array[i].y += game_data.bullet_array[i].sy*delta/30;
      if(is_outside(game_data.bullet_array[i].x, game_data.bullet_array[i].y))
        game_destroy_bullet(i);
    }
    else if(i < game_data.direct_bullet)
      game_data.direct_bullet = i;
}

/* Game Manager */

void game_create_bullet(int x, int y, int sx, int sy, unsigned char type)
{
  Bullet *b;
  unsigned int i = game_data.direct_bullet;
  if(game_data.valid_bullet >= game_data.n_bullet)
    return;
  if(game_data.bullet_array[i].type)
    return;
  if(game_data.direct_bullet < game_data.valid_bullet)
  {
    for(i = game_data.direct_bullet; (i <= game_data.valid_bullet) && game_data.bullet_array[i].type; i++)
      game_data.direct_bullet = i;
    if(i <= game_data.valid_bullet)
      game_data.direct_bullet++;
  }
  b = &(game_data.bullet_array[i]);
  b->x = x;
  b->y = y;
  b->sx = sx;
  b->sy = sy;
  b->type = type;
  if(type && (game_data.valid_bullet == game_data.direct_bullet) && game_data.valid_bullet < game_data.n_bullet-1)
  {
    game_data.direct_bullet++;
    game_data.valid_bullet++;
  }
}

void game_create_enemy(int x, int y, int sx, int sy, unsigned char life)
{
  Spaceship *e;
  unsigned int i = game_data.direct_enemy;
  if(game_data.valid_enemy >= game_data.n_enemy)
    return;
  if(game_data.enemies[i].life)
    return;
  if(game_data.direct_enemy < game_data.valid_enemy)
  {
    for(i = game_data.direct_enemy; (i <= game_data.valid_enemy) && game_data.enemies[i].life; i++)
      game_data.direct_enemy = i;
    if(i <= game_data.valid_enemy)
      game_data.direct_enemy++;
  }
  e = &(game_data.enemies[i]);
  e->x = x;
  e->y = y;
  e->sx = sx;
  e->sy = sy;
  e->life = life;
  if(life && (game_data.valid_enemy == game_data.direct_enemy) && game_data.valid_enemy < game_data.n_enemy-1)
  {
    game_data.direct_enemy++;
    game_data.valid_bullet++;
  }
}

void game_destroy_bullet(unsigned int b)
{
  unsigned int i;

  if(b > game_data.n_bullet || b > game_data.valid_bullet)
    return;
  game_data.bullet_array[b].type = 0;
  for(i = game_data.valid_bullet; i >= 0 && !(game_data.bullet_array[i].type); i--)
    game_data.valid_bullet = i;
  if(b < game_data.direct_bullet)
    game_data.direct_bullet = b;
}

void game_destroy_enemy(unsigned int e)
{
  unsigned int i;

  if(e > game_data.n_enemy || e > game_data.valid_enemy)
    return;
  game_data.enemies[e].life = 0;
  for(i = game_data.valid_enemy; i >= 0 && !(game_data.enemies[i].life); i--)
    game_data.valid_enemy = i;
  if(e < game_data.direct_enemy)
    game_data.direct_enemy = e;
}

/* Load Scene */
void scene_load_game()
{
  game_init(32, 16);
}

/* Game logic */
int scene_logic_game(Uint32 delta)
{
  game_player_process(delta);
  game_bullet_process(delta);
  return 1;
}

/* Game render */
void bullet_draw()
{
  unsigned int i;
  for(i = 0; i < game_data.valid_bullet; i++)
    if(game_data.bullet_array[i].type)
      engine_draw_sprite(engine_sprites, 44, 0, 15, 16, game_data.bullet_array[i].x, game_data.bullet_array[i].y);
}

void player_draw()
{
  engine_draw_sprite(engine_sprites, 0, 0, 43, 43, game_data.player.x, game_data.player.y);
}

void scene_render_game(Uint32 delta)
{
  player_draw();
  bullet_draw();
}
