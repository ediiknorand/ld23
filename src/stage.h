#include <SDL/SDL.h>

#ifndef H_STAGE_H
#define H_STAGE_H

typedef struct
{
  Uint32 enemy_delay, next_step;
  Uint32 ms;
  int current;
} Stage;

Stage stage;

void stage_process(Uint32 delta);

void stage_1_load();
void stage_1_process(Uint32 delta);

void stage_2_load();
void stage_2_process(Uint32 delta);

void stage_3_load();
void stage_3_process(Uint32 delta);

#endif
