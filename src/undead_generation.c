
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //access() fun + chdir

#include "../header/game_display.h"
#include "../header/game_io.h"
#include "../header/game_fun.h"
#include "../header/game.h"

game generation(void){
  game g = new_game_ext(4,4);
  return g;
}
