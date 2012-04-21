#include <SDL/SDL.h>

#ifndef H_SCENE_H
#define H_SCENE_H

#define SCENE_INIT 0
#define SCENE_GAME 5

/* Game scenes */

/* Init */
void scene_load_init();
int scene_logic_init(Uint32 delta);
void scene_render_init(Uint32 delta);

/* Game */
void scene_load_game();
int scene_logic_game(Uint32 delta);
void scene_render_game(Uint32 delta);

#endif
