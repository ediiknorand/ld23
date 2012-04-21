#include "scene.h"

#ifndef H_GAME_H
#define H_GAME_H

typedef struct
{
  int x, y, sx, sy;
  unsigned char life;
  int id;
} Spaceship;

typedef struct
{
  int x, y, sx, sy;
  unsigned char life;
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
  unsigned int direct_bullet;

  Spaceship *enemies;
  unsigned int n_enemy;
  unsigned int valid_enemy;
  unsigned int direct_enemy;
} Game_data;

/* Global vars */
Game_data game_data;

/* Functions */
void game_init(unsigned int n_bullet, unsigned int n_enemy);
void game_finish();

void game_player_process(Uint32 delta);
void game_bullet_process(Uint32 delta);

void game_create_bullet(int x, int y, int sx, int sy, unsigned char type);
void game_create_enemy(int x, int y, int sx, int sy, unsigned char life);
void game_destroy_bullet(unsigned int b);
void game_destroy_enemy(unsigned int e);

#endif
