#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "game_display.c"
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

bool board_is_full(game g){
  for (unsigned int x = 0; x < game_width(g); x++){
    for(unsigned int y = 0; y < game_height(g); y++){
      if(get_content(g,x,y) == EMPTY)
        return false;
    }
  }
  return true;
}


game is_valid(game g, int pos, content monster){
  int x = pos/game_width(g);
  int y = pos/game_height(g);

  game g2 = new_game_ext(game_width(g), game_height(g));
  g2 = copy_game(g);
  free(g);
  if(!(potential_invalid_game(g2))){
    free(g2);
    return NULL;
  }


  if(get_content(g2,x,y) == EMPTY){
    add_monster(g2, monster, x, y);
  }

  if(board_is_full(g2)){
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
  game g1 = load_game("autosave");
  g1 = is_valid(g1,0,EMPTY);

  //display(g);
  if(g1 == NULL){
    printf("No solution has been find\n");
  } else{
    save_game(g1, "solution_dude");
  }
  free(g1);
}
