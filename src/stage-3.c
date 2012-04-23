#include <stdlib.h>
#include "stage.h"
#include "engine.h"
#include "scene.h"
#include "game.h"
#include "background.h"


void stage_3_load()
{
  stage.enemy_delay = 0;
  stage.next_step = 2000;
  stage.ms = 0;
  stage.current = 3;
  background_load("resource/bg-03.bmp");
}

void stage_3_process(Uint32 delta)
{
  stage.ms += delta;
  stage.enemy_delay += delta;
  if(stage.enemy_delay < stage.next_step)
    return;
  if(stage.next_step <= 4000)
  {
    game_create_enemy(engine_screen.width-1, engine_screen.height/2, -4, 0, 10, 1, 0);
    game_create_enemy(engine_screen.width-1, engine_screen.height*8/9, -8, 1, 3, 1, 2);
    stage.next_step += 500;
  }
  else if(stage.next_step <= 10000)
  {
    game_create_enemy(engine_screen.width-1, engine_screen.height/10, -3, 2, 7, 1, 1);
    stage.next_step += 900;
  }
  else if(stage.next_step <= 18000)
  {
    game_create_enemy(engine_screen.width-1, rand()%engine_screen.height, -5, 0, 5, 1, 2);
    stage.next_step += 1000;
  }
  else if(stage.next_step <= 24000)
  {
    game_create_enemy(engine_screen.width-1, engine_screen.height/2, -2, 0, 20, 3, 1);
    stage.next_step = 25000;
  }
  else if(stage.next_step <= 26000)
  {
    game_create_enemy(engine_screen.width-1, rand()%engine_screen.height, -2, 0, 50, 3, 2);
    stage.next_step += 1000;
  }
  else if(stage.next_step <= 40000)
  {
    game_create_enemy(engine_screen.width-1, engine_screen.height/10, -10, 1, 4, 1, 3);
    game_create_enemy(engine_screen.width-1, engine_screen.height*9/10, -10, -1, 4, 1, 1);
    stage.next_step += 900;
  }
  else if(stage.next_step <= 50000)
  {
    game_create_enemy(engine_screen.width-1, engine_screen.height/2, -2, 0, 100, 3, 2);
    stage.next_step = 50001;
  }
  else if(!(game_data.valid_enemy))
  {
    background_unload();
    engine_load_scene(SCENE_INIT);
  }
}
