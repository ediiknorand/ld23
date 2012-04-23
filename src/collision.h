#ifndef H_COLLISION_H
#define H_COLLISION_H

int collision_detect_world();

int collision_bullet_player(unsigned int b);
int collision_enemy_player(unsigned int e);

int collision_bullet_world(unsigned int b);
int collision_enemy_world(unsigned int e);

int collision_bullet_enemy(unsigned int b, unsigned int e);

int collision_item_player(unsigned int t);
int collision_item_world(unsigned int t);

#endif
