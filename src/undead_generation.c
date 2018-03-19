#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../header/game.h"
#include "../header/game_io.h"

#include "./undead_solve.c"

game new_game_generation(void){

  int width =5, height = 6;      //Change to non-arbitrary values
  int nb_cells = width*height;
  int nb_mirror = nb_cells/2;    //Change to non-arbitrary values
  int nb_monsters = nb_cells/2;  //Change to non-arbitrary values

  game g = new_game_ext(width,height);
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      if((x+y) %2 == 0 && nb_mirror >0 && get_content(g,x,y) == EMPTY){
        add_mirror_ext(g, MIRROR,x,y);
        nb_mirror -= 1;
      }else if(nb_monsters > 0 && get_content(g,x,y) == EMPTY){
        add_monster(g,ZOMBIE,x,y);
        nb_monsters -=1;
      }
    }
  }



















  /*  ***   Check is the generated board is possible    *** */

	int nb_solution = 0;	//Integer which will contain the number of solution board find by the prog.

  game * res= (game*) malloc(sizeof(game) *50);	//We create an array which will contain (maximum) 50 solution board
  result_array_init(res);	//Init. it with few things


  solve_mode solving_result = NB_SOL;	//Get the solving mode wanted (ie. NB_SOL, FIND_ONE, *_ALL,)

  int i = 0;
  while(nb_solution == 0 && i < 100){

    game g = load_game("../executable/saves/autosave");

  	is_valid(g, 0, res, &nb_solution, solving_result);

    if(nb_solution != 0){
      free(res);
      return g;
    }else{
      i+=1;
      g = new_game_generation();
    }
  }
  return NULL;
}
