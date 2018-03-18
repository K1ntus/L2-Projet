#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "model.h"

#include "../header/game.h"
#include "../header/game_io.h"

game new_game_generation(void){
  game g = load_game("../executable/saves/autosave");;
  return g;
}
