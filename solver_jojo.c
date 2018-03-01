#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "game_io.h"

bool potential_invalid_game(game g){
  for(unsigned int x = 0; x < game_width(g);x++){
    if(required_nb_seen(g, N, x) - current_nb_seen(g,N,x) < 0)
      return false;
    if(required_nb_seen(g,S,x) - current_nb_seen(g,S,x) < 0)
      return false;
  }


  for(unsigned int x = 0; x < game_height(g);x++){
    if(required_nb_seen(g, E, x) - current_nb_seen(g, E,x) < 0)
    return false;
    if(required_nb_seen(g,W,x) - current_nb_seen(g,W,x) < 0)
    return false;
  }

    return true;
}
game is_valid(game g, int pos, content monster){
  int x = pos/game_width(g);
  int y = pos/game_height(g);


  game g2 = copy_game(g);
  free(g);
  if(!(potential_invalid_game(g2))){
    free(g2);
    return NULL;
  }


  if(get_content(g2,x,y) == EMPTY){
    add_monster(g2, monster, x, y);
  }

  if(pos == game_width(g2) * game_height(g2) -1){
    if(is_game_over(g2)){
      return g2;
    }else{
      free(g2);
      return NULL;
    }
  }

  return is_valid(g2, pos++, ZOMBIE);
  return is_valid(g2, pos++, GHOST);
  return is_valid(g2, pos++, SPIRIT);
  return is_valid(g2, pos++, VAMPIRE);
}


int main(void) {
  game g = new_game_ext(4,4);
  g = is_valid(g,0,EMPTY);

  save_game(g, "solution dude");
  free(g);
}
