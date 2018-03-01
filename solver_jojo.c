#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.c"

game is_valid(game g, int pos, content monster){
  int x = pos/game_width(g);
  int y = pos/game_height(g);
  if(get_content(g,x,y) == EMPTY){
    add_monster(g, monster, x, y);
  }

  if(pos == game_width(g) * game_height(g) -1){
    game g2 = copy_game(g);
    if(is_game_over(g2)){
      return g2;
    }else{
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
  is_valid(g,0,EMPTY);
}
