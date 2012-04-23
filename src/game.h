#include "scene.h"

#ifndef H_GAME_H
#define H_GAME_H

typedef struct
{
  int x, y, sx, sy;
  Uint32 cooldown;
  unsigned char life;
  unsigned char type;
  unsigned char drop;
} Spaceship;

typedef struct
{
  int x, y, sx, sy;
  unsigned char life;
  unsigned char join;
  unsigned char joined;
  Uint32 cooldown;
  unsigned char powerup_type;
  unsigned char invencible;
} World;

typedef struct
{
  int x, y, sx, sy;
  unsigned char type;
} Bullet;

typedef struct
{
  Spaceship player;
  World world;

  Bullet *bullet_array;
  unsigned int n_bullet;
  unsigned int valid_bullet;

  Spaceship *enemies;
  unsigned int n_enemy;
  unsigned int valid_enemy;

  Bullet *items;
  unsigned int n_item;
  unsigned int valid_item;
} Game_data;

/* Global vars */
Game_data game_data;

/* Functions */
void game_init(unsigned int n_bullet, unsigned int n_enemy, unsigned int n_item);
void game_finish();

void game_player_process(Uint32 delta);
void game_bullet_process(Uint32 delta);
void game_item_process(Uint32 delta);

void game_create_bullet(int x, int y, int sx, int sy, unsigned char type);
void game_create_enemy(int x, int y, int sx, int sy, unsigned char life, unsigned char type, unsigned char drop);
void game_destroy_bullet(unsigned int b);
void game_destroy_enemy(unsigned int e);

void game_create_item(int x, int y, int sx, int sy, unsigned char type);
void game_destroy_item(unsigned int t);

#endif
