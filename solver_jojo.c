#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "game.h"
#include "game_display.c"
#include "game_io.h"


typedef enum e_solve_mode {FIND_ONE,NB_SOL,FIND_ALL} solve_mode;



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


//game is_valid(game g, int pos, content monster, int *nb_sol){
game is_valid(game g, int pos, content monster){
  int x = pos%game_width(g);
  int y = pos/game_width(g);


      if(is_game_over(g)){
        return g;
      }
  game g2 = new_game_ext(game_width(g), game_height(g));
  g2 = copy_game(g);
  printf("pos:%d\n", pos);

  /*
  if(!(potential_invalid_game(g2))){
    free(g2);
    return NULL;
  }*/



  if(get_content(g2,x,y) == EMPTY){
    add_monster(g2, monster, x, y);
  }
      if(is_game_over(g2)){
        return g2;
      }


  if(board_is_full(g2)){
    free(g2);
    return NULL;
  }
  /*
  return is_valid(g2, pos++, ZOMBIE, nb_sol);
  return is_valid(g2, pos++, GHOST, nb_sol);
  return is_valid(g2, pos++, SPIRIT, nb_sol);
  return is_valid(g2, pos++, VAMPIRE, nb_sol);
  */

  if(required_nb_monsters(g,ZOMBIE) - current_nb_monsters(g, ZOMBIE) > 0)
    is_valid(g2, pos+1, ZOMBIE);

  if(required_nb_monsters(g,GHOST) - current_nb_monsters(g, GHOST) > 0)
    is_valid(g2, pos+1, GHOST);

  if(required_nb_monsters(g,SPIRIT) - current_nb_monsters(g, SPIRIT) > 0)
    is_valid(g2, pos+1, SPIRIT);

  if(required_nb_monsters(g,VAMPIRE) - current_nb_monsters(g, VAMPIRE) > 0)
    is_valid(g2, pos+1, VAMPIRE);

  return NULL;
}


int main(void) {
  printf("Loading file\n");
  game g1 = load_game("autosave");
  printf("File has been loaded\n");
  //int nb_solution = 0;

  //g1 = is_valid(g1,0,EMPTY, &nb_solution);
  g1 = is_valid(g1,0,EMPTY);

  if(g1 == NULL){
    printf("No solution has been find\n");
  } else{
    //printf("There's %d solutions! \n",nb_solution);
    save_game(g1, "this_is_the_solution_dude");
  }

  free(g1);

  return EXIT_SUCCESS;
}
