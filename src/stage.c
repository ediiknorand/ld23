#include <SDL/SDL.h>
#include "stage.h"

void stage_process(Uint32 delta)
{
  switch(stage.current)
  {
  case 1: stage_1_process(delta); break;
  case 2: stage_2_process(delta); break;
  case 3: stage_3_process(delta); break;
  }
}
