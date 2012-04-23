#include <stdlib.h>
#include "stage.h"
#include "engine.h"
#include "game.h"
#include "background.h"


void stage_2_load()
{
  background_load("resource/bg-02.bmp");
  stage.enemy_delay = 0;
  stage.next_step = 1000;
  stage.ms = 0;
  stage.current = 2;
}

void stage_2_process(Uint32 delta)
{
  stage.ms += delta;
  stage.enemy_delay += delta;
  if(stage.enemy_delay < stage.next_step)
    return;
  if(stage.next_step <= 2000)
  {
    game_create_enemy(engine_screen.width - 1, engine_screen.height/2, -3, 0, 6, 1, 0);
    game_create_enemy(engine_screen.width - 1, engine_screen.height/4, -3, -2, 6, 1, 0);
    stage.next_step += 800;
  }
  else if(stage.next_step <= 10000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height/3, -3, -2, 2, 1, 3);
    stage.next_step += 1000;
  }
  else if(stage.next_step <= 15000)
  {
    game_create_enemy(engine_screen.width -1, rand()%engine_screen.height, -3, 0, 6, 2, 0);
    stage.next_step += 600;
  }
  else if(stage.next_step <= 18000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height/10, -3, 1, 6, 1, 0);
    stage.next_step += 800;
  }
  else if(stage.next_step <= 22000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height/2, -2, 0, 80, 3, 1);
    stage.next_step = 23000;
  }
  else if(stage.next_step <= 32000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height/10, -5, 0, 3, 1, 0);
    game_create_enemy(engine_screen.width -1, engine_screen.height*9/10, -5, 0, 3, 1, 0);
    stage.next_step += 800;
  }
  else if(stage.next_step <= 35000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height/10, -5, 0, 1, 2, 2);
    game_create_enemy(engine_screen.width -1, engine_screen.height/2, -3, 0, 1, 2, 1);
    stage.next_step = 39000;
  }
  else if(stage.next_step <= 40000)
  {
    background_unload();
    stage_3_load();
  }
}
