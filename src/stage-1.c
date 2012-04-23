#include "stage.h"
#include "game.h"
#include "engine.h"
#include "background.h"

void stage_1_load()
{
  stage.enemy_delay = 0;
  stage.next_step = 2000;
  stage.ms = 0;
  stage.current = 1;
  background_load("resource/bg-01.bmp");
}

void stage_1_process(Uint32 delta)
{
  stage.ms += delta;
  stage.enemy_delay += delta;
  if(stage.enemy_delay < stage.next_step)
    return;
  if(stage.next_step <= 4000)
  {
    game_create_enemy(engine_screen.width - 1, engine_screen.height/5, -3, 0, 4, 2, 0);
    game_create_enemy(engine_screen.width - 1, engine_screen.height*3/5, -3, 0, 4, 2, 0);
    game_create_enemy(engine_screen.width - 1, engine_screen.height*9/10, -3, 0, 3, 2, 2);
    stage.next_step += 3000;
    return;
  } 
  else if(stage.next_step <= 10000)
  {
    game_create_enemy(engine_screen.width - 1, engine_screen.height/10, -3, 3, 4, 1, 0);
    stage.next_step += 800;
    return;
  }
  else if(stage.next_step <= 12000)
  {
    game_create_enemy(engine_screen.width - 1, engine_screen.height/2, -2, 0, 50, 3, 1);
    stage.next_step = 20000;
  }
  else if(stage.next_step <= 30000)
  {
    game_create_enemy(engine_screen.width - 1, engine_screen.height/3, -3, 1, 3, 1, 0);
    game_create_enemy(engine_screen.width - 1, engine_screen.height*2/3, -3, -1, 3, 1, 0);
    stage.next_step += 800;
  }
  else if(stage.next_step <= 35000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height/8, -3, -1, 3, 1, 0);
    stage.next_step += 800;
  }
  else if(stage.next_step <= 36000)
  {
    game_create_enemy(engine_screen.width -1, engine_screen.height*7/8, -3, 2, 3, 1, 2);
    stage.next_step += 1000;
  }
  else if(stage.next_step <= 48000)
  {
    background_unload();
    stage_2_load();
  }
}
